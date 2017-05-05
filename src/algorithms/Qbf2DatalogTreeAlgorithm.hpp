#ifndef QBF2ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_
#define QBF1ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspTreeAlgorithm.hpp>

#include <logic/parsers>

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

		virtual void setOutputStream(std::ostream &out) override;

		virtual std::vector<const htd::ILabelingFunction *>
			preprocessOperations() const override;

		virtual sharp::ITable *evaluateNode(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const sharp::IDecomposableInstance &instance) const override;

		virtual bool needAllTables() const override;

	protected:
		sharp::ITable *evaluateNode(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const logic::IQbfInstance &instance) const;

	private:
		const std::ostream * out_;

	}; // class Qbf2DatalogTreeAlgorithm

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_
