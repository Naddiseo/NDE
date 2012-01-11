#include "ASTree.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {


ENUM_STR(eReturnType, ReturnTypeEnum)
ENUM_STR(eDeclType, DeclTypeEnum)
ENUM_STR(eBinaryOp, BinOpEnum)
ENUM_STR(eUnaryType, UnaryTypeEnum)
ENUM_STR(eLiteralType, LiteralTypeEnum)

const std::string LISTSEP = ", ";
const std::string STMTSEP = ";\n";

Node::~Node() {
	switch (type) {
#define NODEFN(klass, var_name, enum_name) case eNodeType::enum_name: { delete value.var_name; }; break;
	NODETYPE;
#undef NODEFN
	}
}

void Node::print() {
	switch (type) {
#define NODEFN(klass, var_name, enum_name) case eNodeType::enum_name: { value.var_name->print(); }; break;
	NODETYPE
#undef NODEFN
	default:break;

	}
}


} // namespace ast
NDESCRIPT_NS_END
