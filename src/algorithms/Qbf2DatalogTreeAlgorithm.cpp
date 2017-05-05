#include "../preamble.h"
#include "Qbf2DatalogTreeAlgorithm.hpp"

#include "Qbf2DatalogTable.hpp"

#include <qbf2asp/create.hpp>
#include <qbf2asp/DecomposableQbfInstance.hpp>

#include <memory>

namespace qbf2asp
{
	using logic::IQbfInstance;

	using sharp::INodeTableMap;
	using sharp::IDecomposableInstance;
	using sharp::ITable;

	using htd::IHypergraph;
	using htd::ITreeDecompositionAlgorithm;
	using htd::ITreeDecomposition;
	using htd::ILabelingFunction;
	using htd::vertex_t;

	using std::unique_ptr;
	using std::size_t;
	using std::vector;
	using std::ostream;

	Qbf2DatalogTreeAlgorithm::Qbf2DatalogTreeAlgorithm() : out_(&std::cout) { }

	Qbf2DatalogTreeAlgorithm::~Qbf2DatalogTreeAlgorithm() { }

	void Qbf2DatalogTreeAlgorithm::setOutputStream(ostream &out)
	{
		out_ = &out;
	}

	vector<const ILabelingFunction *>
	Qbf2DatalogTreeAlgorithm::preprocessOperations() const
	{
		return vector<const ILabelingFunction *>();
	}
	
	ITable *Qbf2DatalogTreeAlgorithm::evaluateNode(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const INodeTableMap &tables,
			const IDecomposableInstance &instance) const
	{
		const DecomposableQbfInstance &qbfInstance(
				static_cast<const DecomposableQbfInstance &>(instance));

		return evaluateNode(node, decomposition, tables, qbfInstance.content());
	}

	bool Qbf2DatalogTreeAlgorithm::needAllTables() const
	{
		return false;
	}

	ITable *Qbf2DatalogTreeAlgorithm::evaluateNode(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const INodeTableMap &tables,
			const IQbfInstance &instance) const
	{
		return nullptr;
	}

} // namespace qbf2asp
