/**
 * @file
 */

#ifndef QBF2ASP_QBF2ASP_IDEPENDENCYORDER_H_
#define QBF2ASP_QBF2ASP_IDEPENDENCYORDER_H_

#include <qbf2asp/global>
#include <logic/parsers>

#include <set>
#include <ostream>

namespace qbf2asp
{
    /**
     * @brief Interface for dependency orders.
     * A dependency order is the reflexive and transitive closure of
     * the components of a dependency scheme. Depending on the type
     * and the implementation of a dependency scheme computing this
     * closure may be more or less costly. This interface is
     * intended to abstract the implementation of this closure.
     */
    class QBF2ASP_API IDependencyOrder
    {
    public:

        /**
         * @brief Retrives dependend variables.
         * @param variable The variable for which the dependend
         * variables are looked up.
         * @return The set of variables that depend on the given
         * variable.
         */
        virtual const std::set<logic::variable_t> & dependingVariables(
            logic::variable_t variable) const = 0;

        /**
         * @brief Retrieves the minimal variables.
         * @param variables The minimal variables are stored in this
         * list.
         */
        virtual void minimalVariables(std::set<logic::variable_t> & variables) const = 0;

        /**
         * @brief Retrieves the minimal variables.
         * @param eliminated These variables are considered not to
         * belong to the ordering.
         * @param target A set into which the minimal variables will be
         * stored.
         */
        virtual void minimalVariables(
            const std::set<logic::variable_t> & eliminated,
            std::set<logic::variable_t> & target) const = 0;

        virtual const logic::IQbfInstance & getFormula(void) const = 0;
    };

    /**
     * @brief Prints a dependency order.
     * @param out The dependency order is printed to this stream.
     * @param dependencyOrder The dependency order that is printed.
     */
    void QBF2ASP_API showDependencyOrder(
        std::ostream & out,
        const IDependencyOrder & dependencyOrder);

}

#endif // QBF2ASP_QBF2ASP_IDEPENDENCYORDER_H_
