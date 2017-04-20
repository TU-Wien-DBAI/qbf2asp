#ifndef QBF2ASP_QBF2ASP_QBF2ASPALGORITHM_H_
#define QBF2ASP_QBF2ASP_QBF2ASPALGORITHM_H_

#include <qbf2asp/global>

#include <sharp/main>

#include <htd/main.hpp>

namespace qbf2asp
{

	class QBF2ASP_API IQbf2AspAlgorithm : public sharp::ITreeAlgorithm
	{
	protected:
		IQbf2AspAlgorithm &operator=(IQbf2AspAlgorithm &) { return *this; }

	public:
		virtual ~IQbf2AspAlgorithm() override = 0;

		virtual std::vector<const htd::ILabelingFunction *>
			preprocessOperations() const override;

		virtual sharp::ITable *evaluateNode(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const sharp::IInstance &instance) const override;

		virtual bool needAllTables() const override;

	}; // class IQbf2AspAlgorithm

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_QBF2ASPALGORITHM_H_
