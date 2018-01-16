#include "StandardDependencyScheme.hpp"

#include <qbf2asp/DependencyScheme.hpp>

#include <logic/parsers>

#include <map>
#include <set>
#include <list>
#include <unordered_set>

namespace qbf2asp
{
    using std::map;
    using std::list;
    using std::set;
    using std::unordered_set;
    using logic::IQbfInstance;
    using logic::IQbfClause;
    using logic::variable_t;

    StandardDependencyScheme::StandardDependencyScheme(
        const IQbfInstance & formula) : scheme_(), formula_(formula)
    {
        populateScheme();
    }

    const set<logic::variable_t> &
    StandardDependencyScheme::dependingVariables(variable_t variable) const
    {
        StandardDependencyScheme * this_ptr
            = const_cast<StandardDependencyScheme *>(this);
        
        return this_ptr->scheme_[variable];
    }

    const IQbfInstance & StandardDependencyScheme::getFormula(void) const
    {
        return formula_;
    }
    
    void StandardDependencyScheme::populateScheme(void)
    {
        for (variable_t variable = 1;
             variable <= formula_.variableCount(); variable++) {
            scheme_[variable];
            lookupRightVariables(variable, formula_);
        }
    }

    void StandardDependencyScheme::expandRootVariable(
        const IQbfInstance & formula,
        variable_t root,
        list<const IQbfClause *> & working_clauses)
    {
        for (const IQbfClause & clause : formula) {
            if (clause.contains(root)) {
                working_clauses.push_back(&clause);
            }
        }
    }
    
    void StandardDependencyScheme::lookupRightVariables(
        variable_t variable, const IQbfInstance & formula)
    {
        list<variable_t> working_variables;
        list<const IQbfClause *> working_clauses;
        map<variable_t, bool> seen_variables;
        map<const IQbfClause *, bool> seen_clauses;
        set<variable_t> right_existential_variables;
        set<variable_t> right_variables;
        
        qbf2asp::rightExistentialVariables(formula, variable, right_existential_variables);
        qbf2asp::rightVariables(formula, variable, right_variables);

        expandRootVariable(formula, variable, working_clauses);

        while (!working_variables.empty() || !working_clauses.empty()) {
            if (!working_variables.empty()) {
                variable_t v = working_variables.front();
                working_variables.pop_front();
                seen_variables[v] = true;
                expandVariable(
                    formula,
                    variable,
                    v,
                    working_clauses,
                    seen_clauses,
                    right_existential_variables);
            }
            if (!working_clauses.empty()) {
                const IQbfClause * c = working_clauses.front();
                working_clauses.pop_front();
                seen_clauses[c] = true;
                expandClause(
                    *c,
                    working_variables,
                    seen_variables,
                    right_existential_variables,
                    right_variables);
            }
        }
    }

    void StandardDependencyScheme::expandClause(
        const IQbfClause & clause,
        list<variable_t> & working_variables,
        map<variable_t, bool> & seen_variables,
        const set<variable_t> & right_existential_variables,
        const set<variable_t> & right_variables)
    {
        for (variable_t v : clause) {
            if (!seen_variables[v] && right_variables.count(v) > 0)
                working_variables.push_back(v);
        }
     
    }

    void StandardDependencyScheme::expandVariable(
        const IQbfInstance & formula,
        variable_t root,
        variable_t variable,
        list<const IQbfClause*> & working_clauses,
        map<const IQbfClause*, bool> & seen_clauses,
        const set<variable_t> & right_existential_variables)
    {
        if (!qbf2asp::sameQuantifier(formula, root, variable))
        {
            scheme_[root].insert(variable);
        }
        if (right_existential_variables.count(variable) == 0) {
            return ;
        }
        for (const IQbfClause & clause : formula) {
            if (clause.contains(variable) && !seen_clauses[&clause]) {
                working_clauses.push_back(&clause);
            }
        }
    }
    
    void StandardDependencyScheme::removeVariable(variable_t variable)
    {
        scheme_.erase(variable);
        map<variable_t, set<variable_t>>::iterator it = scheme_.begin();
        while (it != scheme_.end()) {
            it->second.erase(variable);
            it++;
        }
    }
}
    
