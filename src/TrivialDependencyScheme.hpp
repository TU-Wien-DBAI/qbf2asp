#ifndef QBF2ASP_QBF2ASP_TRIVIALDEPENDENCYSCHEME_H_
#define QBF2ASP_QBF2ASP_TRIVIALDEPENDENCYSCHEME_H_

#include <qbf2asp/IDependencyScheme.hpp>
#include <logic/parsers>

#include <unordered_set>
#include <map>

namespace qbf2asp
{
    class QBF2ASP_API TrivialDependencyScheme : public IDependencyScheme 
    {
    public:
        TrivialDependencyScheme(const logic::IQbfInstance & formula);
        ~TrivialDependencyScheme();
        
    public:
        virtual const std::unordered_set<logic::variable_t> &
            rightVariables(logic::variable_t variable) const ;
        
        virtual void removeVariable(logic::variable_t variable);

        virtual void show(void) const;
        
    private:
        std::map<logic::variable_t, std::unordered_set<logic::variable_t>> scheme_;

    private:
        void populateScheme(const logic::IQbfInstance & formula);
    };
}

#endif // QBF2ASP_QBF2ASP_TRIVIALDEPENDENCYSCHEME_H_
