#ifndef QBF2ASP_INSTANCES_QBFTOPRIMALHYPERGRAPHCONVERTER_H_
#define QBF2ASP_INSTANCES_QBFTOPRIMALHYPERGRAPHCONVERTER_H_

#include <qbf2asp/global>

#include "QbfInstance.hpp"

#include <qbf2asp/IQbfToHypergraphConverter.hpp>

namespace qbf2asp
{
	class QBF2ASP_LOCAL QbfToPrimalHypergraphConverter
		: public IQbfToHypergraphConverter
	{
	public:
		QbfToPrimalHypergraphConverter();
		virtual ~QbfToPrimalHypergraphConverter() override;

		virtual htd::IHypergraph *convert(
				const IQbfInstance &instance) const override;

	}; // class QbfToPrimalHypergraphConverter

} // namespace qbf2asp

#endif // QBF2ASP_INSTANCES_QBFTOPRIMALHYPERGRAPHCONVERTER_H_
