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


#define STMTTYPE(X) \
	X(StmtNode, stmt_node, STMTNODE) \
	X(CodeBlock, code_block, CODEBLOCK) \
	X(IfStmt, if_stmt, IFSTMT) \
	X(WhileStmt, while_stmt, WHILESTMT) \
	X(ForStmt, for_stmt, FORSTMT) \
	X(ExprStmt, expr_stmt, EXPRSTMT) \
	X(ReturnStmt, return_stmt, RETURNSTMT) \
	X(ContinueStmt, continue_stmt, CONTINUESTMT) \
	X(BreakStmt, break_stmt, BREAKSTMT)

#define EXPRTYPE(X) \
	X(ExprNode, expr_node, EXPRNODE) \
	X(EmptyExpression, empty_expression, EMPTYEXPRESSION) \
	X(BinaryExpr, bin_expr, BINEXPR) \
	X(TernaryExpr, ternary_expr, TERNARYEXPR) \
	X(UnaryExpr, unary_expr, UNARYEXPR) \
	X(PrimaryExpr, primary_expr, PRIMARYEXPR) \
	X(LiteralExpr, literal_expr, LITERALEXPR) \
	X(AttributeNode, attribute_node, ATTRIBUTENODE) \
	X(SubscriptNode, subscript_node, SUBSCRIPTNODE) \
	X(FunctionCall, function_call, FUNCTIONCALL) \
	X(IdentNode, ident_node, IDENTNODE) \
	X(ArrayNode, array_node, ARRAYNODE)

#define LISTTYPE(X) \
	X(expr_list_t, expr_list, EXPRLIST) \
	X(stmt_list_t, stmt_list, STMTLIST) \
	X(vardecls_t, var_decls, VARDECLS) \
	X(declarations_t, declarations, DECLARATIONS)

#define DECLTYPE(X) \
	X(Decl, decl_node, DECLNODE) \
	X(VarDecl, var_decl, VARDECL) \
	X(FunctionDecl, function_decl, FUNCTIONDECL) \
	X(ClassDecl, class_decl, CLASSDECL)

#define NODETYPE(X) \
	EXPRTYPE(X) \
	STMTTYPE(X) \
	LISTTYPE(X) \
	DECLTYPE(X) \
	X(VarType, var_type, VARTYPE)

#define TO_ENUM(klass, var_name, enum_name) enum_name,

enum class eNodeType {
	NODETYPE(TO_ENUM)
};

enum class eStmtType {
	STMTTYPE(TO_ENUM)
	DECLTYPE(TO_ENUM)
};

enum class eExprType {
	EXPRTYPE(TO_ENUM)
};

#undef TO_ENUM

extern const char* eNodeType_str[];
std::ostream& operator<<(std::ostream &, eNodeType);

#define CLASS_FORWARD(klass, var_name, enum_name, ...) class klass;
	NODETYPE(CLASS_FORWARD)
#undef CLASS_FORWARD

} //namespace ast
NDESCRIPT_NS_END
