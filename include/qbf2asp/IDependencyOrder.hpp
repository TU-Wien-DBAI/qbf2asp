#ifndef QBF2ASP_QBF2ASP_IDEPENDENCYORDER_H_
#define QBF2ASP_QBF2ASP_IDEPENDENCYORDER_H_

#include <qbf2asp/global>
#include <logic/parsers>

#include <set>
#include <ostream>

namespace qbf2asp
{
    class QBF2ASP_API IDependencyOrder
    {
    public:
        virtual const std::set<logic::variable_t> & dependingVariables(
            logic::variable_t variable) const = 0;
        
        virtual void removeVariable(logic::variable_t variable) = 0;

        virtual bool isMinimal(logic::variable_t variable) const = 0;
        
        virtual void minimalVariables(std::set<logic::variable_t> & variables) const = 0;

        virtual void minimalVariables(
            const std::set<logic::variable_t> & eliminated,
            std::set<logic::variable_t> & target) const = 0;

        virtual const logic::IQbfInstance & getFormula(void) const = 0;
    };

    void QBF2ASP_API showDependencyOrder(
        std::ostream & out,
        const IDependencyOrder & dependencyOrder);

}

#endif // QBF2ASP_QBF2ASP_IDEPENDENCYORDER_H_
