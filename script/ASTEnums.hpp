#pragma once
#include <iostream>
#include "Script.hpp"
/*
 * ASTEnums.hpp
 *
 *  Created on: 2012-01-15
 *      Author: richard
 */


NDESCRIPT_NS_BEGIN
namespace ast {


#define ENUM_INNER(x) x,
#define ENUM_INNER_STR(x) #x,

#define ENUM(name, klass, inner) \
	enum class name : klass { inner(ENUM_INNER)  LAST }; \
	extern const char* name##_str[]; \
	std::ostream& operator<<(std::ostream &, name);

#define ENUM_STR(name, inner) \
	const char* name##_str[static_cast<size_t>(name::LAST)] = { inner(ENUM_INNER_STR) }; \
	std::ostream& operator<<(std::ostream & out, name e) { return out << name##_str[static_cast<size_t>(e)]; }

#define ReturnTypeEnum(X) \
	X(VOID) \
	X(INT) \
	X(UINT) \
	X(FLOAT) \
	X(VECTOR) \
	X(STRING) \
	X(BOOL) \
	X(OBJECT)
ENUM(eReturnType, char, ReturnTypeEnum)

#define DeclTypeEnum(X) \
	X(ERROR) \
	X(VAR) \
	X(FUNCTION) \
	X(CLASS)
ENUM(eDeclType, char, DeclTypeEnum)

#define BinOpEnum(X) \
	X(ERROR) \
	X(ASSIGN) \
	X(BORASSIGN) \
	X(BANDASSIGN) \
	X(BXORASSIGN) \
	X(LSHIFTASSIGN) \
	X(RSHIFTASSIGN) \
	X(ADDASSIGN) \
	X(SUBASSIGN) \
	X(MULASSIGN) \
	X(DIVASSIGN) \
	X(MODASSIGN) \
	X(GT) \
	X(LT) \
	X(GTE) \
	X(LTE) \
	X(LSHIFT) \
	X(RSHIFT) \
	X(ADD) \
	X(SUB) \
	X(MUL) \
	X(DIV) \
	X(MOD) \
	X(OR) \
	X(AND) \
	X(BOR) \
	X(BAND) \
	X(BXOR) \
	X(EQUAL) \
	X(NEQUAL)
ENUM(eBinaryOp, char, BinOpEnum)

#define UnaryTypeEnum(X) \
	X(BNOT) \
	X(NOT) \
	X(INC) \
	X(DEC) \
	X(SUB)
ENUM(eUnaryType, char, UnaryTypeEnum)

#define LiteralTypeEnum(X) \
	X(ERROR) \
	X(STRINGVAL) \
	X(INTVAL) \
	X(UINTVAL) \
	X(BOOLVAL) \
	X(TRUE) \
	X(FALSE) \
	X(FLOATVAL) \
	X(VECTORVAL)
ENUM(eLiteralType, char, LiteralTypeEnum)


#define NODETYPE(NODEFN) \
	NODEFN(VarType, var_type, VARTYPE) \
	NODEFN(ExprNode, expr_node, EXPRNODE) \
	NODEFN(StmtNode, stmt_node, STMTNODE) \
	NODEFN(expr_list_t, expr_list, EXPRLIST) \
	NODEFN(stmt_list_t, stmt_list, STMTLIST) \
	NODEFN(EmptyExpression, empty_expression, EMPTYEXPRESSION) \
	NODEFN(BinaryExpr, bin_expr, BINEXPR) \
	NODEFN(TernaryExpr, ternary_expr, TERNARYEXPR) \
	NODEFN(UnaryExpr, unary_expr, UNARYEXPR) \
	NODEFN(PrimaryExpr, primary_expr, PRIMARYEXPR) \
	NODEFN(IdentNode, ident_node, IDENTNODE) \
	NODEFN(LiteralExpr, literal_expr, LITERALEXPR) \
	NODEFN(AttributeNode, attribute_node, ATTRIBUTENODE) \
	NODEFN(SubscriptNode, subscript_node, SUBSCRIPTNODE) \
	NODEFN(FunctionCall, function_call, FUNCTIONCALL) \
	NODEFN(CodeBlock, code_block, CODEBLOCK) \
	NODEFN(Decl, decl_node, DECLNODE) \
	NODEFN(VarDecl, var_decl, VARDECL) \
	NODEFN(declarations_t, declarations, DECLARATIONS) \
	NODEFN(vardecls_t, var_decls, VARDECLS) \
	NODEFN(FunctionDecl, function_decl, FUNCTIONDECL) \
	NODEFN(ClassDecl, class_decl, CLASSDECL) \
	NODEFN(IfStmt, if_stmt, IFSTMT) \
	NODEFN(WhileStmt, while_stmt, WHILESTMT) \
	NODEFN(ForStmt, for_stmt, FORSTMT) \
	NODEFN(ExprStmt, expr_stmt, EXPRSTMT) \
	NODEFN(ReturnStmt, return_stmt, RETURNSTMT) \
	NODEFN(ContinueStmt, continue_stmt, CONTINUESTMT) \
	NODEFN(BreakStmt, break_stmt, BREAKSTMT)

enum class eNodeType {
#define TO_ENUM(klass, var_name, enum_name) enum_name,
	NODETYPE(TO_ENUM)
#undef TO_ENUM
};

extern const char* eNodeType_str[];
std::ostream& operator<<(std::ostream &, eNodeType);

#define CLASS_FORWARD(klass, var_name, enum_name, ...) class klass;
	NODETYPE(CLASS_FORWARD)
#undef CLASS_FORWARD

} //namespace ast
NDESCRIPT_NS_END
