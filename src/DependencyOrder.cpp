
#include "DependencyOrder.hpp"
#include "StandardDependencyScheme.hpp"
#include "TrivialDependencyScheme.hpp"

#include <qbf2asp/IDependencyScheme.hpp>

#include <logic/parsers>

#include <map>
#include <set>
#include <list>
#include <ostream>

namespace qbf2asp
{
    using std::list;
    using std::set;
    using std::map;
    using std::ostream;
    
    using logic::variable_t;
    using logic::IQbfInstance;

    DependencyOrder::DependencyOrder(
        const IDependencyScheme & scheme,
        const IQbfInstance & formula) : scheme_(scheme), formula_(formula), order_()
    {
        populateOrder(formula);
    }
                                                       
    const set<variable_t> & DependencyOrder::dependingVariables(
        variable_t variable) const
    {
        DependencyOrder * this_ptr = const_cast<DependencyOrder *>(this);
        
        return this_ptr->order_[variable];
    }

    void DependencyOrder::populateOrder(
        const IQbfInstance & formula)
    {
        for (variable_t variable = 1;
             variable <= formula.variableCount();
             variable++) {
            reflexiveTransitiveClosure(variable, order_[variable]);
        }
    }

    void DependencyOrder::push_back_all(
        list<variable_t> & list, const set<variable_t> & other) const
    {
        for (variable_t variable : other) {
            list.push_back(variable);
        }
    }

    void DependencyOrder::removeVariable(
        variable_t variable)
    {
        throw "not implemented";
    }

    bool DependencyOrder::isMinimal(
        variable_t variable) const
    {
        throw "not implemented";
    }

    void DependencyOrder::minimalVariables(
        set<variable_t> & minimal) const
    {
        set<variable_t> eliminated;
        minimalVariables(eliminated, minimal);
    }

    void DependencyOrder::minimalVariables(
        const set<variable_t> & eliminated,
        set<variable_t> & target) const
    {
        for ( variable_t variable = 1; variable <= formula_.variableCount(); variable++)
        {
            set<variable_t> closure;
            reflexiveTransitiveClosure(variable, eliminated, closure);
            if (closure.size() == 1) {
                target.insert(variable);
            }
        }
    }

    void DependencyOrder::reflexiveTransitiveClosure(
        variable_t origin,
        set<variable_t> & closure) const
    {
        set<variable_t> eliminated;
        reflexiveTransitiveClosure(origin, eliminated, closure);
    }

    void DependencyOrder::reflexiveTransitiveClosure(
        variable_t origin,
        const set<variable_t> & eliminated,
        set<variable_t> & closure) const
    {
        list<variable_t> queue;

        queue.push_back(origin);

        while (!queue.empty()) {
            variable_t current = queue.front();
            queue.pop_front();
            if (eliminated.count(current) == 0) {
                closure.insert(current);
                push_back_all(queue, scheme_.dependingVariables(current));
            }
        }
    }

    const IQbfInstance & DependencyOrder::getFormula(void) const
    {
        return formula_;
    }

    void showDependencyOrder(
        ostream & out,
        const IDependencyOrder & dependencyOrder)
    {
        const IQbfInstance & formula = dependencyOrder.getFormula();

        out << "Dependency Order" << std::endl;
        
        for (variable_t variable = 1; variable <= formula.variableCount(); variable++) {
            out << variable << " :";
            for (variable_t depending : dependencyOrder.dependingVariables(variable)) {
                out << " " << depending;
            }
            out << std::endl;
        }
    }

    StandardDependencyOrder::StandardDependencyOrder(
        const IQbfInstance & formula) :
        DependencyOrder(*(new StandardDependencyScheme(formula)), formula) {}

    TrivialDependencyOrder::TrivialDependencyOrder(
        const IQbfInstance & formula) :
        DependencyOrder(*(new TrivialDependencyScheme(formula)), formula) {}
}
