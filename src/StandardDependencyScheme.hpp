#ifndef QBF2ASP_QBF2ASP_STANDARDDEPENDENCYSCHEME_H_
#define QBF2ASP_QBF2ASP_STANDARDDEPENDENCYSCHEME_H_

#include <qbf2asp/IDependencyScheme.hpp>
#include <logic/parsers>

#include <map>
#include <set>
#include <list>

namespace qbf2asp
{
    class QBF2ASP_API StandardDependencyScheme : public IDependencyScheme
    {
    public:
        StandardDependencyScheme(const logic::IQbfInstance & formula);
        ~StandardDependencyScheme();

    public:
        virtual const std::unordered_set<logic::variable_t> &
            rightVariables(logic::variable_t variable) const;

        virtual void removeVariable(logic::variable_t variable);

        virtual void show(void) const;

    private:
        std::map<logic::variable_t, std::unordered_set<logic::variable_t>> scheme_;

    private:
        void populateScheme(const logic::IQbfInstance & formula);
        
        void lookupRightVariables(
            logic::variable_t variable, const logic::IQbfInstance & formula);
        
        void rightExistentialVariables(
            const logic::IQbfInstance & formula,
            logic::variable_t variable,
            std::set<logic::variable_t> & variables);
        
        bool isExistentialLevel(
            unsigned short level, const logic::IQbfInstance & formula);
        
        bool sameQuantifier(const logic::IQbfInstance & formula,
                            logic::variable_t v1, logic::variable_t v2);
        
        void expandClause(
            const logic::IQbfClause & clause,
            std::list<logic::variable_t> & working_variables,
            std::map<logic::variable_t, bool> & seen_variables,
            const std::set<logic::variable_t> & right_existential_variables,
            const std::set<logic::variable_t> & right_variables);

        void expandVariable(
            const logic::IQbfInstance & formula,
            logic::variable_t root,
            logic::variable_t variable,
            std::list<const logic::IQbfClause *> & working_clauses,
            std::map<const logic::IQbfClause *, bool> & seen_clauses,
            const std::set<logic::variable_t> & right_existential_variables);

        void rightVariablesOf(
            const logic::IQbfInstance & formula,
            logic::variable_t variable,
            std::set<logic::variable_t> & variables);

        void expandRootVariable(
            const logic::IQbfInstance & formula,
            logic::variable_t root,
            std::list<const logic::IQbfClause *> & working_clauses);



    };
}

#endif // QBF2ASP_QBF2ASP_STANDARDDEPENDENCYSCHEME_H_
