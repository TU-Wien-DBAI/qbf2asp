#ifndef QBF2ASP_QBF2ASP_IQBFTOHYPERGRAPHCONVERTER_H_
#define QBF2ASP_QBF2ASP_IQBFTOHYPERGRAPHCONVERTER_H_

#include <qbf2asp/global>

#include <logic/parsers>

#include <htd/main.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQbfToHypergraphConverter
	{
	protected:
		IQbfToHypergraphConverter &operator=(IQbfToHypergraphConverter &)
		{ return *this; }

	public:
		virtual ~IQbfToHypergraphConverter() = 0;

		virtual htd::IHypergraph *convert(
				const logic::IQbfInstance &instance) const = 0;

	}; // class IQbfToHypergraphConverter

	inline IQbfToHypergraphConverter::~IQbfToHypergraphConverter() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBFTOHYPERGRAPHCONVERTER_H_
