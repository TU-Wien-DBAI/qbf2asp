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

number [1-9][0-9]*
exists e
forall a
comment c{blank}.*
problem p
cnf cnf
dnf dnf
neg -


%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}

%%

%{
yylloc->step();
%}

{comment}	{
				yylval->string = new std::string(yytext + 2);
				return token::COMMENT;
			}

{blank}		{ yylloc->step(); }

{zero}  	{ return token::ZERO; }

{eol}		{ 
				yylloc->lines(yyleng);
				return token::EOL;
			}

{problem}	{ return token::PROBLEM; }

{cnf}		{ return token::CNF; }

{dnf}		{ return token::DNF; }

{number}    {
				yylval->number = static_cast<qbf2asp::num_t>(
						std::stoul(yytext));
				return token::NUMBER;
			}

{exists}    { return token::EXISTS; }

{forall}    { return token::FORALL; }

{neg}       { return token::NEG; }
				
%%

namespace qbf2asp
{
	QDIMACSLexer::QDIMACSLexer(std::istream *in, std::ostream *out)
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
