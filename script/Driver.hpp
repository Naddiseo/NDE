#pragma once
#include <string>
#include "Parser.hpp"


#ifndef YY_DECL
#	define YY_DECL \
		nde::script::Parser::token_type \
		nde::script::Scanner::lex( \
			nde::script::Parser::semantic_type* yylval, \
			nde::script::Parser::location_type* yylloc, \
			nde::script::Driver&driver, \
		)
#endif

#ifndef __FLEX_LEXER_H
#	include "Scanner.hpp"
#endif
#include "ScannerImpl.hpp"

namespace nde {

namespace ast { class Program; }

namespace script {


class Scanner;

class Driver {
public:
	Driver(class ast::Program& _program);
	~Driver();

	bool trace_scanning;
	bool trace_parsing;

	std::string streamname;

	bool parseStream(std::istream& in, const std::string& sname = "stream input");
	bool parseString(const std::string& input, const std::string& sname = "string stream");
	bool parseFile(const std::string& filename);

	void error(const class location& l, const std::string& m);
	void error(const std::string& m);


	class Scanner* lexer;

	class ast::Program& program;
};

}
}

