#ifndef QBF2ASP_QBF2ASP_QBF2DATALOGTREEREWRITER_H_
#define QBF1ASP_QBF2ASP_QBF2DATALOGTREEREWRITER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspTreeRewriter.hpp>
#include <qbf2asp/IQbf2AspTreeAlgorithm.hpp>

#include <sharp/main>

#include <htd/main.hpp>

#include <memory>

namespace qbf2asp
{

	class QBF2ASP_LOCAL Qbf2DatalogTreeRewriter : public IQbf2AspTreeRewriter
	{
	protected:
		Qbf2DatalogTreeRewriter &operator=(Qbf2DatalogTreeRewriter &)
		{ return *this; }

	public:
		Qbf2DatalogTreeRewriter();
		virtual ~Qbf2DatalogTreeRewriter() override;

		virtual void rewrite(
				const logic::IQbfInstance &instance) const override;

		virtual void rewrite(
				const logic::IQbfInstance &instance,
				std::ostream &out) const override;

		virtual htd::ITreeDecomposition *decompose(
				const sharp::IDecomposableInstance &instance) const override;

		virtual sharp::ISolution *solve(
				const sharp::IDecomposableInstance &instance) const override;

		virtual sharp::ISolution *solve(
				const sharp::IDecomposableInstance &instance,
				const htd::ITreeDecomposition &decomposition) const override;

	private:
		std::unique_ptr<htd::ITreeDecompositionAlgorithm> tdAlgorithm_;
		std::unique_ptr<IQbf2AspTreeAlgorithm> treeAlgorithm_;
		std::unique_ptr<sharp::ITreeSolver> solver_;

	}; // class Qbf2DatalogTreeRewriter

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_QBF2DATALOGTREEREWRITER_H_
