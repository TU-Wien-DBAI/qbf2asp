#include "../preamble.h"
#include "QbfToPrimalHypergraphConverter.hpp"

#include <qbf2asp/create.hpp>

#include <vector>
#include <typeinfo>
#include <stdexcept>

namespace qbf2asp
{
	using htd::vertex_t;
	using htd::IHypergraph;
	using htd::IMutableHypergraph;
	using htd::HypergraphFactory;

	using std::vector;

	QbfToPrimalHypergraphConverter::QbfToPrimalHypergraphConverter() { }

	QbfToPrimalHypergraphConverter::~QbfToPrimalHypergraphConverter() { }

	IHypergraph *QbfToPrimalHypergraphConverter::convert(
			const IQbfInstance &instance) const
	{
		IMutableHypergraph *hypergraph = 
			create::htdlib().hypergraphFactory().createInstance();

		for(size_t vertex = instance.getVariableCount(); vertex > 0; --vertex)
			hypergraph->addVertex();

		for(const IQbfClause &clause : instance)
		{
			vector<vertex_t> edge;

			for(variable_t variable : clause)
				edge.push_back(variable);

			DBG("edge: "); DBG_COLL(edge); DBG(std::endl);

			hypergraph->addEdge(edge);
		}

		return hypergraph;
	}
} // namespace qbf2asp
