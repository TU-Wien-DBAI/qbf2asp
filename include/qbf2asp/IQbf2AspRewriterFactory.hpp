#ifndef QBF2ASP_QBF2ASP_IQBF2ASPREWRITERFACTORY_H_
#define QBF2ASP_QBF2ASP_IQBF2ASPREWRITERFACTORY_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriter.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQbf2AspRewriterFactory
	{
	protected:
		IQbf2AspRewriterFactory &operator=(IQbf2AspRewriterFactory &)
		{ return *this; }

	public:
		virtual ~IQbf2AspRewriterFactory() = 0;

		virtual IQbf2AspRewriter *create() const = 0;

	}; // class IQbf2AspRewriterFactory

	inline IQbf2AspRewriterFactory::~IQbf2AspRewriterFactory() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBF2ASPREWRITERFACTORY_H_
