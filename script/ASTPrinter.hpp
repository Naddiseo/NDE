#pragma once
#include <functional>
#include "Script.hpp"
#include "ASTree.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

class ASTPrinter {
	size_t tabs;
	void tab();
	typedef std::function<void(Node*, bool, std::string, bool)> printlist_callback_t;
public:
	ASTPrinter();
	virtual ~ASTPrinter();

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
			print(node);

			callback(node, node == _nodelist->back(), sep, print_last);

		}
	}

	void print(Node* _node);
	void print(VarType* _node);
	void print(ExprNode* _node);
	void print(StmtNode* _node);
	void print(expr_list_t* _node);
	void print(stmt_list_t* _node);
	void print(EmptyExpression* _node);
	void print(BinaryExpr* _node);
	void print(TernaryExpr* _node);
	void print(UnaryExpr* _node);
	void print(PrimaryExpr* _node);
	void print(IdentNode* _node);
	void print(LiteralExpr* _node);
	void print(AttributeNode* _node);
	void print(SubscriptNode* _node);
	void print(FunctionCall* _node);
	void print(CodeBlock* _node);
	void print(Decl* _node);
	void print(VarDecl* _node);
	void print(declarations_t* _node);
	void print(vardecls_t* _node);
	void print(FunctionDecl* _node);
	void print(ClassDecl* _node);
	void print(IfStmt* _node);
	void print(WhileStmt* _node);
	void print(ForStmt* _node);
	void print(ExprStmt* _node);
	void print(ReturnStmt* _node);
	void print(ContinueStmt* _node);
	void print(BreakStmt* _node);

};

} // namespace ast
NDESCRIPT_NS_END


