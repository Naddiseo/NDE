#include "ASTree.hpp"
#include "ASTEnums.hpp"

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

#define NodeConstructor(klass, var_name, enum_name) Node::Node(location& _loc, klass* _v) : loc(_loc), type(eNodeType::enum_name) { var_name = _v; _v->loc = _loc; }
	NODETYPE(NodeConstructor)
#undef NodeConstructor

bool
Node::is_expr() const {
#define IS_EXPR(klass, var_name, enum_name) if (is_ ## var_name()) { return true; }
	EXPRTYPE(IS_EXPR);
#undef IS_EXPR
	return false;
}

bool
Node::is_stmt() const {
#define IS_STMT(klass, var_name, enum_name) if (is_ ## var_name()) { return false; }
	EXPRTYPE(IS_STMT);
#undef IS_STMT
	return true;
}


Node::~Node() {
	switch (type) {
#define ENUM_CASE(klass, var_name, enum_name, ...) case eNodeType::enum_name: {  COND_DEL(var_name);  }; break;
	NODETYPE(ENUM_CASE);
#undef ENUM_CASE
	}
}


} // namespace ast
NDESCRIPT_NS_END
