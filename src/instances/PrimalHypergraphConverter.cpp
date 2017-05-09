#include "../preamble.h"
#include "PrimalHypergraphConverter.hpp"

#include <qbf2asp/create.hpp>

#include <vector>
#include <typeinfo>
#include <stdexcept>

namespace qbf2asp
{
	using logic::IQbfInstance;
	using logic::IQbfClause;
	using logic::variable_t;
	using logic::clause_t;

	using htd::id_t;
	using htd::vertex_t;
	using htd::IMultiHypergraph;
	using htd::IMutableMultiHypergraph;

	using std::vector;
	using std::unique_ptr;

	PrimalHypergraphConverter::PrimalHypergraphConverter() { }

	PrimalHypergraphConverter::~PrimalHypergraphConverter() { }

	IMultiHypergraph *PrimalHypergraphConverter::convert(
			const IQbfInstance &instance) const
	{
		unique_ptr<IMutableMultiHypergraph> hypergraph(
			create::htdlib().multiHypergraphFactory().createInstance());

		for(vertex_t vertex = 1;  vertex <= instance.variableCount(); ++vertex)
			hypergraph->addVertex();

		for(const IQbfClause &clause : instance)
		{
			vector<vertex_t> edge;

			for(variable_t variable : clause)
				edge.push_back(variable);

			DBG("edge: "); DBG_COLL(edge); DBG(" = "); 

#ifdef DEBUG
			htd::id_t edgeId =
#endif // DEBUG
			hypergraph->addEdge(edge);

			DBG(edgeId + instance.variableCount()); DBG(std::endl);
		}

		return hypergraph.release();
	}
} // namespace qbf2asp
