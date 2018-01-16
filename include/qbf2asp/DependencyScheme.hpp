/** 
 * @file
 */

#ifndef QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_
#define QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_

#include <qbf2asp/global>
#include <logic/parsers>

#include <set>

/** 
 * @namespace 
 */
namespace qbf2asp
{
    /** 
     * @class IDependencyScheme
     * @brief Interface for dependency schemes.
     */
    class QBF2ASP_API IDependencyScheme
    {
    public:
        /**
         * @brief Computes the set of dependend variables.
         * @param variable The variable for which the dependend
         * variables are computed.
         * @return A reference to a set containing all variables that
         * depend on the given variable.
         */
        virtual const std::set<logic::variable_t> &
            dependingVariables(logic::variable_t variable) const = 0;

        /**
         * @brief Returns the formula associated to this dependency
         * scheme.
         * @return A formula.
         */
        virtual const logic::IQbfInstance & getFormula() const = 0;
    };

    /**
     * @brief Prints a dependency scheme.
     * @param out The stream to which the dependency scheme is
     * printed.
     * @param dependencyScheme The dependency scheme that is printed.
     */
    QBF2ASP_API void showDependencyScheme(
        std::ostream & out,
        const IDependencyScheme & dependencyScheme);

    /**
     * @brief Retrieves the variables that are to right of the given
     * variable in the quantifier prefix.
     * This excludes variables that are in the same quantifier block.
     * @param formula The formula with respect to which the right
     * variables are looked up.
     * @param variable The variable for which the right variables are
     * looked up.
     * @param variables The right variables are stored into this set.
     */
    QBF2ASP_API void rightVariables(
        const logic::IQbfInstance & formula,
        logic::variable_t variable,
        std::set<logic::variable_t> & variables);

    /**
     * @brief Looks up right variables that are existentially
     * quantified.
     * This function looks up all existentially quantified variables
     * that are to the right of the given variable in the quantifier
     * prefix of the given formula. Variables of the same quantifier
     * level as the given variable are ignored.
     * @param formula The formula with respect to which the right
     * variables are looked up.
     * @param variable The variable for which the right variables are
     * looked up.
     * @param variables The looked up variables are stored in this set.
     */
    QBF2ASP_API void rightExistentialVariables(
        const logic::IQbfInstance & formula,
        logic::variable_t variable,
        std::set<logic::variable_t> & variables);

    /**
     * @brief Tests whether a quantifier level is existential.
     * @param level The quantifier level to check.
     * @param formula The formula with respect to which the level is
     * checked.
     * @return Returns `true` if the level is an existential level,
     * `false` otherwise.
     */
    QBF2ASP_API bool isExistentialLevel(
        unsigned short level, const logic::IQbfInstance & formula);

    /**
     * @brief Tests whether two variables are bound by the same type
     * of quantifier.
     * @param formula The formula with respect to which the variables
     * are tested.
     * @param v1 A variable.
     * @param v2 A variable.
     * @return Returns `true` if v1 and v2 are bound in formula by the
     * same type of quantifier, `false` otherwise.
     */
    QBF2ASP_API bool sameQuantifier(
        const logic::IQbfInstance & formula,
        logic::variable_t v1, logic::variable_t v2);


}

#endif // QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_
