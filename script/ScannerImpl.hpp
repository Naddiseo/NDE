#pragma once
#include "Script.hpp"


#ifndef YY_DECL
#	define YY_DECL \
		NDESCRIPT_NS Parser::token_type \
		NDESCRIPT_NS Scanner::lex( \
			NDESCRIPT_NS Parser::semantic_type* yylval, \
			NDESCRIPT_NS Parser::location_type* yylloc, \
			NDESCRIPT_NS Driver& driver \
		)
#endif

NDESCRIPT_NS_BEGIN

class Scanner : public yyFlexLexer {
public:
		Scanner(FLEX_STD istream* arg_yyin = 0, FLEX_STD ostream* arg_yyout = 0);

		virtual ~Scanner();

		virtual Parser::token_type lex(Parser::semantic_type* yylval, Parser::location_type* yylloc, Driver& driver);

		void set_debug(bool b);
};

NDESCRIPT_NS_END

#undef yylex
#define yylex driver.lexer->lex
