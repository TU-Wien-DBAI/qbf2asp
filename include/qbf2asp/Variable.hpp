#ifndef QBF2ASP_QBF2ASP_VARIABLE_H_
#define QBF2ASP_QBF2ASP_VARIABLE_H_

#include <qbf2asp/global>

#include <htd/main.hpp>

#include <vector>

namespace qbf2asp
{
	typedef htd::vertex_t variable_t;
	typedef std::vector<variable_t> variable_vector;

	struct Variable
	{
	private:
		Variable();
	};


} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_VARIABLE_H_
