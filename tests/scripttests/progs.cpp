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

std::string prog3 = // test all the tokens
	"int\nuint\nfloat\nstring\nvector\nbool\ntrue\nfalse\nvoid\n"
	"if\nwhile\nfor\nbreak\ncontinue\nelse\n"
	"identifier\n94545\n1.2\n12.12\n\"hello \\\"world\\\"!\"\n"
	";\n(\n)\n{\n}\n,\n.\n"
	"=\n==\n!\n!=\n<\n>\n<=\n>=\n"
	"||\nor\n&&\nand\n"
	"~\n|\n&\n^\n<<\n>>\n|=\n&=\n^=\n<<=\n>>=\n"
	"+\n-\n*\n/\n++\n--\n+=\n-=\n*=\n/=\n"
	;
nde::tokens_t prog3_expected = {
	{TT(INT), 1, 1},
	{TT(UINT), 2, 1},
	{TT(FLOAT), 3, 1},
	{TT(STRING), 4, 1},
	{TT(VECTOR), 5, 1},
	{TT(BOOL), 6, 1},
	{TT(TRUE), 7, 1},
	{TT(FALSE), 8, 1},
	{TT(VOID), 9, 1},
	{TT(IF), 10, 1},
	{TT(WHILE), 11, 1},
	{TT(FOR), 12, 1},
	{TT(BREAK), 13, 1},
	{TT(CONTINUE), 14, 1},
	{TT(ELSE), 15, 1},
	{TT(IDENT), 16, 1, "identifier"},
	{TT(INTVAL), 17, 1, (int)94545},
	{TT(FLOATVAL), 18, 1, 1.2f},
	{TT(FLOATVAL), 19, 1, 12.12f},
	{TT(STRINGVAL), 20, 1, "hello \"world\"!"},
	{TT(SEMICOLON), 21, 1},
	{TT(LPAREN), 22, 1},
	{TT(RPAREN), 23, 1},
	{TT(LBRACE), 24, 1},
	{TT(RBRACE), 25, 1},
	{TT(COMMA), 26, 1},
	{TT(DOT), 27, 1},
	{TT(ASSIGN), 28, 1},
	{TT(EQUAL), 29, 1},
	{TT(NOT), 30, 1},
	{TT(NEQUAL), 31, 1},
	{TT(LT), 32, 1},
	{TT(GT), 33, 1},
	{TT(LTE), 34, 1},
	{TT(GTE), 35, 1},
	{TT(OR), 36, 1},
	{TT(OR), 37, 1},
	{TT(AND), 38, 1},
	{TT(AND), 39, 1},
	{TT(BNOT), 40, 1},
	{TT(BOR), 41, 1},
	{TT(BAND), 42, 1},
	{TT(BXOR), 43, 1},
	{TT(LSHIFT), 44, 1},
	{TT(RSHIFT), 45, 1},
	{TT(BORASSIGN), 46, 1},
	{TT(BANDASSIGN), 47, 1},
	{TT(BXORASSIGN), 48, 1},
	{TT(LSHIFTASSIGN), 49, 1},
	{TT(RSHIFTASSIGN), 50, 1},
	{TT(ADD), 51, 1},
	{TT(SUB), 52, 1},
	{TT(MUL), 53, 1},
	{TT(DIV), 54, 1},
	{TT(INC), 55, 1},
	{TT(DEC), 56, 1},
	{TT(ADDASSIGN), 57, 1},
	{TT(SUBASSIGN), 58, 1},
	{TT(MULASSIGN), 59, 1},
	{TT(DIVASSIGN), 60, 1},
};

#undef TT
