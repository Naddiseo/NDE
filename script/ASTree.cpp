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
#define ENUM_CASE(klass, var_name, enum_name) case eNodeType::enum_name: { /* delete var_name; */ }; break;
	NODETYPE(ENUM_CASE);
#undef ENUM_CASE
	}
}

void Node::print() {
	switch (type) {
#define ENUM_CASE(klass, var_name, enum_name) case eNodeType::enum_name: { var_name->print(); }; break;
	NODETYPE(ENUM_CASE)
#undef ENUM_CASE
	default:break;

	}
}


} // namespace ast
NDESCRIPT_NS_END
