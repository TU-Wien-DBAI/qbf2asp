#ifndef QBF2ASP_QBF2ASP_TRIVIALDEPENDENCYSCHEME_H_
#define QBF2ASP_QBF2ASP_TRIVIALDEPENDENCYSCHEME_H_

#include <qbf2asp/DependencyScheme.hpp>
#include <logic/parsers>

#include <set>
#include <map>

namespace qbf2asp
{
    class QBF2ASP_API TrivialDependencyScheme : public IDependencyScheme 
    {
    public:
        TrivialDependencyScheme(const logic::IQbfInstance & formula);
        ~TrivialDependencyScheme();
        
    public:
        virtual const std::set<logic::variable_t> &
            dependingVariables(logic::variable_t variable) const ;
        
        virtual void removeVariable(logic::variable_t variable);

        virtual const logic::IQbfInstance & getFormula(void) const;
        
    private:
        std::map<logic::variable_t, std::set<logic::variable_t>> scheme_;
        const logic::IQbfInstance & formula_;

    private:
        void populateScheme(void);
    };
}

#endif // QBF2ASP_QBF2ASP_TRIVIALDEPENDENCYSCHEME_H_
