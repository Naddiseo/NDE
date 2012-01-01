#include <cctype>
#include <map>
#include "script/Lexer.hpp"

namespace nde {

static std::map<std::string, TokenType> keywords = {
	{"int", TokenType::INT},
	{"uint", TokenType::UINT},
	{"float", TokenType::FLOAT},
	{"string", TokenType::STRING},
	{"vector", TokenType::VECTOR},
	{"void", TokenType::VOID},
};

typedef std::map<std::string, TokenType>::iterator kw_t;

Lexer::Lexer() : lineno(1), charno(1), haserror(false) {}

Lexer::~Lexer() {}

bool
Lexer::lex(const std::string& _program) {
#define SAVE _lineno = lineno; _charno = charno;
#define TOK(t) tokens.push_back({t, _lineno, _charno});
#define TOKV(t, v) tokens.push_back({t, _lineno, _charno, v});
	size_t _lineno, _charno;
	if (_program.size() < MIN_SCRIPT_LENGTH) {
		return false;
	}

	program = _program.c_str();
	program_end = const_cast<char*>(program + _program.size());
	c = const_cast<char*>(program);
	peek = c + 1;

	while (c != NULL) {
		skipWhite();
		if (!c) break;
		if (isAlpha() || *c == '_') {
			SAVE;
			std::string ident = getIdent();
			kw_t kw = keywords.find(ident);
			if (kw == keywords.end()) {
				TOKV(TokenType::IDENT, ident);
			}
			else {
				TOK(kw->second);
			}
			continue;
		}
		else if (isPunct()) {
			SAVE;
			TOK(getPunct());
		}
		next();
	}

	return !haserror;
#undef SAVE
}

void
Lexer::setError(std::string s) {
	errmsg = s;
	haserror = true;
}

bool
Lexer::next() {
	if (c == program_end || haserror) {
		c = NULL;
		return false;
	}

	c++;

	if (*c == '\n') {
		charno = 0;
		lineno++;
	}
	else {
		charno++;
	}

	if (peek == program_end) {
		peek = NULL;
	}
	else {
		peek++;
	}

	return true;
}

bool Lexer::isWhite() const { return std::isspace(*c) || std::iscntrl(*c); }
bool Lexer::isAlpha() const { return std::isalpha(*c); }
bool Lexer::isNumeric() const { return std::isdigit(*c); }
bool Lexer::isAlNum() const { return std::isalnum(*c); }
bool Lexer::isPunct() const { return std::ispunct(*c); }

bool
Lexer::expect(char expected_char) {
	if (expected_char == *c) {
		return true;
	}
	setError(std::string("Unexpected char '") + *c + "'");
	return false;
}

void
Lexer::skipWhite() {
	while (c && isWhite()) { next(); }
}
std::string
Lexer::getIdent() {
	std::string buf;

	if (isAlpha() || *c == '_') {
		buf += *c;
		next();
	}

	while (isAlNum() || *c == '_') {
		buf += *c;
		next();
	}

	return buf;
}

TokenType
Lexer::getPunct() {

	switch (*c) {
	case '=':
		switch (*peek) {
		case '=':
			next();
			return TokenType::EQUAL;
		default:
			break;
		}
		return TokenType::ASSIGN;
		break;
	case '(':
		return TokenType::LPAREN;
	case ')':
		return TokenType::RPAREN;
	case '{':
		return TokenType::LBRACE;
	case '}':
		return TokenType::RBRACE;
	}

	return TokenType::ERROR;
}


} // namespace nde
