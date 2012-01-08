#pragma once


#ifndef YY_DECL
#	define YY_DECL \
		nde::script::Parser::token_type \
		nde::script::Scanner::lex( \
			nde::script::Parser::semantic_type* yylval, \
			nde::script::Parser::location_type* yylloc, \
			nde::script::Driver&driver, \
		)
#endif

namespace nde {
namespace script {

class Scanner : public yyFlexLexer {
public:
		Scanner(FLEX_STD istream* arg_yyin = 0, FLEX_STD ostream* arg_yyout = 0);

		virtual ~Scanner();

		virtual Parser::token_type lex(Parser::semantic_type* yylval, Parser::location_type* yylloc, Driver& driver);

		void set_debug(bool b);
};

}
}


#undef yylex
#define yylex driver.lexer->lex
