#include "TrivialDependencyScheme.hpp"

#include <logic/parsers>

#include <map>

namespace qbf2asp
{
    using std::map;
    using std::unordered_set;
    using logic::IQbfInstance;
    using logic::variable_t;
    
    TrivialDependencyScheme::TrivialDependencyScheme(const IQbfInstance & formula) : scheme_()
    {
        populateScheme(formula);
    }

    void TrivialDependencyScheme::populateScheme(const IQbfInstance & formula)
    {
        for (variable_t variable = 1; variable <= formula.variableCount(); variable++) {
            scheme_[variable]; // create empty set of right variables
            for (unsigned short level = formula.quantifierLevel(variable) + 1;
                 level <= formula.innermostQuantifierLevel(); level++) {
                const unordered_set<variable_t> & variables = formula.variables(level);
                scheme_[variable].insert(variables.begin(), variables.end());
            }
        }
    }

    const unordered_set<variable_t> & TrivialDependencyScheme::rightVariables(
        variable_t variable) const
    {
        TrivialDependencyScheme * this_ptr = const_cast<TrivialDependencyScheme*>(this);
        return this_ptr->scheme_[variable];
    }

    void TrivialDependencyScheme::removeVariable(variable_t variable)
    {
        scheme_.erase(variable);
        map<variable_t, unordered_set<variable_t>>::iterator it = scheme_.begin();
        while (it != scheme_.end()) {
            it->second.erase(variable);
            it++;
        }
    }

    void TrivialDependencyScheme::show(void) const
    {
        std::cout << "Trivial Dependency Scheme";
        for (auto pair : scheme_) {
            std::cout << std::endl << pair.first << " :";
            for (variable_t variable : pair.second) {
                std::cout << " " << variable;
            }
        }
        std::cout << std::endl;
    }
}
