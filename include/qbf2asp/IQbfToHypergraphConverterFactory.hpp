#ifndef QBF2ASP_QBF2ASP_IQBFTOHYPERGRAPHCONVERTERFACTORY_H_
#define QBF2ASP_QBF2ASP_IQBFTOHYPERGRAPHCONVERTERFACTORY_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbfToHypergraphConverter.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQbfToHypergraphConverterFactory
	{
	protected:
		IQbfToHypergraphConverterFactory &operator=(
				IQbfToHypergraphConverterFactory &)
		{ return *this; }

	public:
		virtual ~IQbfToHypergraphConverterFactory() = 0;

		virtual IQbfToHypergraphConverter *create() const = 0;

	}; // class IQbfToHypergraphConverterFactory

	inline IQbfToHypergraphConverterFactory::~IQbfToHypergraphConverterFactory()
	{ }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBFTOHYPERGRAPHCONVERTERFACTORY_H_
