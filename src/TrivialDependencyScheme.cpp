#include "TrivialDependencyScheme.hpp"

#include <logic/parsers>

#include <set>
#include <map>
#include <unordered_set>

namespace qbf2asp
{
    using std::map;
    using std::set;
    using std::unordered_set;
    
    using logic::IQbfInstance;
    using logic::variable_t;
    
    TrivialDependencyScheme::TrivialDependencyScheme(
        const IQbfInstance & formula) : scheme_(), formula_(formula)
    {
        populateScheme();
    }

    const set<variable_t> & TrivialDependencyScheme::dependingVariables(
        variable_t variable) const
    {
        TrivialDependencyScheme * this_ptr
            = const_cast<TrivialDependencyScheme*>(this);
        
        return this_ptr->scheme_[variable];
    }

    void TrivialDependencyScheme::removeVariable(variable_t variable)
    {
        scheme_.erase(variable);
        map<variable_t, set<variable_t>>::iterator it = scheme_.begin();
        while (it != scheme_.end()) {
            it->second.erase(variable);
            it++;
        }
    }

    const IQbfInstance & TrivialDependencyScheme::getFormula(void) const
    {
        return formula_;
    }

    void TrivialDependencyScheme::populateScheme(void)
    {
        for (variable_t variable = 1;
             variable <= formula_.variableCount(); variable++) {
            scheme_[variable]; // create empty set of right variables
            for (unsigned short level = formula_.quantifierLevel(variable) + 1;
                 level <= formula_.innermostQuantifierLevel(); level++) {
                const unordered_set<variable_t> & variables
                    = formula_.variables(level);
                scheme_[variable].insert(variables.begin(), variables.end());
            }
        }
    }
}
