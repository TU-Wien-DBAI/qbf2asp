
#include "StandardDependencyOrder.hpp"

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

    StandardDependencyOrder::StandardDependencyOrder(
        const IQbfInstance & formula) : scheme_(formula), formula_(formula), order_()
    {
        populateOrder(formula);
    }
                                                       
    const set<variable_t> & StandardDependencyOrder::dependingVariables(
        variable_t variable) const
    {
        StandardDependencyOrder * this_ptr = const_cast<StandardDependencyOrder *>(this);
        
        return this_ptr->order_[variable];
    }

    void StandardDependencyOrder::populateOrder(
        const IQbfInstance & formula)
    {
        for (variable_t variable = 1;
             variable <= formula.variableCount();
             variable++) {
            reflexiveTransitiveClosure(variable, order_[variable]);
        }
    }

    void StandardDependencyOrder::push_back_all(
        list<variable_t> & list, const set<variable_t> & other) const
    {
        for (variable_t variable : other) {
            list.push_back(variable);
        }
    }

    void StandardDependencyOrder::removeVariable(
        variable_t variable)
    {
        throw "not implemented";
    }

    bool StandardDependencyOrder::isMinimal(
        variable_t variable) const
    {
        throw "not implemented";
    }

    void StandardDependencyOrder::minimalVariables(
        set<variable_t> & minimal) const
    {
        set<variable_t> eliminated;
        minimalVariables(eliminated, minimal);
    }

    void StandardDependencyOrder::minimalVariables(
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

    void StandardDependencyOrder::reflexiveTransitiveClosure(
        variable_t origin,
        set<variable_t> & closure) const
    {
        set<variable_t> eliminated;
        reflexiveTransitiveClosure(origin, eliminated, closure);
    }

    void StandardDependencyOrder::reflexiveTransitiveClosure(
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

    const IQbfInstance & StandardDependencyOrder::getFormula(void) const
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
}
