#pragma once
#include <string>
#include <stdexcept>

#include <script/ScriptBase.hpp>
#include "script/Token.hpp"

namespace nde {

#define MIN_SCRIPT_LENGTH 10 // try writing a program shorter than this

class LexerError : public std::runtime_error { };

class Lexer : public ScriptBase<LexerError> {
	typedef union { int i; float f; } number_t;

	tokens_t tokens;
	const char* program;
	char* program_end;
	char* c;
	char* peek;

	size_t lineno;
	size_t charno;

public:
	Lexer();
	virtual ~Lexer();

	bool lex(const std::string& _program);

	tokens_t::iterator begin();
	tokens_t::iterator end();
	tokens_t& getTokens() { return tokens; }

private:
	bool next();
	void backup(size_t count = 1);

	bool isWhite() const;
	bool isAlpha() const;
	bool isNumeric() const;
	bool isAlNum() const;
	bool isPunct() const;

	bool expect(char expected_char);

	void skipWhite();
	std::string getIdent();
	TokenType getPunct();
	number_t getNumber(TokenType& t);
	std::string getString();

};

}


