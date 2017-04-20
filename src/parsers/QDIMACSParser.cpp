#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif
#include "../util/debug.hpp"

#include "QDIMACSParser.hpp"

#include "QDIMACSBisonParser.hpp"
#include "QDIMACSLexer.hpp"

#include <qbf2asp/create.hpp>

#include <iostream>

namespace qbf2asp
{
	using std::istream;
	using std::ostream;

	QDIMACSParser::QDIMACSParser() { }

	QDIMACSParser::~QDIMACSParser() { }

	IQbfInstance *QDIMACSParser::parse(istream *in)
	{
		return this->parse(in, nullptr);
	}

	IQbfInstance *QDIMACSParser::parse(istream *in, ostream *out)
	{
		IQbfInstance *result = create::instance();

		//TODO: proper error handling
		//if(!result) return nullptr;

		QDIMACSLexer *lexer = new QDIMACSLexer(in, out);
		QDIMACSBisonParser *parser = new QDIMACSBisonParser(*lexer, *result);

		bool error = parser->parse();

		delete parser;
		delete lexer;

		//TODO: proper error handling
		if(error)
		{
			delete result;
			return nullptr;
		}

		return result;
	}

} // namespace qbf2asp
