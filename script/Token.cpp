#include "script/Token.hpp"
#include <cmath>

namespace nde {

static const float THRESHHOLD = 0.00005;

static const std::string TOKEN_NAMES[static_cast<size_t>(TokenType::__LAST__)] = {
#	define TOK(x) #x,
#	include "toks.hpp"
#	undef TOK
};

Token::Token()
	: type(TokenType::ERROR), lineno(0), charno(0) {}

Token::Token(TokenType _t, size_t _l, size_t _c)
	: type(_t), lineno(_l), charno(_c) {}

Token::Token(TokenType _t, size_t _l, size_t _c, std::string _s)
	: type(_t), lineno(_l), charno(_c), strtype(_s) {}

Token::Token(TokenType _t, size_t _l, size_t _c, int _i)
	: type(_t), lineno(_l), charno(_c), inttype(_i) {}

Token::Token(TokenType _t, size_t _l, size_t _c, float _f)
	: type(_t), lineno(_l), charno(_c), flttype(_f) {}

/*Token::Token(TokenType _t, size_t _l, size_t _c, Vector _v)
	: type(_t), lineno(_l), charno(_c), vectype(_v) {}
*/

Token::~Token() {}


std::string
Token::getName() {
	return TOKEN_NAMES[static_cast<size_t>(type)];
}


bool
Token::isExact(const Token& other) const {
	return (
		(*this == other) && // checks type and value
		(lineno == other.lineno) &&
		(charno == other.charno)
	);
}

bool
Token::operator==(const Token& other) const  {
	bool ret = (type == other.type);

	switch (type) {
	case TokenType::INTVAL:
		ret = ret && (other.inttype == inttype);
		break;
	case TokenType::FLOATVAL:
		ret = ret && (std::abs((float)(other.flttype - flttype)) < THRESHHOLD);
		break;
	case TokenType::STRINGVAL:
	case TokenType::IDENT:
		ret = ret && (other.strtype == strtype);
		break;
	case TokenType::VECTORVAL:
		// ret = ret && (other.vectype == vectype);
		break;
	default:
		break;
	}
	return ret;
}

#ifdef NDEBUG
Token::operator std::string() {
	std::stringstream ss;
	ss << "TOKEN(" << getName() << "," << lineno << "," << charno << ")";

	switch (type) {
	case TokenType::INTVAL:
		ss << "[" << inttype << "]";
		break;
	case TokenType::FLOATVAL:
		ss << "[" << flttype << "]";
		break;
	case TokenType::STRINGVAL:
	case TokenType::IDENT:
		ss << "[" << strtype << "]";
		break;
	case TokenType::VECTORVAL:
		// ret = ret && (other.vectype == vectype);
		break;
	default:
		break;
	}

	return ss.str();
}
#endif

} // namespace nde

