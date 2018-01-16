#include "../preamble.h"
#include "Qbf2DatalogTreeAlgorithm.hpp"

#include <qbf2asp/create.hpp>
#include <qbf2asp/DecomposableQbfInstance.hpp>

#include <memory>
#include <sstream>
#include <climits>

#include <set>

namespace qbf2asp
{
	using logic::IQbfInstance;
	using logic::IQbfClause;
	using logic::variable_t;
	using logic::clause_t;

	using sharp::INodeTableMap;
	using sharp::IDecomposableInstance;
	using sharp::ITable;

	using htd::IHypergraph;
	using htd::ITreeDecompositionAlgorithm;
	using htd::ITreeDecomposition;
	using htd::ILabelingFunction;
	using htd::ConstCollection;
	using htd::ConstIterator;
	using htd::vertex_t;

	using std::vector;
	using std::list;
	using std::unique_ptr;
	using std::unordered_set;
	using std::ostream;
	using std::ostringstream;
	using std::string;
	using std::to_string;
	using std::endl;

    using std::set;

	Qbf2DatalogTreeAlgorithm::Qbf2DatalogTreeAlgorithm() : out_(&std::cout) { }

	Qbf2DatalogTreeAlgorithm::~Qbf2DatalogTreeAlgorithm() { }

	void Qbf2DatalogTreeAlgorithm::setOutputStream(ostream &out)
	{
		out_ = &out;
	}

	vector<const ILabelingFunction *>
	Qbf2DatalogTreeAlgorithm::preprocessOperations() const
	{
		return vector<const ILabelingFunction *>();
	}
	
	ITable *Qbf2DatalogTreeAlgorithm::evaluateNode(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const INodeTableMap &tables,
			const IDecomposableInstance &instance) const
	{
		const DecomposableQbfInstance &qbfInstance(
				static_cast<const DecomposableQbfInstance &>(instance));

		return evaluateNode(node, decomposition, tables, qbfInstance.content());
	}

	bool Qbf2DatalogTreeAlgorithm::needAllTables() const
	{
		return false;
	}
    
	ITable *Qbf2DatalogTreeAlgorithm::evaluateNode(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const INodeTableMap &tables,
			const IQbfInstance &instance) const
	{
		// print some debug output about the current node
		DBG(node); DBG(": ");
		DBG_COLL(decomposition.bagContent(node)); DBG("; ");
		DBG_COLL(clauses(node, decomposition, instance)); DBG(".");
		DBG(endl);

		unique_ptr<Qbf2DatalogTable> table(
				createTable(node, decomposition, tables, instance));

		// store the order of the variables
		list<variable_t> order;
		for(variable_t var : table->current) order.push_back(var);
		for(variable_t var : table->forgotten) order.push_back(var);

		// process all clauses
		for(clause_t clause : clauses(node, decomposition, instance))
			printClauseRule(instance, node, order, clause);

		// add variables that we will forget to the appropriate list
		for(variable_t var : variablesToForget(node, decomposition))
		{
			table->forgotten.insert(var);
			table->current.erase(var);
		}

		DBG(node); DBG(": "); DBG_COLL(order);
		DBG_COLL(table->forgotten); DBG("; ");

		// now, project out as many variables as possible
		long step = 0;
		while(true)
		{
			DBG_COLL(table->remaining); DBG("&");

			unordered_set<variable_t> projectOut;
			for(auto it = table->remaining.begin();
                it != table->remaining.end();) {
				if(table->forgotten.find(*it) != table->forgotten.end())
				{
                    // Keep track of the eliminated variables.
                    table->eliminated.insert(*it);
                    
					projectOut.insert(*it);
					table->forgotten.erase(*it);
					table->current.erase(*it);
					it = table->remaining.erase(it);
				}
				else
				{
					++it;
				}
            }

			DBG_COLL(projectOut); DBG(" = "); DBG(table->currentQuantifier);
			DBG(endl);

			if(projectOut.empty()) {
				break;
            }
            
            printEliminationRules(instance, node, projectOut, order, step);
            
            // Check if there new minimal elements to be eliminated.
            
            set<variable_t> minimalVariables;
            set<variable_t> eliminatedVariables(
                table->eliminated.begin(), table->eliminated.end());
            
            order_->minimalVariables(eliminatedVariables, minimalVariables);
            

            if (!minimalVariables.empty()) {
                table->remaining.insert(
                    minimalVariables.begin(), minimalVariables.end());
            } else {
                break;
            }
		}

		printOutputRule(node, step, table->current, table->forgotten, order);

		if(decomposition.isRoot(node))
			printRootRules(node);

		return table.release();
	}

	Qbf2DatalogTable *Qbf2DatalogTreeAlgorithm::createTable(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const INodeTableMap &tables,
			const IQbfInstance &instance) const
	{
		if(decomposition.isLeaf(node))
			return createLeafTable(node, decomposition, instance);
		return createNodeTable(node, decomposition, tables, instance);
	}

	Qbf2DatalogTable *Qbf2DatalogTreeAlgorithm::createLeafTable(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const IQbfInstance &instance) const
	{
		unique_ptr<Qbf2DatalogTable> table(new Qbf2DatalogTable());

		table->current.insert(
				decomposition.bagContent(node).begin(),
				decomposition.bagContent(node).end());
        
		table->currentQuantifier = instance.innermostQuantifierLevel();
        
		// table->remaining = instance.variables(table->currentQuantifier);

        set<variable_t> minimalVariables;
        
        order_->minimalVariables(minimalVariables);

        table->remaining.insert(
            minimalVariables.begin(), minimalVariables.end());
        
		return table.release();
	}

    void Qbf2DatalogTreeAlgorithm::intersectRemainingVariables(
        const INodeTableMap &tables,
        unordered_set<variable_t> & remaining,
        ConstCollection<vertex_t> children) const
    {
        for (auto child : children) {
            const Qbf2DatalogTable &ctable = table(child, tables);
            for(auto it = remaining.begin(); it != remaining.end();) {
                if(ctable.remaining.find(*it) == ctable.remaining.end()) {
                    it = remaining.erase(it);
                }
                else {
                    ++it;
                }
            }

        }
    }
    
	Qbf2DatalogTable *Qbf2DatalogTreeAlgorithm::createNodeTable(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const INodeTableMap &tables,
			const IQbfInstance &instance) const
	{
		unique_ptr<Qbf2DatalogTable> table(new Qbf2DatalogTable());

		table->current.insert(
				decomposition.bagContent(node).begin(),
				decomposition.bagContent(node).end());
		table->currentQuantifier = SHRT_MAX;

        // (1) Get all the remaining nodes from the children
        // (2) Get all the eliminated nodes from the children
        // (3) Get all the forgotten nodes from the children
        
		ConstCollection<vertex_t> children = decomposition.children(node);

		processChildTables(node, instance,
                           table->current,
                           tables,
                           table->currentQuantifier,
                           table->remaining,
                           table->eliminated,
                           table->forgotten,
                           children.begin(),
                           children.end());

        // (4) Intersect the remaining sets with all remaining
        
        intersectRemainingVariables(tables, table->remaining, children);
        
        // (5) Find the new minimal nodes, add them to remaining

        set<variable_t> minimalVariables;
        set<variable_t> eliminatedVariables(
            table->eliminated.begin(), table->eliminated.end());
        
        order_->minimalVariables(eliminatedVariables, minimalVariables);
        table->remaining.insert(minimalVariables.begin(), minimalVariables.end());

		return table.release();
	}

	const Qbf2DatalogTable &Qbf2DatalogTreeAlgorithm::table(
			vertex_t node,
			const INodeTableMap &tables) const
	{
		return static_cast<const Qbf2DatalogTable &>(tables[node]);
	}

	unordered_set<variable_t> Qbf2DatalogTreeAlgorithm::variablesToForget(
			vertex_t node,
			const ITreeDecomposition &decomposition) const
	{
		unordered_set<variable_t> result;

		if(decomposition.isRoot(node))
		{
			result.insert(
					decomposition.bagContent(node).begin(),
					decomposition.bagContent(node).end());
		}
		else
		{
			vertex_t parent = decomposition.parent(node);
			auto toForget = decomposition.forgottenVertices(parent, node);

			result.insert(toForget.begin(), toForget.end());
		}

		return result;
	}

	unordered_set<clause_t> Qbf2DatalogTreeAlgorithm::clauses(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const IQbfInstance &instance) const
	{
		unordered_set<clause_t> clauses;

		for(auto edge : decomposition.inducedHyperedges(node))
			clauses.insert(edge.id() + instance.variableCount());

		return clauses;
	}

	void Qbf2DatalogTreeAlgorithm::processChildTables(
			vertex_t node,
			const IQbfInstance &instance,
			const unordered_set<variable_t> &current,
			const INodeTableMap &tables,
			short &currentQuantifier,
			std::unordered_set<logic::variable_t> &remaining,
            std::unordered_set<logic::variable_t> &eliminated,
			std::unordered_set<logic::variable_t> &forgotten,
			htd::ConstIterator<htd::vertex_t> begin,
			htd::ConstIterator<htd::vertex_t> end) const
	{
			const Qbf2DatalogTable &ctable = table(*begin, tables);

            // Find all the remaining variables
            remaining.insert(ctable.remaining.begin(), ctable.remaining.end());

            // Remove variables that have been eliminated by a child
            for(auto it = remaining.begin(); it != remaining.end();) {
                if(ctable.remaining.find(*it) == ctable.remaining.end()) {
                    it = remaining.erase(it);
                }
                else {
                    ++it;
                }
            }
            
			forgotten.insert(ctable.forgotten.begin(), ctable.forgotten.end());

			// recursively proceed though all children
			vertex_t child = *begin++;
			if(begin != end)
				processChildTables(node,
                                   instance,
                                   current,
                                   tables,
                                   currentQuantifier,
                                   remaining,
                                   eliminated,
                                   forgotten,
                                   begin,
                                   end);

			// now that we know all forgotten nodes, print out the rule
			printMappingRule(node, current, forgotten, 
					child, ctable.current, ctable.forgotten);
	}

	void Qbf2DatalogTreeAlgorithm::printMappingRule(
			vertex_t node,
			const unordered_set<variable_t> &current,
			const unordered_set<variable_t> &forgotten,
			vertex_t child,
			const unordered_set<variable_t> &ccurrent,
			const unordered_set<variable_t> &cforgotten) const
	{
		ostream &out = *out_;
		unordered_set<variable_t> notInChild;

		// print the head: 
		out << "p_" << node << "_in(";
		
		// all current variables
		string sep = "";
		for(variable_t var : current)
		{
			out << sep << "V" << var;
			sep = ", ";

			if(ccurrent.find(var) == ccurrent.end())
				notInChild.insert(var);
		}

		// and all forgotten variables
		for(variable_t var : forgotten)
		{
			out << sep << "V" << var;
			sep = ", ";
		}

		// finish head, print implication, and start body:
		out << ") :- p_" << child << "_out(";

		// all current variables in the child
		sep = "";
		for(variable_t var : ccurrent)
		{
			out << sep << "V" << var;
			sep = ", ";
		}

		// and all forgotten variables in the child
		for(variable_t var : forgotten)
			if(cforgotten.find(var) == cforgotten.end())
			{
				notInChild.insert(var);
			}
			else
			{
				out << sep << "V" << var;
				sep = ", ";
			}

		// finalize the big body atom
		out << ")";

		// and print all tf atoms for variables not in the child
		sep = ", ";
		for(variable_t var : notInChild)
			out << sep << "tf(V" << var << ")";

		// print the end of the rule
		out << "." << endl;
	}

	void Qbf2DatalogTreeAlgorithm::printClauseRule(
			const IQbfInstance &instance,
			vertex_t node,
			const list<variable_t> &order,
			clause_t clauseId) const
	{
		ostream &out = *out_;
		const IQbfClause &clause = instance.clause(clauseId);
		string sep;

		// print head and implication symbol:
		out << "p_" << node << "_in(";
		sep = "";
		for(variable_t var : order)
		{
			out << sep << "V" << var;
			sep = ", ";
		}
		out << ") :- ";

		// print body
		sep = "";
		for(variable_t var : order)
		{
			if(clause.contains(var))
			{
				// the Datalog encoding works for DNFs, so we need
				// to invert the negation if we have a CNF
				if(clause.isNegated(var) != instance.isCnf())
					out << sep << "f(V" << var << ")";
				else
					out << sep << "t(V" << var << ")";
			}
			else
			{
				out << sep << "tf(V" << var << ")";
			}
			sep = ", ";
		}

		// print end of rule
		out << "." << endl;
	}


    void Qbf2DatalogTreeAlgorithm::printEliminationRules(
        const IQbfInstance & instance,
        vertex_t node,
        const unordered_set<variable_t> &projectOut,
        list<variable_t> &order,
        long &step) const
    {
        for (variable_t variable : projectOut) {
            if (instance.isUniversal(variable) != instance.isCnf()) {
                printSingleUniversalEliminationRule(
                    node, variable, order, step);
            } else {
                printSingleExistentialEliminationRule(
                    node, variable, order, step);
            }
        }
    }

    void Qbf2DatalogTreeAlgorithm::printSingleExistentialEliminationRule(
        vertex_t node,
        variable_t var,
        list<variable_t> &order,
        long &step) const
    {      
        ostream &out = *out_;
		ostringstream ss;

		string postfix = step ? to_string(step) : "in";

		out << "p_" << node << "_" << ++step << "("; 
		ss  << "p_" << node << "_" << postfix << "("; 

		string hsep = "", bsep = "";

		for(auto it = order.begin(); it != order.end();)
		{
			ss << bsep << "V" << *it;
			bsep = ", ";

			if(var == *it)
			{
				it = order.erase(it);
			}
			else
			{
				out << hsep << "V" << *it;
				hsep = ", ";
				++it;
			}
		}

		out << ") :- " << ss.str() << ")." << endl;
    }
    
    void Qbf2DatalogTreeAlgorithm::printSingleUniversalEliminationRule(
        vertex_t node,
        variable_t var,
        list<variable_t> &order,
        long &step) const
    {
        ostream &out = *out_;

        ostringstream ss1, ss2;
        string postfix = step ? to_string(step) : "in";

        out << "p_" << node << "_" << ++step << "("; 
        ss1 << "p_" << node << "_" << postfix << "("; 
        ss2 << "p_" << node << "_" << postfix << "("; 

        string hsep = "", bsep = "";

        for(auto it = order.begin(); it != order.end();)
        {
            ss1 << bsep << "V" << *it;
            ss2 << bsep << "V" << *it;
            bsep = ", ";

            if(var == *it)
            {
                it = order.erase(it);
                ss1 << "A";
                ss2 << "B";
            }
            else
            {
                out << hsep << "V" << *it;
                hsep = ", ";
                ++it;
            }
        }

        out << ") :- " << ss1.str() << "), " << ss2.str() << "), "
            << "t(V" << var << "A), f(V" << var << "B)." << endl;

    }

	void Qbf2DatalogTreeAlgorithm::printOutputRule(
			vertex_t node,
			long step,
			const unordered_set<variable_t> &current,
			const unordered_set<variable_t> &forgotten,
			const list<variable_t> &order) const
	{
		ostream &out = *out_;

		out << "p_" << node << "_out(";

		string sep = "";
		for(variable_t var : current)
		{
			out << sep << "V" << var;
			sep = ", ";
		}
		for(variable_t var : forgotten)
		{
			out << sep << "V" << var;
			sep = ", ";
		}

		string postfix = step ? to_string(step) : "in";
		out << ") :- p_" << node << "_" << postfix << "(";

		sep = "";
		for(variable_t var : order)
		{
			out << sep << "V" << var;
			sep = ", ";
		}

		out << ")." << endl;
	}

	void Qbf2DatalogTreeAlgorithm::printRootRules(htd::vertex_t node) const
	{
		ostream &out = *out_;
		out << ":- p_" << node << "_out()." << endl;
		out << "t(1). f(0). tf(1). tf(0)." << endl;
	}

    void Qbf2DatalogTreeAlgorithm::setDependencyOrder(
        qbf2asp::IDependencyOrder & order)
    {
        order_ = &order;
    }


} // namespace qbf2asp
