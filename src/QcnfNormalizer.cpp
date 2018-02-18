#include "./preamble.h"

#include "QcnfNormalizer.hpp"
#include <logic/ProceduralQbfInstanceBuilder.hpp>

#include <logic/parsers>

#include <set>
#include <utility>
#include <list>

namespace qbf2asp
{
    using logic::variable_t;
    using logic::IQbfInstance;
    using logic::IQbfClause;
    using logic::IQbfInstanceBuilder;
    using logic::ProceduralQbfInstanceBuilder;
    using logic::ProceduralQbfClauseBuilder;

    using std::cout;
    using std::endl;
    using std::pair;
    using std::list;
    using std::set;

    QbfLiteral::QbfLiteral(variable_t variable, bool polarity)
    {
	this->variable_ = variable;
	this->polarity_ = polarity;
    }

    variable_t QbfLiteral::variable(void) const
    {
	return this->variable_;
    }

    bool QbfLiteral::polarity(void) const
    {
	return this->polarity_;
    }

    bool QbfLiteral::operator==(const QbfLiteral & other)
    {
	return this->variable() == other.variable() && this->polarity() == other.polarity();
    }

    bool QbfLiteral::operator<(const QbfLiteral & other)
    {
	return this->polarity() < other.polarity() || this->variable() < other.variable();
    }

    bool operator<(QbfLiteral that, QbfLiteral other)
    {
	return that.operator<(other);
    }

    QcnfNormalizer::QcnfNormalizer(unsigned int maxClauseSize) {
	this->maxClauseSize_ = maxClauseSize;
    }

    unsigned int QcnfNormalizer::maxClauseSize() const
    {
	return this->maxClauseSize_;
    }
  
    list<list<QbfLiteral> *> * QcnfNormalizer::normalizeClause(
	const IQbfClause & clause, set<variable_t> * variables,
	VariableGenerator variableGenerator, const IQbfInstance & instance)
    {
    
	list<QbfLiteral> * workingLiterals = clauseToLiteralList(clause);
	list<list<QbfLiteral> *> * newClauses = new list<list<QbfLiteral> *>();
    
	while (workingLiterals->size() > maxClauseSize_) {
	    pair<list<QbfLiteral> *, list<QbfLiteral> *> partition
		= this->partitionClause(workingLiterals, instance);
      
	    variable_t splitVariable = variableGenerator.freshVariable();
      
	    variables->insert(splitVariable);
	    partition.first->push_back(QbfLiteral(splitVariable, false));
	    partition.second->push_back(QbfLiteral(splitVariable, true));
      
	    delete workingLiterals;

	    newClauses->push_back(partition.first);
	    workingLiterals = partition.second;
	}
	newClauses->push_back(workingLiterals);
	return newClauses;
    }
  
    const IQbfInstance * QcnfNormalizer::normalize(const IQbfInstance & instance)
    {
	VariableGenerator variableGenerator(&instance);
	set<variable_t> splitVariables = set<variable_t>();
	list<list<QbfLiteral> *> newClauses = list<list<QbfLiteral> *>();
    
	for (const IQbfClause & clause : instance) {
	    list<list<QbfLiteral> *> * clauses = normalizeClause(
		clause, &splitVariables, variableGenerator, instance);
	    for (auto literalList : *clauses) {
		newClauses.push_back(literalList);
	    }
	    delete clauses;
	}
    
	const IQbfInstance * normalInstance = buildQbfInstance(
	    &newClauses, &splitVariables, instance);

	// free allocated objects
	for (auto literalList : newClauses) {
	    delete literalList;
	}
    
	return normalInstance;
    }
  
    VariableGenerator::VariableGenerator(const IQbfInstance * instance) {
        this->instance = instance;
        variableCounter = 1;
        for (const IQbfClause & clause : *instance) {
            for (const variable_t variable : clause) {
                variableCounter =
                    (variableCounter <= variable) ? (variable + 1) : variableCounter;
            }
        }
    }

    variable_t VariableGenerator::freshVariable() {
	return variableCounter++;
    }

    NaiveQcnfNormalizer::NaiveQcnfNormalizer(unsigned int maxClauseSize) : QcnfNormalizer(maxClauseSize) {}

    pair<list<QbfLiteral> *, list<QbfLiteral> *> NaiveQcnfNormalizer::partitionClause(
	list<QbfLiteral> * literals, const IQbfInstance & instance)
    {
	pair<list<QbfLiteral> *, list<QbfLiteral> *> result;
	result.first  = new list<QbfLiteral>();
	result.second = new list<QbfLiteral>();
	unsigned int literalCount = 0;
	for (QbfLiteral literal : *literals) {
	    if (literalCount < this->maxClauseSize() - 1) {
		result.first->push_back(literal);
		literalCount++;
	    } else {
		result.second->push_back(literal);
	    }
	}
	return result;
    }

    list<QbfLiteral> * clauseToLiteralList(const IQbfClause & clause)
    {
	list<QbfLiteral> * literals = new list<QbfLiteral>();
	for (variable_t variable : clause) {
	    literals->push_back(QbfLiteral(variable, clause.isNegated(variable)));
	}
	return literals;
    }

    
    void copyLiteralListToClause(
        list<QbfLiteral> * literals,
        ProceduralQbfClauseBuilder & clauseBuilder)
    {
	for (auto literal : *literals) {
	    clauseBuilder.addLiteral(literal.variable(), literal.polarity());
	}
    }

    const IQbfInstance * buildQbfInstance(
	const list<list<QbfLiteral>*> * newClauses,
	const set<variable_t> * splitVariables,
	const IQbfInstance & instance)
    {
	ProceduralQbfInstanceBuilder * instanceBuilder = logic::parser::qbfInstanceBuilder();

    if (instance.isCnf()) {
        instanceBuilder->setCnf();
    } else {
        instanceBuilder->setDnf();
    }
    
//	instanceBuilder->setVariableCount(instance.variableCount() + splitVariables->size());

	for (auto literalList : *newClauses) {
	    copyLiteralListToClause(literalList, instanceBuilder->addClause());
	}
	for (variable_t variable = 1; variable <= instance.variableCount(); variable++) {
	    instanceBuilder->setQuantifierLevel(variable, instance.quantifierLevel(variable));
	}
	for (variable_t variable : *splitVariables) {
	    instanceBuilder->setQuantifierLevel(variable, instance.innermostQuantifierLevel());
	}
	// todo: free the instance builder if this is possible.
	return instanceBuilder->toInstance();
    }

    unsigned int clauseCount(const IQbfInstance & instance)
    {
	return std::distance(instance.begin(), instance.end());
    }
  
    void print_qbf_qdimacs(
        std::ostream & out,
        const IQbfInstance & instance)
    {
        // print problem line
        out << "p" << " "
            << (instance.isCnf() ? "cnf" : "dnf") << " "
            << instance.variableCount() << " "
            << clauseCount(instance) << endl;
    
        // print quantifier lines
        for (int currentQuantifierLevel = 0;
             currentQuantifierLevel <= instance.innermostQuantifierLevel();
             currentQuantifierLevel++) {
            bool primalQuantifier =
                (currentQuantifierLevel + instance.innermostQuantifierLevel()) % 2 == 0;
            if (primalQuantifier) {
                out << (instance.isCnf() ? "e" : "a");
            } else {
                out << (instance.isCnf() ? "a" : "e");
            }
            out << " ";

            for (variable_t variable : instance.variables(currentQuantifierLevel)) {
                out << variable << " ";
            }
            out << "0" << endl;
        }

        // print clause lines
        for (const IQbfClause & clause : instance) {
            for (variable_t variable : clause) {
                out << (clause.isNegated(variable) ? "-" : "") << variable << " ";
            }
            out << "0" << endl;
        }
    }
}
