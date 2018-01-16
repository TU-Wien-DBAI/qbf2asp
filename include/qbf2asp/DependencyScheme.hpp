#ifndef QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_
#define QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_

#include <qbf2asp/global>
#include <logic/parsers>

#include <set>

namespace qbf2asp
{
    class QBF2ASP_API IDependencyScheme
    {
    public:
        virtual const std::set<logic::variable_t> &
            dependingVariables(logic::variable_t variable) const = 0;

        virtual const logic::IQbfInstance & getFormula() const = 0;
        
        virtual void removeVariable(logic::variable_t variable) = 0;
    };

    QBF2ASP_API void showDependencyScheme(
        std::ostream & out,
        const IDependencyScheme & dependencyScheme);

    QBF2ASP_API void rightVariables(
        const logic::IQbfInstance & formula,
        logic::variable_t variable,
        std::set<logic::variable_t> & variables);

    QBF2ASP_API void rightExistentialVariables(
        const logic::IQbfInstance & formula,
        logic::variable_t variable,
        std::set<logic::variable_t> & variables);

    QBF2ASP_API bool isExistentialLevel(
        unsigned short level, const logic::IQbfInstance & formula);
        
    QBF2ASP_API bool sameQuantifier(
        const logic::IQbfInstance & formula,
        logic::variable_t v1, logic::variable_t v2);


}

#endif // QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_
