#ifndef QBF2ASP_QBF2ASP_CLAUSE_H_
#define QBF2ASP_QBF2ASP_CLAUSE_H_

#include <qbf2asp/global>

#include <htd/main.hpp>

#include <vector>

namespace qbf2asp
{
	typedef htd::vertex_t clause_t;
	typedef std::vector<clause_t> clause_vector;

	struct Clause
	{
	private:
		Clause();
	};

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_CLAUSE_H_
