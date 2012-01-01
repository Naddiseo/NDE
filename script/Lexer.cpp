#include <cctype>
#include <sstream>
#include <cstring>
#include <iostream>
#include <map>
#include "script/Lexer.hpp"

namespace nde {

static std::map<std::string, TokenType> keywords = {
	{"int", TokenType::INT},
	{"uint", TokenType::UINT},
	{"float", TokenType::FLOAT},
	{"string", TokenType::STRING},
	{"vector", TokenType::VECTOR},
	{"bool", TokenType::BOOL},
	{"void", TokenType::VOID},
	{"and", TokenType::AND},
	{"or", TokenType::OR},
	{"if", TokenType::IF},
	{"while", TokenType::WHILE},
	{"for", TokenType::FOR},
	{"break", TokenType::BREAK},
	{"continue", TokenType::CONTINUE},
	{"else", TokenType::ELSE},
	{"true", TokenType::TRUE},
	{"false", TokenType::FALSE},
};

typedef std::map<std::string, TokenType>::iterator kw_t;

Lexer::Lexer() : lineno(1), charno(1), haserror(false) {}

Lexer::~Lexer() {}

bool
Lexer::lex(const std::string& _program) {
#define SAVE _lineno = lineno; _charno = charno;
#define TOK(t) tokens.push_back({t, _lineno, _charno});// std::cerr << Token(t, 0, 0).getName() << std::endl;
#define TOKV(t, v) tokens.push_back({t, _lineno, _charno, v});//  std::cerr << Token(t, 0, 0).getName() << std::endl;
	size_t _lineno, _charno;
	if (_program.size() < MIN_SCRIPT_LENGTH) {
		return false;
	}

	program = _program.c_str();
	program_end = const_cast<char*>(program + _program.size());
	c = const_cast<char*>(program);
	peek = c + 1;

	while (c != NULL) {
		//std::cerr << "STEP: " << c << std::endl;
		skipWhite();
		SAVE;
		if (!c) break;
		if (isAlpha() || *c == '_') {
			std::string ident = getIdent();
			kw_t kw = keywords.find(ident);
			if (kw == keywords.end()) {
				TOKV(TokenType::IDENT, ident);
			}
			else {
				TOK(kw->second);
			}
		}
		else if (*c == '"') { // must come before isPunct
			TOKV(TokenType::STRINGVAL, getString());
		}
		else if (isPunct()) {
			TOK(getPunct());
			next();
		}
		else if (isNumeric()) {
			TokenType t = TokenType::INTVAL;
			number_t n = getNumber(t);
			if (t == TokenType::INTVAL) {
				TOKV(t, n.i);
			}
			else {
				TOKV(t, n.f);
			}
		}
		else {
			std::cerr << " ERROR " << std::endl;
		}
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

	if (*++c == '\n') {
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

void
Lexer::backup(size_t count) {
	c -= count;
	if (c < program) {
		c = const_cast<char*>(program);
	}
	peek = c + 1;
}

bool Lexer::isWhite() const { return std::isspace(*c) || std::iscntrl(*c); }
bool Lexer::isAlpha() const { return std::isalpha(*c); }
bool Lexer::isNumeric() const { return std::isdigit(*c); }
bool Lexer::isAlNum() const { return std::isalnum(*c); }
bool Lexer::isPunct() const { return std::ispunct(*c); }

bool
Lexer::expect(char expected_char) {
	if (expected_char == *c) {
		next();
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
		while (isAlNum() || *c == '_') {
			buf += *c;
			next();
		}
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
		}
		return TokenType::ASSIGN;

	case '!':
		switch (*peek) {
		case '=':
			next();
			return TokenType::NEQUAL;
		}
		return TokenType::NOT;

	case '<':
		switch (*peek) {
		case '=':
			next();
			return TokenType::LTE;
		case '<':
			next();
			switch (*peek) {
			case '=':
				next();
				return TokenType::LSHIFTASSIGN;
			}
			return TokenType::LSHIFT;
		}
		return TokenType::LT;

	case '>':
		switch (*peek) {
		case '=':
			next();
			return TokenType::GTE;
		case '>':
			next();
			switch (*peek) {
			case '=':
				next();
				return TokenType::RSHIFTASSIGN;
			}
			return TokenType::RSHIFT;
		}
		return TokenType::GT;

	case '|':
		switch (*peek) {
		case '=':
			next();
			return TokenType::BORASSIGN;
		case '|':
			next();
			return TokenType::OR;
		}
		return TokenType::BOR;

	case '&':
		switch (*peek) {
		case '=':
			next();
			return TokenType::BANDASSIGN;
		case '&':
			next();
			return TokenType::AND;
		}
		return TokenType::BAND;

	case '^':
		switch (*peek) {
		case '=':
			next();
			return TokenType::BXORASSIGN;
		}
		return TokenType::BXOR;

	case '+':
		switch (*peek) {
		case '=':
			next();
			return TokenType::ADDASSIGN;
		case '+':
			next();
			return TokenType::INC;
		}
		return TokenType::ADD;

	case '-':
		switch (*peek) {
		case '=':
			next();
			return TokenType::SUBASSIGN;
		case '-':
			next();
			return TokenType::DEC;
		}
		return TokenType::SUB;

	case '*':
		switch (*peek) {
		case '=':
			next();
			return TokenType::MULASSIGN;
		}
		return TokenType::MUL;

	case '/':
		switch (*peek) {
		case '=':
			next();
			return TokenType::DIVASSIGN;
		}
		return TokenType::DIV;

	case '.':
		return TokenType::DOT;

	case '~':
		return TokenType::BNOT;

	case ',':
		return TokenType::COMMA;

	case '(':
		return TokenType::LPAREN;

	case ')':
		return TokenType::RPAREN;

	case '{':
		return TokenType::LBRACE;

	case '}':
		return TokenType::RBRACE;

	case ';':
		return TokenType::SEMICOLON;
	}

	setError(std::string("Unknown Operator '") + *c + "'");
	return TokenType::ERROR;
}

Lexer::number_t
Lexer::getNumber(TokenType& t) {
	std::stringstream ss;
	const size_t bufsize = 20;
	size_t i = 0;
	char buf[bufsize];
	char* bufptr = buf;
	number_t ret;
	ret.i = 0;
	t = TokenType::INTVAL;

	std::memset(buf, 0, bufsize);

	while (isNumeric() && i++ < bufsize) {
		*bufptr++ = *c;
		next();
	}

	if (*c == '.') {
		t = TokenType::FLOATVAL;
		*bufptr++ = *c;
		next();
		i++;
		while (isNumeric() && i++ < bufsize) {
			*bufptr++ = *c;
			next();
		}
	}

	ss << buf;

	if (t == TokenType::INTVAL) {
		ss >> ret.i;
	}
	else {
		ss >> ret.f;
	}

	return ret;
}

std::string
Lexer::getString() {
	std::string ret;

	expect('"');

	while (c && *c != '"') {
		switch (*c) {
		case '\\':
			switch (*peek) {
			case '\\':
				ret += '\\';
				break;
			case 'n':
				ret += '\n';
				break;
			case 'r':
				ret += '\r';
				break;
			case 't':
				ret += '\t';
				break;
			case '"':
				ret += '"';
				break;
			default:
				ret += *peek;
				break;
			}
			next();
			break;
		default:
			ret += *c;
			break;
		}
		next();
	}

	expect('"');


	return ret;
}

} // namespace nde
