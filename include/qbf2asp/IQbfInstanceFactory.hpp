#ifndef QBF2ASP_QBF2ASP_IQBFINSTANCEFACTORY_H_
#define QBF2ASP_QBF2ASP_IQBFINSTANCEFACTORY_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbfInstance.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQbfInstanceFactory
	{
	protected:
		IQbfInstanceFactory &operator=(IQbfInstanceFactory &) { return *this; }

	public:
		virtual ~IQbfInstanceFactory() = 0;

		virtual IQbfInstance *create() const = 0;

	}; // class IQbfInstanceFactory

	inline IQbfInstanceFactory::~IQbfInstanceFactory() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBFINSTANCEFACTORY_H_
