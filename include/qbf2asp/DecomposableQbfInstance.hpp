#ifndef QBF2ASP_QBF2ASP_DECOMPOSABLEQBFINSTANCE_H_
#define QBF2ASP_QBF2ASP_DECOMPOSABLEQBFINSTANCE_H_

#include <qbf2asp/global>

#include <logic/parsers>

#include <sharp/main>

namespace qbf2asp
{
	template<>
	using DecomposableQbfInstance = 
		sharp::DecomposableInstance<logic::IQbfInstance>;

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_DECOMPOSABLEQBFINSTANCE_H_
