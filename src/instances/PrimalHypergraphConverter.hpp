#ifndef QBF2ASP_INSTANCES_PRIMALHYPERGRAPHCONVERTER_H_
#define QBF2ASP_INSTANCES_PRIMALHYPERGRAPHCONVERTER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbfToHypergraphConverter.hpp>

namespace qbf2asp
{
	class QBF2ASP_LOCAL PrimalHypergraphConverter
		: public IQbfToHypergraphConverter
	{
	public:
		PrimalHypergraphConverter();
		virtual ~PrimalHypergraphConverter() override;

		virtual htd::IMultiHypergraph *convert(
				const logic::IQbfInstance &instance) const override;

	}; // class PrimalHypergraphConverter

} // namespace qbf2asp

#endif // QBF2ASP_INSTANCES_PRIMALHYPERGRAPHCONVERTER_H_
