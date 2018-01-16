#include <qbf2asp/DependencyScheme.hpp>

#include <logic/parsers>

#include <ostream>


namespace qbf2asp
{
    using std::ostream;
    using std::set;
    using std::endl;
    
    using logic::variable_t;
    using logic::IQbfInstance;
    
    QBF2ASP_API void showDependencyScheme(
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
}
