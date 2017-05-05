#ifndef QBF2ASP_INSTANCES_PRIMALHYPERGRAPHCONVERTER_H_
#define QBF2ASP_INSTANCES_PRIMALHYPERGRAPHCONVERTER_H_

#include <qbf2asp/global>

#include "QbfInstance.hpp"

#include <qbf2asp/IQbfToHypergraphConverter.hpp>

namespace qbf2asp
{
	class QBF2ASP_LOCAL PrimalHypergraphConverter
		: public IHypergraphConverter
	{
	public:
		PrimalHypergraphConverter();
		virtual ~PrimalHypergraphConverter() override;

		virtual htd::IHypergraph *convert(
				const IQbfInstance &instance) const override;

	}; // class PrimalHypergraphConverter

} // namespace qbf2asp

#endif // QBF2ASP_INSTANCES_PRIMALHYPERGRAPHCONVERTER_H_
