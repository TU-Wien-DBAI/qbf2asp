#ifndef QBF2ASP_PARSERS_QDIMACSLEXER_H_
#define QBF2ASP_PARSERS_QDIMACSLEXER_H_

#include <qbf2asp/global>

#include "QDIMACSBisonParser.hpp"

typedef qbf2asp::QDIMACSBisonParser::token token;
typedef qbf2asp::QDIMACSBisonParser::token_type token_type;
typedef qbf2asp::QDIMACSBisonParser::semantic_type semantic_type;
typedef qbf2asp::QDIMACSBisonParser::location_type location_type;

#ifndef YY_DECL
#define YY_DECL						\
	token_type						\
	qbf2asp::QDIMACSLexer::lex(		\
		semantic_type *yylval,		\
		location_type *yylloc		\
	)
#endif // YY_DECL

#ifndef __FLEX_LEXER_H
#undef yyFlexLexer
#define yyFlexLexer QDIMACSFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif // __FLEX_LEXER_H

namespace qbf2asp
{
	class QBF2ASP_LOCAL QDIMACSLexer : public QDIMACSFlexLexer
	{
	public:
		QDIMACSLexer(std::istream *in = nullptr, std::ostream *out = nullptr);
		virtual ~QDIMACSLexer();

		virtual token_type lex(semantic_type *yylval, location_type *yylloc);

		void set_debug(bool debug);

	}; // class QDIMACSLexer

} // namespace qbf2asp

#endif /* QBF2ASP_PARSERS_QDIMACSLEXER_H_ */
