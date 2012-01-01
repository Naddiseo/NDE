#pragma once
#include <vector>
#include <string>
#ifdef NDEBUG
#	include <sstream>
#endif
namespace nde {

enum class TokenType : char {
	ERROR,

	// native types
	INT,
	UINT,
	FLOAT,
	STRING,
	VECTOR,
	VOID,

	//
	IDENT,

	// PUNCTUATION
	LPAREN, // (
	RPAREN, // )
	LBRACE, // {
	RBRACE, // }

	ASSIGN, // =
	EQUAL, // ==
	NEQUAL, // !=

};

struct Token {
	TokenType type;
	size_t lineno;
	size_t charno;

	std::string strtype;
	int inttype;
	float flttype;
	// Vector vectype;

	Token();
	Token(TokenType _t, size_t _l, size_t _c);
	Token(TokenType _t, size_t _l, size_t _c, std::string _s);
	Token(TokenType _t, size_t _l, size_t _c, int _i);
	Token(TokenType _t, size_t _l, size_t _c, float _f);
	//Token(TokenType _t, size_t _l, size_t _c, Vector _v);
	~Token();

	bool isExact(const Token& other) const;
	bool operator==(const Token& other) const;
#ifdef NDEBUG
	operator std::string();
#endif
};

typedef std::vector<Token> tokens_t;

} // namespace nde


