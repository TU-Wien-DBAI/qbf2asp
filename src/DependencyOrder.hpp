#ifndef QBF2ASP_QBF2ASP_DEPENDENCYORDER_H_
#define QBF2ASP_QBF2ASP_DEPENDENCYORDER_H_

#include <qbf2asp/IDependencyOrder.hpp>
#include <qbf2asp/IDependencyScheme.hpp>

#include "StandardDependencyScheme.hpp"

#include <qbf2asp/global>
#include <logic/parsers>

#include <map>
#include <set>

namespace qbf2asp
{    
    class QBF2ASP_API DependencyOrder : public IDependencyOrder
    {
    public:
        DependencyOrder(
            const IDependencyScheme & scheme,
            const logic::IQbfInstance & formula);

        virtual void removeVariable(logic::variable_t variable);

        virtual bool isMinimal(logic::variable_t variable) const;
        
        virtual const std::set<logic::variable_t> & dependingVariables(
            logic::variable_t variable) const;

        
        virtual void minimalVariables(std::set<logic::variable_t> & variables) const;

        virtual const logic::IQbfInstance & getFormula(void) const;

        void minimalVariables(
            const std::set<logic::variable_t> & eliminated,
            std::set<logic::variable_t> & target) const;
     
    private:
        const IDependencyScheme & scheme_;
        const logic::IQbfInstance & formula_;
        std::map<logic::variable_t, std::set<logic::variable_t>> order_;

    private:
        void populateOrder(
            const logic::IQbfInstance & formula);

        void reflexiveTransitiveClosure(
            logic::variable_t variable,
            std::set<logic::variable_t> & closure) const;

        void reflexiveTransitiveClosure(
            logic::variable_t origin,
            const std::set<logic::variable_t> & eliminated,
            std::set<logic::variable_t> & closure) const;

        void push_back_all(
            std::list<logic::variable_t> & list,
            const std::set<logic::variable_t> & other) const;
    };

    class StandardDependencyOrder : public DependencyOrder
    {
      public:
        StandardDependencyOrder(const logic::IQbfInstance & formula);
    };

    class TrivialDependencyOrder : public DependencyOrder
    {
      public:
        TrivialDependencyOrder(const logic::IQbfInstance & formula);
    };

}

#endif // QBF2ASP_QBF2ASP_STANDARDDEPENDENCYORDER_H_
