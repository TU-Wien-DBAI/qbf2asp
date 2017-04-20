%{
#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include "QDIMACSBisonParser.hpp"
#include "QDIMACSLexer.hpp"

#include <string>

#include <cstddef>

#define yyterminate() return static_cast<token_type>(0);

%}

%option c++ batch noyywrap stack yylineno nounput debug
%option prefix="QDIMACS"

blank [ \t\r]
eol \n
zero 0
textline [^{eol}]*

word [1-9][0-9]*
exists e
forall a
comment c
problem p
cnf cnf
dnf dnf
neg -


%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}

%x COMMENT

%%

%{
yylloc->step();
%}

<COMMENT>
{
	{textline}  {
					BEGIN(INITIAL);
					yylval->string = new std::string(yytext, yyleng);
					return token::TEXT;
				}
}				


{blank}		{ yylloc->step(); }

{zero}  	{ return token::ZERO; }

{eol}		{ 
				yylloc->lines(yyleng);
				return token::EOL;
			}

{problem}	{ return token::PROBLEM; }

{comment}   {
				BEGIN(COMMENT);
				return token::COMMENT;
			}

{cnf}		{ return token::CNF; }

{dnf}		{ return token::DNF; }

{word}      {
				yylval->number = static_cast<std::size_t>(std::stoull(yytext));
				return token::WORD;
			}

{exists}    { return token::EXISTS; }

{forall}    { return token::FORALL; }

{neg}       { return token::NEG; }
			
%%

namespace qbf2asp
{
	QDIMACSLexer::QDIMACSLexer(FLEX_STD istream *in, FLEX_STD ostream *out)
		: QDIMACSFlexLexer(in, out)
	{ }

	QDIMACSLexer::~QDIMACSLexer() { }

	void QDIMACSLexer::set_debug(bool value)
	{
		yy_flex_debug = value;
	}
}

#ifdef yylex
#undef yylex
#endif
int QDIMACSFlexLexer::yylex()
{
	std::cerr << "In QDIMACSFlexLexer::yylex()!" << std::endl;
	return 0;
}
