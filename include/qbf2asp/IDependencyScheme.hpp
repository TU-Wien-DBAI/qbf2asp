#ifndef QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_
#define QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_

#include <qbf2asp/global>
#include <logic/parsers>

#include <unordered_set>

namespace qbf2asp
{
    class QBF2ASP_API IDependencyScheme
    {
    public:
        virtual const std::unordered_set<logic::variable_t> &
            rightVariables(logic::variable_t variable) const = 0;
        
        virtual void removeVariable(logic::variable_t variable) = 0;
    };
}

#endif // QBF2ASP_QBF2ASP_IDEPENDENCYSCHEME_H_
