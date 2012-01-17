#pragma once
#include <functional>
#include "Script.hpp"
#include "ASTree.hpp"
#include "ASTVisitor.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

class Visitor;

class Printer : public Visitor {
	size_t tabs;
	void tab();
	typedef std::function<void(Node*, bool, std::string, bool)> printlist_callback_t;
public:
	Printer();
	virtual ~Printer();

	template<typename T>
	void printlist(T _nodelist, std::string sep= ", ", bool print_last = false, bool indent = false, printlist_callback_t callback = NULL) {
		static printlist_callback_t default_callback = [](Node* node, bool is_last, std::string sep, bool print_last) {
			if (!is_last || print_last) {
				std::cout << sep;
			}
		};

		if (!callback) {
			callback = default_callback;
		}

		for (Node* node : *_nodelist) {
			if (indent) {
				tab();
			}

			Visitor::walk(node);

			callback(node, node == _nodelist->back(), sep, print_last);

		}
	}

	using Visitor::walk;

	virtual void walk(VarType* _node);
	virtual void walk(ExprNode* _node);
	virtual void walk(StmtNode* _node);
	virtual void walk(expr_list_t* _node);
	virtual void walk(stmt_list_t* _node);
	virtual void walk(EmptyExpression* _node);
	virtual void walk(BinaryExpr* _node);
	virtual void walk(TernaryExpr* _node);
	virtual void walk(UnaryExpr* _node);
	virtual void walk(PrimaryExpr* _node);
	virtual void walk(IdentNode* _node);
	virtual void walk(LiteralExpr* _node);
	virtual void walk(AttributeNode* _node);
	virtual void walk(SubscriptNode* _node);
	virtual void walk(FunctionCall* _node);
	virtual void walk(CodeBlock* _node);
	virtual void walk(Decl* _node);
	virtual void walk(VarDecl* _node);
	virtual void walk(declarations_t* _node);
	virtual void walk(vardecls_t* _node);
	virtual void walk(FunctionDecl* _node);
	virtual void walk(ClassDecl* _node);
	virtual void walk(IfStmt* _node);
	virtual void walk(WhileStmt* _node);
	virtual void walk(ForStmt* _node);
	virtual void walk(ExprStmt* _node);
	virtual void walk(ReturnStmt* _node);
	virtual void walk(ContinueStmt* _node);
	virtual void walk(BreakStmt* _node);

};

} // namespace ast
NDESCRIPT_NS_END


