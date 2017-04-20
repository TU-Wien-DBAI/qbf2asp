#ifndef QBF2ASP_QBF2ASP_IQDIMACSPARSERFACTORY_H_
#define QBF2ASP_QBF2ASP_IQDIMACSPARSERFACTORY_H_

#include <qbf2asp/global>

#include <qbf2asp/IQDIMACSParser.hpp>

namespace qbf2asp
{
	class QBF2ASP_API IQDIMACSParserFactory
	{
	protected:
		IQDIMACSParserFactory &operator=(IQDIMACSParserFactory &)
		{ return *this; }

	public:
		virtual ~IQDIMACSParserFactory() = 0;

		virtual IQDIMACSParser *create() const = 0;

	}; // class IQDIMACSParserFactory

	inline IQDIMACSParserFactory::~IQDIMACSParserFactory() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQDIMACSPARSERFACTORY_H_
