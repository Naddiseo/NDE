#pragma once
#include <string>

namespace nde {


enum class TokenType : char {
#	define TOK(x) x,
#	include "toks.def"
#	undef TOK
	__LAST__
};

extern const std::string TOKEN_NAMES[static_cast<size_t>(TokenType::__LAST__)];

} // namespace nde


