%{

#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include "QDIMACSBisonParser.hpp"
#include "QDIMACSLexer.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

#include <cstddef>

#undef yylex
#define yylex lexer.lex

#define CHECK(name, pos, expect, actual)	\
	if((expect) != (actual))				\
	{										\
		std::ostringstream ss;				\
		ss << (name) << " was "	<< (expect)	\
		   << " but " << (actual)			\
		   << " in list";					\
		error((pos), ss.str());				\
		YYERROR;							\
	}
%}

%require "3.0"

%skeleton "lalr1.cc"

%define "parser_class_name" { QDIMACSBisonParser } 
%name-prefix "qbf2asp"
%file-prefix "QDIMACSBison"

%locations
%define parse.error verbose

%union
{
	std::string *string;
	std::size_t number;
	std::vector<std::size_t> *vector;
	IQbfClause *clause;
}

%token PROBLEM EXISTS FORALL NEG CNF DNF ZERO EOL
%token<string> COMMENT
%token<number> WORD

%destructor { delete $$; } COMMENT

%parse-param { QDIMACSLexer &lexer } { IQbfInstance &instance }

%start qdimacs

%%

qdimacs	 :	comments cnf quantse clauses
		 |  comments dnf quantsf clauses
		 ;

comments :  comment comments
		 |
		 ;

comment  :  COMMENT EOL
		 ;

cnf      :	PROBLEM CNF varcnt clausecnt EOL
		 ;

dnf		 :	PROBLEM DNF varcnt clausecnt EOL
	     ;

varcnt   :  WORD
		 ;

clausecnt:  WORD
		 ;

quantsf  :	quantse forall
		 |
		 ;

quantse  :	quantsf exists
		 |
		 ;

exists   :  EXISTS variables ZERO EOL
		 ;

forall   :  FORALL variables ZERO EOL
		 ;

variables:  variable variables
		 |  variable
		 ;

variable :  WORD
		 ;

clauses  :  clause clauses
		 |  clause
		 ;

clause   :  literals ZERO EOL
		 ;

literals :  literal literals
		 |  literal
		 ;

literal  :  variable
		 |  NEG variable
		 ;

%%

namespace qbf2asp
{
	void QDIMACSBisonParser::error(
		const QDIMACSBisonParser::location_type &l,
		const std::string &m)
	{
		std::cerr << l << ": " << m << "; last parsed word: '"
			<< lexer.YYText() << "'" << std::endl;
	}
}
