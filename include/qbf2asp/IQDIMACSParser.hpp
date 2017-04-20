#ifndef QBF2ASP_QBF2ASP_IQDIMACSPARSER_H_
#define QBF2ASP_QBF2ASP_IQDIMACSPARSER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbfInstance.hpp>

#include <iostream>

namespace qbf2asp
{
	class QBF2ASP_API IQDIMACSParser
	{
	protected:
		IQDIMACSParser &operator=(IQDIMACSParser &) { return *this; }

	public:
		virtual ~IQDIMACSParser() = 0;

		virtual IQbfInstance *parse(std::istream *in) = 0;
		virtual IQbfInstance *parse(
				std::istream *in,
				std::ostream *out) = 0;

	}; // class IQDIMACSParser

	inline IQDIMACSParser::~IQDIMACSParser() { }

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_IQDIMACSPARSER_H_
