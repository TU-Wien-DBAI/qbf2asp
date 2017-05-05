#ifndef QBF2ASP_QBF2ASP_DECOMPOSABLEQBFINSTANCE_H_
#define QBF2ASP_QBF2ASP_DECOMPOSABLEQBFINSTANCE_H_

#include <qbf2asp/global>

#include <logic/parsers>

#include <sharp/main>

namespace sharp
{
	template class sharp::DecomposableInstance<logic::IQbfInstance>;

} // namespace sharp

namespace qbf2asp
{
	typedef sharp::DecomposableInstance<logic::IQbfInstance>
		DecomposableQbfInstance;

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_DECOMPOSABLEQBFINSTANCE_H_
