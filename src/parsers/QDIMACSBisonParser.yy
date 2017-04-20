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

#include <cstddef>

#undef yylex
#define yylex lexer.lex

#define CHECK(name, pos, expect, actual)	\
	if((expect) != (actual))				\
	{										\
		std::ostringstream ss;				\
		ss << (name) << " was "	<< (expect)	\
		   << " but " << (actual)		\
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

%token PROBLEM COMMENT EXISTS FORALL NEG CNF DNF ZERO EOL
%token<string> TEXT
%token<number> WORD

%destructor { delete $$; } TEXT

%parse-param { QDIMACSLexer &lexer } { IQbfInstance &instance }

%start qdimacs

%%

qdimacs	 :	comments cnf quantse clauses
		 |  comments dnf quantsf clauses
		 ;

comments :  comments comment
		 |
		 ;

comment  :  COMMENT TEXT EOL

cnf      :	PROBLEM CNF WORD WORD EOL
		 ;

dnf		 :	PROBLEM DNF WORD WORD EOL
	     ;

quantsf  :	quantse forall
		 |
		 ;

quantse  :	quantsf exists
		 |
		 ;

exists   :  variables ZERO EOL
		 ;

forall   :  variables ZERO EOL
		 ;

variables:  variables variable
		 |  variable
		 ;

clauses  :  clauses clause
		 |  clause
		 ;

clause   :  literals ZERO EOL
		 ;

literals :  literals literal
		 |  literal
		 ;

literal  :  WORD
		 |  NEG WORD
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
