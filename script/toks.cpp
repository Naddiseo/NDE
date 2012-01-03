#include <string>
#include <script/toks.hpp>
namespace nde {


const std::string TOKEN_NAMES[static_cast<size_t>(TokenType::__LAST__)] = {
#	define TOK(x) #x,
#	include "toks.def"
#	undef TOK
};


} // namespace nde

