#ifndef QBF2ASP_QBF2ASP_IQBF2ASPTREEREWRITERFACTORY_H_
#define QBF2ASP_QBF2ASP_IQBF2ASPTREEREWRITERFACTORY_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriterFactory.hpp>
#include <qbf2asp/IQbf2AspTreeRewriter.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQbf2AspTreeRewriterFactory
		: public IQbf2AspRewriterFactory
	{
	protected:
		IQbf2AspTreeRewriterFactory &operator=(IQbf2AspTreeRewriterFactory &)
		{ return *this; }

	public:
		virtual ~IQbf2AspTreeRewriterFactory() = 0;

		virtual IQbf2AspTreeRewriter *create() const override = 0;

	}; // class IQbf2AspTreeRewriterFactory

	inline IQbf2AspTreeRewriterFactory::~IQbf2AspTreeRewriterFactory() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQBF2ASPTREEREWRITERFACTORY_H_
