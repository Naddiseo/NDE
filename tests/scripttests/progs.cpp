#include "tests/scripttests/progs.hpp"

using nde::TokenType;
using nde::Token;

#define TT(v,l,c,  ...) Token(TokenType::v, l, c, ##__VA_ARGS__)

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
	TT(INT, 1, 1),
	TT(IDENT, 1, 5, "a"),
	TT(ASSIGN, 1, 6),
	TT(INTVAL, 1, 7, 123456),
	TT(SEMICOLON, 1, 13),
	TT(FLOAT, 3, 3),
	TT(IDENT, 3, 9, "b"),
	TT(ASSIGN, 3, 10),
	TT(FLOATVAL, 3, 12, 98765.4321f),
	TT(SEMICOLON, 3, 22),
	TT(STRING, 4, 1),
	TT(IDENT, 4, 8, "c"),
	TT(ASSIGN, 4, 10),
	TT(STRINGVAL, 4, 11, "hello world\n"),
	TT(SEMICOLON, 4, 26)
};

std::string prog3 = // test all the tokens
	"int\nuint\nfloat\nstring\nvector\nbool\ntrue\nfalse\nvoid\n"
	"if\nwhile\nfor\nbreak\ncontinue\nelse\nclass\nreturn\nevent\ntrigger\n"
	"identifier\n94545\n1.2\n12.12\n\"hello \\\"world\\\"!\"\n"
	";\n(\n)\n{\n}\n,\n.\n"
	"=\n==\n!\n!=\n<\n>\n<=\n>=\n"
	"||\nor\n&&\nand\n"
	"~\n|\n&\n^\n<<\n>>\n|=\n&=\n^=\n<<=\n>>=\n"
	"+\n-\n*\n/\n++\n--\n+=\n-=\n*=\n/=\n"
	":\n?\n"
	;

#undef TT

#define TT(v,...) Token(TokenType::v, __COUNTER__+1, 1, ##__VA_ARGS__)

nde::tokens_t prog3_expected = {
	TT(INT),
	TT(UINT),
	TT(FLOAT),
	TT(STRING),
	TT(VECTOR),
	TT(BOOL),
	TT(TRUE),
	TT(FALSE),
	TT(VOID),
	TT(IF),
	TT(WHILE),
	TT(FOR),
	TT(BREAK),
	TT(CONTINUE),
	TT(ELSE),
	TT(CLASS),
	TT(RETURN),
	TT(EVENT),
	TT(TRIGGER),
	TT(IDENT, "identifier"),
	TT(INTVAL, (int)94545),
	TT(FLOATVAL, 1.2f),
	TT(FLOATVAL, 12.12f),
	TT(STRINGVAL, "hello \"world\"!"),
	TT(SEMICOLON),
	TT(LPAREN),
	TT(RPAREN),
	TT(LBRACE),
	TT(RBRACE),
	TT(COMMA),
	TT(DOT),
	TT(ASSIGN),
	TT(EQUAL),
	TT(NOT),
	TT(NEQUAL),
	TT(LT),
	TT(GT),
	TT(LTE),
	TT(GTE),
	TT(OR),
	TT(OR),
	TT(AND),
	TT(AND),
	TT(BNOT),
	TT(BOR),
	TT(BAND),
	TT(BXOR),
	TT(LSHIFT),
	TT(RSHIFT),
	TT(BORASSIGN),
	TT(BANDASSIGN),
	TT(BXORASSIGN),
	TT(LSHIFTASSIGN),
	TT(RSHIFTASSIGN),
	TT(ADD),
	TT(SUB),
	TT(MUL),
	TT(DIV),
	TT(INC),
	TT(DEC),
	TT(ADDASSIGN),
	TT(SUBASSIGN),
	TT(MULASSIGN),
	TT(DIVASSIGN),
	TT(COLON),
	TT(QUESTION),
};


std::string prog4 =
	"class Base {\n"
	"	"
	"}\n"
	"class Child : Base {\n"
	"}\n"
	"void main(){ Child c(); }"
	;

#undef TT
