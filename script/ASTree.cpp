#include "ASTree.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {


ENUM_STR(eReturnType, ReturnTypeEnum)
ENUM_STR(eDeclType, DeclTypeEnum)
ENUM_STR(eBinaryOp, BinOpEnum)
ENUM_STR(eUnaryType, UnaryTypeEnum)
ENUM_STR(eLiteralType, LiteralTypeEnum)

const char* eNodeType_str[] = {
#define NODEFN(klass, var_name, enum_name, ...) #enum_name,
	NODETYPE(NODEFN)
#undef NODEFN
};

std::ostream& operator<<(std::ostream & out, eNodeType e) {
	 return out << eLiteralType_str[static_cast<size_t>(e)];
}

Node::~Node() {
	switch (type) {
#define ENUM_CASE(klass, var_name, enum_name, ...) case eNodeType::enum_name: {  delete var_name;  }; break;
	NODETYPE(ENUM_CASE);
#undef ENUM_CASE
	}
}


} // namespace ast
NDESCRIPT_NS_END
