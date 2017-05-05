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

		for(size_t vertex = 1;  vertex <= instance.variableCount(); ++vertex)
			hypergraph->addVertex();

		clause_t clause = instance.variableCount + 1;
		for(const IQbfClause &clause : instance)
		{
			vector<vertex_t> edge;
			edge.push_back(clause++);

			for(variable_t variable : clause)
				edge.push_back(variable);

			DBG("edge: "); DBG_COLL(edge); DBG(std::endl);

			hypergraph->addEdge(edge);
		}

		return hypergraph;
	}
} // namespace qbf2asp