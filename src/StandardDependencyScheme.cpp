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
            DependingNodeLookup lookup(formula_, variable);
            set<variable_t> dependingVariables;
            lookup.lookupDependingNodes(dependingVariables);
            scheme_[variable].insert(
                dependingVariables.begin(), dependingVariables.end());
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

    StandardDependencyScheme::DependingNodeLookup::DependingNodeLookup(
        const IQbfInstance & formula, variable_t origin) : formula_(formula), origin_(origin)
    {
        qbf2asp::rightVariables(
            formula_, origin_, right_variables_);
        qbf2asp::rightExistentialVariables(
            formula_, origin_, right_existential_variables_);
    }

    void StandardDependencyScheme::DependingNodeLookup::expandOrigin(void)
    {
        for (const IQbfClause & clause : formula_) {
            if (clause.contains(origin_)) {
                working_clauses_.push_back(&clause);
            }
        }
    }

    void StandardDependencyScheme::DependingNodeLookup::expandVariable(
        variable_t variable)
    {
        if (!qbf2asp::sameQuantifier(formula_, origin_, variable))
        {
            depending_variables_.insert(variable);
        }
        if (right_existential_variables_.count(variable) == 0) {
            return ;
        }
        for (const IQbfClause & clause : formula_) {
            if (clause.contains(variable) && !seen_clauses_[&clause]) {
                working_clauses_.push_back(&clause);
            }
        }
    }

    void StandardDependencyScheme::DependingNodeLookup::expandClause(
        const IQbfClause & clause)
    {
        for (variable_t v : clause) {
            if (!seen_variables_[v] && right_variables_.count(v) > 0)
                working_variables_.push_back(v);
        }
    }

    void StandardDependencyScheme::DependingNodeLookup::lookupDependingNodes(
        set<variable_t> & variables)
    {
        expandNodes();
        variables.insert(depending_variables_.begin(), depending_variables_.end());
    }

    void StandardDependencyScheme::DependingNodeLookup::expandNodes(void)
    {
        expandOrigin();

        while (!working_variables_.empty() || !working_clauses_.empty()) {
            if (!working_variables_.empty()) {
                variable_t v = working_variables_.front();
                working_variables_.pop_front();
                seen_variables_[v] = true;
                expandVariable(v);
            }
            if (!working_clauses_.empty()) {
                const IQbfClause * c = working_clauses_.front();
                working_clauses_.pop_front();
                seen_clauses_[c] = true;
                expandClause(*c);

            }
        }

    }
}
    
