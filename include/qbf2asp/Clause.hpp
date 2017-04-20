#ifndef QBF2ASP_QBF2ASP_CLAUSE_H_
#define QBF2ASP_QBF2ASP_CLAUSE_H_

#include <asp2qbf/global>

#include <htd/main.hpp>

#include <vector>

namespace asp2qbf
{
	typedef htd::vertex_t clause_t;
	typedef std::vector<clause_t> clause_vector;

	struct Clause
	{
	private:
		Clause();
	};

} // namespace asp2qbf

#endif // QBF2ASP_QBF2ASP_CLAUSE_H_
