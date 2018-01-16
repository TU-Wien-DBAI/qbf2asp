#include <qbf2asp/DependencyScheme.hpp>

#include <logic/parsers>

#include <ostream>
#include <set>
#include <unordered_set>

namespace qbf2asp
{
    using std::ostream;
    using std::set;
    using std::endl;
    using std::unordered_set;
    
    using logic::variable_t;
    using logic::IQbfInstance;
    
    void showDependencyScheme(
        ostream & out,
        const IDependencyScheme & dependencyScheme)
    {
        const IQbfInstance & formula = dependencyScheme.getFormula();
        out << "Dependency Scheme";
        for (variable_t variable = 1; variable <= formula.variableCount(); variable++) {
            const set<variable_t> & dependingVariables
                = dependencyScheme.dependingVariables(variable);
            out << endl << variable << " :";
            for (variable_t depending : dependingVariables) {
                out << " " << depending;
            }
        }
        out << endl;
    }

    bool sameQuantifier(
        const IQbfInstance & formula, variable_t v1, variable_t v2)
    {
        return formula.quantifierLevel(v1) % 2 == formula.quantifierLevel(v2) % 2;
    }

    void rightVariables(
        const IQbfInstance & formula,
        variable_t variable,
        set<variable_t> & variables)
    {
        for (int quantifierLevel = formula.quantifierLevel(variable) + 1;
             quantifierLevel <= formula.innermostQuantifierLevel();
             quantifierLevel++) {
            const unordered_set<variable_t> & levelVariables
                = formula.variables(quantifierLevel);
            variables.insert(levelVariables.begin(), levelVariables.end());
        }
    }

    void rightExistentialVariables(
        const IQbfInstance & formula,
        variable_t variable,
        set<variable_t> & variables)
    {
        set<variable_t> right_variables;
        rightVariables(formula, variable, right_variables);
        for (variable_t v : right_variables) {
            if (isExistentialLevel(formula.quantifierLevel(v), formula)) {
                variables.insert(v);
            }
        }
    }

    bool isExistentialLevel(
        unsigned short level, const IQbfInstance & formula)
    {
        return formula.isCnf()
            && level % 2 == formula.innermostQuantifierLevel() % 2;
    }
}
