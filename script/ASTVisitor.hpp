#pragma once
#include <functional>
#include "Script.hpp"
#include "ASTEnums.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

class Node;


class Visitor {
public:
	virtual ~Visitor() {}


	virtual void walk(Node* _node);

	virtual void walk(VarType* node) = 0;
	virtual void walk(ExprNode* node) = 0;
	virtual void walk(StmtNode* node) = 0;
	virtual void walk(expr_list_t* node) = 0;
	virtual void walk(stmt_list_t* node) = 0;
	virtual void walk(EmptyExpression* node) = 0;
	virtual void walk(BinaryExpr* node) = 0;
	virtual void walk(TernaryExpr* node) = 0;
	virtual void walk(UnaryExpr* node) = 0;
	virtual void walk(PrimaryExpr* node) = 0;
	virtual void walk(IdentNode* node) = 0;
	virtual void walk(LiteralExpr* node) = 0;
	virtual void walk(AttributeNode* node) = 0;
	virtual void walk(SubscriptNode* node) = 0;
	virtual void walk(FunctionCall* node) = 0;
	virtual void walk(CodeBlock* node) = 0;
	virtual void walk(Decl* node) = 0;
	virtual void walk(VarDecl* node) = 0;
	virtual void walk(declarations_t* node) = 0;
	virtual void walk(vardecls_t* node) = 0;
	virtual void walk(FunctionDecl* node) = 0;
	virtual void walk(ClassDecl* node) = 0;
	virtual void walk(IfStmt* node) = 0;
	virtual void walk(WhileStmt* node) = 0;
	virtual void walk(ForStmt* node) = 0;
	virtual void walk(ExprStmt* node) = 0;
	virtual void walk(ReturnStmt* node) = 0;
	virtual void walk(ContinueStmt* node) = 0;
	virtual void walk(BreakStmt* node) = 0;
};


struct iVisitorNode {
	virtual ~iVisitorNode() {}

	virtual void semAccept(Visitor* visitor) {}
};

} // namespace ast
NDESCRIPT_NS_END
