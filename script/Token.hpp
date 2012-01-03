#pragma once
#include <vector>
#include <string>
#ifdef NDEBUG
#	include <sstream>
#endif
#include "script/toks.hpp"

namespace nde {

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

	std::string getName();

	static std::string typeToString(TokenType _t);

	bool isError() const { return type == TokenType::IF; }

	bool isExact(const Token& other) const;
	bool operator==(const Token& other) const;
#ifdef NDEBUG
	operator std::string();
#endif
};

typedef std::vector<Token> tokens_t;

} // namespace nde


