#ifndef QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHMFACTORY_H_
#define QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHMFACTORY_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspTreeAlgorithm.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQbf2AspTreeAlgorithmFactory
	{
	protected:
		IQbf2AspTreeAlgorithmFactory &operator=(IQbf2AspTreeAlgorithmFactory &)
		{ return *this; }

	public:
		virtual ~IQbf2AspTreeAlgorithmFactory() = 0;

		virtual IQbf2AspTreeAlgorithm *create() const = 0;

	}; // class IQbf2AspTreeAlgorithmFactory

	inline IQbf2AspTreeAlgorithmFactory::~IQbf2AspTreeAlgorithmFactory() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBF2ASPTREEALGORITHMFACTORY_H_
