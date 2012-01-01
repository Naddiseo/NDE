#include "tests/scripttests/progs.hpp"

using nde::TokenType;
#define TT(v) TokenType::v

std::string prog1 =
	"void main() {\n"
	"}";

nde::tokens_t prog1_expected = {
	{TokenType::VOID, 1, 1},
	{TokenType::IDENT, 1, 6, "main"},
	{TokenType::LPAREN, 1, 10},
	{TokenType::RPAREN, 1, 11},
	{TokenType::LBRACE, 1, 13},
	{TokenType::RBRACE, 2, 1},
};

std::string prog2 =
	"int a=123456;\n"
	"   \n  "
	"float b= 98765.4321;\n"
	"string c =\"hello world\\n\";\n"
	;
nde::tokens_t prog2_expected = {
	{TT(INT), 1, 1},
	{TT(IDENT), 1, 5, "a"},
	{TT(ASSIGN), 1, 6},
	{TT(INTVAL), 1, 7, 123456},
	{TT(SEMICOLON), 1, 13},
	{TT(FLOAT), 3, 3},
	{TT(IDENT), 3, 9, "b"},
	{TT(ASSIGN), 3, 10},
	{TT(FLOATVAL), 3, 12, 98765.4321f},
	{TT(SEMICOLON), 3, 22},
	{TT(STRING), 4, 1},
	{TT(IDENT), 4, 8, "c"},
	{TT(ASSIGN), 4, 10},
	{TT(STRINGVAL), 4, 11, "hello world\n"},
	{TT(SEMICOLON), 4, 26}
};


#undef TT
