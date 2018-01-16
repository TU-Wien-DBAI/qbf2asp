#ifndef QBF2ASP_QBF2ASP_STANDARDDEPENDENCYSCHEME_H_
#define QBF2ASP_QBF2ASP_STANDARDDEPENDENCYSCHEME_H_

#include <qbf2asp/DependencyScheme.hpp>
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

    public:
        virtual const std::set<logic::variable_t> &
            dependingVariables(logic::variable_t variable) const;

        virtual void removeVariable(logic::variable_t variable);

        virtual const logic::IQbfInstance & getFormula() const;

    private:
        std::map<logic::variable_t, std::set<logic::variable_t>> scheme_;
        const logic::IQbfInstance & formula_;

    private:
        void populateScheme(void);
        
        void lookupRightVariables(
            logic::variable_t variable, const logic::IQbfInstance & formula);
                        
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

        void expandRootVariable(
            const logic::IQbfInstance & formula,
            logic::variable_t root,
            std::list<const logic::IQbfClause *> & working_clauses);

    private:
        class DependingNodeLookup {
        public:
            DependingNodeLookup(
                const logic::IQbfInstance & formula,
                logic::variable_t origin);
            
            void lookupDependingNodes(std::set<logic::variable_t> & variables);
            
        private:
            void expandClause(const logic::IQbfClause & clause);
            void expandVariable(logic::variable_t variable);
            void expandOrigin(void);
            void expandNodes(void);
            
        private:
            const logic::IQbfInstance & formula_;
            logic::variable_t origin_;
            
            std::list<logic::variable_t> working_variables_;
            std::list<const logic::IQbfClause *> working_clauses_;
            
            std::map<logic::variable_t, bool> seen_variables_;
            std::map<const logic::IQbfClause *, bool> seen_clauses_;

            std::set<logic::variable_t> right_existential_variables_;
            std::set<logic::variable_t> right_variables_;

            std::set<logic::variable_t> depending_variables_;
        };
    };
}

#endif // QBF2ASP_QBF2ASP_STANDARDDEPENDENCYSCHEME_H_
