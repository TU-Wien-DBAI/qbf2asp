#ifndef QBF2ASP_PARSERS_QDIMACSPARSER_H_
#define QBF2ASP_PARSERS_QDIMACSPARSER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQDIMACSParser.hpp>

namespace qbf2asp
{
	class QBF2ASP_LOCAL QDIMACSParser : public IQDIMACSParser
	{
	public:
		QDIMACSParser();
		virtual ~QDIMACSParser();

		virtual IQbfInstance *parse(std::istream *in) override;
		virtual IQbfInstance *parse(
				std::istream *in,
				std::ostream *out) override;

	}; // class QDIMACSParser

} // namespace qbf2asp

#endif // QBF2ASP_PARSERS_QDIMACSPARSER_H_
