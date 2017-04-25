#ifndef QBF2ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_
#define QBF2ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspTreeAlgorithm.hpp>

#include <sharp/main>

#include <htd/main.hpp>

#include <memory>

namespace qbf2asp
{

	class QBF2ASP_LOCAL Qbf2DatalogTreeAlgorithm : public IQbf2AspTreeAlgorithm
	{
	protected:
		Qbf2DatalogTreeAlgorithm &operator=(Qbf2DatalogTreeAlgorithm &)
		{ return *this; }

	public:
		Qbf2DatalogTreeAlgorithm();
		virtual ~Qbf2DatalogTreeAlgorithm() override;

		virtual void rewrite(const IQbfInstance &instance) const override;

		virtual std::size_t decompose(
				const IQbfInstance &instance) const override;

		virtual std::vector<const htd::ILabelingFunction *>
			preprocessOperations() const override;

		virtual sharp::ITable *evaluateNode(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const sharp::IInstance &instance) const override;

		virtual bool needAllTables() const override;

	protected:
		sharp::ITable *evaluateNode(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const IQbfInstance &instance) const;

	private:
		std::unique_ptr<htd::ITreeDecompositionAlgorithm> tdAlgorithm_;
		std::unique_ptr<sharp::ITreeSolver> solver_;

	}; // class Qbf2DatalogTreeAlgorithm

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_
