#pragma once
#include <string>
#include "Script.hpp"

#include "Parser.hpp"


#ifndef YY_DECL
#	define YY_DECL \
		NDESCRIPT_NS Parser::token_type \
		NDESCRIPT_NS Scanner::lex( \
			NDESCRIPT_NS  Parser::semantic_type* yylval, \
			NDESCRIPT_NS  Parser::location_type* yylloc, \
			NDESCRIPT_NS  Driver& driver \
		)
#endif
#ifndef __FLEX_LEXER_H
#	undef yylex
#	include "Scanner.hpp"
#endif
#include "ScannerImpl.hpp"


NDE_NS_BEGIN
namespace ast { class Program; }
NDE_NS_END

NDESCRIPT_NS_BEGIN


class Scanner;

class Driver {
public:
	Driver(class  ast::Program& _program);
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

NDESCRIPT_NS_END
