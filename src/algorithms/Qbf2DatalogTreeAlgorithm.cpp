#include "../preamble.h"
#include "Qbf2DatalogTreeAlgorithm.hpp"

#include "Qbf2DatalogTable.hpp"

#include <qbf2asp/create.hpp>

#include <memory>

namespace qbf2asp
{
	using sharp::INodeTableMap;
	using sharp::IInstance;
	using sharp::ITable;

	using htd::IHypergraph;
	using htd::ITreeDecompositionAlgorithm;
	using htd::ITreeDecomposition;
	using htd::ILabelingFunction;
	using htd::vertex_t;

	using std::unique_ptr;
	using std::size_t;
	using std::vector;

	Qbf2DatalogTreeAlgorithm::Qbf2DatalogTreeAlgorithm()
	{
		tdAlgorithm_.reset(create::htdlib()
				.treeDecompositionAlgorithmFactory()
				.createInstance());

		solver_.reset(sharp::create::treeSolver(*tdAlgorithm_, *this));
	}

	Qbf2DatalogTreeAlgorithm::~Qbf2DatalogTreeAlgorithm() { }

	size_t Qbf2DatalogTreeAlgorithm::decompose(
			const IQbfInstance &instance) const
	{
		unique_ptr<ITreeDecomposition> td(solver_->decompose(instance));
		return td->maximumBagSize() - 1;
	}

	void Qbf2DatalogTreeAlgorithm::rewrite(const IQbfInstance &instance) const
	{
		unique_ptr<ITreeDecomposition> td(solver_->decompose(instance));
		sharp::ISolution *solution = solver_->solve(instance, *td);

		if(solution)
			delete solution;
	}

	vector<const ILabelingFunction *>
	Qbf2DatalogTreeAlgorithm::preprocessOperations() const
	{ }
	
	ITable *Qbf2DatalogTreeAlgorithm::evaluateNode(
			vertex_t node,
			const ITreeDecomposition &decomposition,
			const INodeTableMap &tables,
			const IInstance &instance) const
	{
		const IQbfInstance &qbfInstance(
				static_cast<const IQbfInstance &>(instance));

		return evaluateNode(node, decomposition, tables, qbfInstance);
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
