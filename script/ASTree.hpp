#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "location.hh"
#include "Script.hpp"
#include "ASTVisitor.hpp"
#include "ASTEnums.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

#define COND_DEL(name) { if (name != NULL) { delete name; name = NULL; } }


struct LocationMixinNode {
	location loc;

	LocationMixinNode() {}
	LocationMixinNode(location& _loc) : loc(_loc) {}
};

struct Node {
	virtual ~Node();

	const location& loc;

	union {
#define TO_UNION(klass, var_name, enum_name) klass* var_name;
		NODETYPE(TO_UNION)
#undef TO_UNION
	};

	eNodeType type;
#define NodeConstructorForward(klass, var_name, enum_name) Node(location& _loc, klass* _v);
	NODETYPE(NodeConstructorForward)
#undef NodeConstructorForward

	bool is_expr() const;
	bool is_stmt() const;

#define NodeIsFunction(klass, var_name, enum_name) bool is_ ## var_name() const { return type == eNodeType::enum_name; }
	NODETYPE(NodeIsFunction)
#undef NodeIsFunction
};

template<typename T>
class NodeList : public iVisitorNode, public LocationMixinNode  {
	std::vector<T*> nodes;
public:
	typedef typename std::vector<T*>::iterator iterator;
	typedef typename std::vector<T*>::const_reference const_reference;

	virtual ~NodeList() {
		for (T* node : nodes) {
			delete node;
			node = NULL;
		}
	}

	void push_back(T* node) { nodes.push_back(node); }

	iterator begin() { return nodes.begin(); }
	iterator end() { return nodes.end(); }
	size_t size() const { return nodes.size(); }
	const_reference back() const { return nodes.back(); }
};

struct VarType : public iVisitorNode, public LocationMixinNode  {
	eReturnType type;
	std::string class_name; // if type == OBJECT
	bool is_array;

	VarType(eReturnType _t) : type(_t), class_name(), is_array(false) {}
	VarType(eReturnType _t, std::string _class) : type(_t), class_name(_class), is_array(false) {}
	virtual ~VarType() {}
};

struct ExprNode : public iVisitorNode, public LocationMixinNode  {
	eExprType type;
	ExprNode(eExprType _type) : type(_type) {}
	virtual ~ExprNode() {}
};
struct StmtNode : public iVisitorNode, public LocationMixinNode   {
	eStmtType type;
	StmtNode(eStmtType _type) : type(_type) {}
	virtual ~StmtNode() {}
};

struct expr_list_t : public NodeList<Node> {};
struct stmt_list_t : public NodeList<Node> {};

struct EmptyExpression : public ExprNode {
	EmptyExpression() : ExprNode(eExprType::EMPTYEXPRESSION) {}
	virtual ~EmptyExpression() {}
};

struct BinaryExpr : public ExprNode {
	eBinaryOp op;
	Node* lhs;
	Node* rhs;

	virtual ~BinaryExpr() { COND_DEL(lhs); COND_DEL(rhs);}

	BinaryExpr(Node* _lhs, eBinaryOp _op, Node* _rhs, eExprType _type = eExprType::BINEXPR)
		: ExprNode(_type), op(_op), lhs(_lhs), rhs(_rhs) {}
};

struct TernaryExpr : public ExprNode {
	Node* condition;
	Node* true_cond;
	Node* false_cond;

	TernaryExpr(Node* _c, Node* _t, Node* _f, eExprType _type = eExprType::TERNARYEXPR)
	: ExprNode(_type),condition(_c), true_cond(_t), false_cond(_f) {}

	virtual ~TernaryExpr() {COND_DEL(condition); COND_DEL(true_cond);COND_DEL(false_cond);}
};

struct UnaryExpr : public ExprNode {
	eUnaryType op;
	Node* expr;

	UnaryExpr(eUnaryType _o, Node* _e, eExprType _type = eExprType::UNARYEXPR)
		: ExprNode(eExprType::UNARYEXPR), op(_o), expr(_e) {}

	virtual ~UnaryExpr() {COND_DEL(expr);}
};

struct PrimaryExpr : public ExprNode {
	PrimaryExpr(eExprType _type = eExprType::PRIMARYEXPR) : ExprNode(_type) {}
	virtual ~PrimaryExpr() {}
};

struct IdentNode : public PrimaryExpr {
	std::string ident;

	IdentNode(std::string _i) : PrimaryExpr(eExprType::IDENTNODE),ident(_i) {}

	virtual ~IdentNode() {}
};

struct LiteralExpr : public PrimaryExpr {
	eLiteralType type;
	std::string str_val;
	union {
		float flt_val;
		int int_val;
	};
	bool bool_val;
	// Vector vector_val;

	virtual ~LiteralExpr() {}

	LiteralExpr(char* _s)
		: PrimaryExpr(eExprType::LITERALEXPR), type(eLiteralType::STRINGVAL), bool_val(false) {

		register char* c = _s;
		bool running = true;
		while (running) {
			switch (*c) {
			case 0:
				running = false;
				break;
			case '\\':
				c++;
				if (*c == 0) {
					type = eLiteralType::ERROR;
					str_val = "End of string found after escape sequence";
					running = false;
					break;
				}
				else {
					switch (*c) {
					case 'n':
						str_val += '\n';
						break;
					case 'r':
						str_val += '\r';
						break;
					case 't':
						str_val += '\t';
						break;
					default:
						str_val += *c;
						break;
					}
					c++;
				}
				break;
			default:
				str_val += *c++;
				break;
			}
		}

	}
	LiteralExpr(float _f)
			:  PrimaryExpr(eExprType::LITERALEXPR), type(eLiteralType::FLOATVAL), flt_val(_f), bool_val(false) {}
	LiteralExpr(size_t _i)
			: PrimaryExpr(eExprType::LITERALEXPR), type(eLiteralType::INTVAL), int_val(_i), bool_val(false) {}
	LiteralExpr(bool _b)
			: PrimaryExpr(eExprType::LITERALEXPR), type(eLiteralType::BOOLVAL), bool_val(_b) {}
	//LiteralExpr(Vector _v)
	//		: PrimaryExpr(eExprType::LITERALEXPR), type(eLiteralType::STRINGVAL), vector_val(_v) {}

};

struct AttributeNode : public PrimaryExpr {
	Node* lhs;
	Node* ident;

	AttributeNode(Node* _l, Node* _i)
		: PrimaryExpr(eExprType::ATTRIBUTENODE), lhs(_l), ident(_i) {}

	virtual ~AttributeNode() {COND_DEL(lhs); COND_DEL(ident);}
};

struct SubscriptNode : public PrimaryExpr {
	Node* base;
	Node* subscript;

	SubscriptNode(Node* _b, Node* _sub)
		: PrimaryExpr(eExprType::SUBSCRIPTNODE), base(_b), subscript(_sub) {}
	virtual ~SubscriptNode() {COND_DEL(base); COND_DEL(subscript);}
};

struct FunctionCall : public PrimaryExpr {
	bool is_trigger;
	Node* name;
	Node* arguments;

	FunctionCall(Node* _name, Node* _args)
		: PrimaryExpr(eExprType::FUNCTIONCALL), is_trigger(false), name(_name), arguments(_args)  {}

	virtual ~FunctionCall() {COND_DEL(name); COND_DEL(arguments);}
};

struct CodeBlock : public StmtNode {
	Node* children;

	CodeBlock(Node* _c = NULL) :  StmtNode(eStmtType::CODEBLOCK), children(_c) {}
	virtual ~CodeBlock() {COND_DEL(children);}
};

struct Decl : StmtNode {
	Node* return_type; // the data about the return. eg, if it's void/int/uint
	eDeclType decl_type; // whether it's a function/var/class
	std::string name; // name of the var/function/class

	Decl(Node* _return_type, eDeclType _t, std::string _name, eStmtType _type = eStmtType::DECLNODE)
		: StmtNode(_type), return_type(_return_type), decl_type(_t), name(_name) {}
	virtual ~Decl() {COND_DEL(return_type);}
};

struct declarations_t : public NodeList<Node> {};

struct VarDecl : public Decl {
	Node* default_value;
	VarDecl(Node* _return_type, std::string _name, Node* _default_value)
		: Decl(_return_type, eDeclType::VAR, _name, eStmtType::VARDECL), default_value(_default_value) {}

	inline eReturnType get_return_type() const { return return_type->var_type->type; }
	inline bool is_array() const { return return_type->var_type->is_array; }

	virtual ~VarDecl() {COND_DEL(default_value);}
};

struct vardecls_t : public NodeList<Node> {};

struct FunctionDecl : public Decl {
	bool is_event;
	Node* arguments;
	Node* block;

	FunctionDecl(Node* _return_type, std::string _name, Node* args, Node* b)
		: Decl(_return_type, eDeclType::FUNCTION, _name, eStmtType::FUNCTIONDECL), is_event(false), arguments(args), block(b) {}

	FunctionDecl(Node* _return_type, std::string _name, bool i_e, Node* args, Node* b)
		: Decl(_return_type, eDeclType::FUNCTION, _name, eStmtType::FUNCTIONDECL), is_event(i_e), arguments(args), block(b) {}

	virtual ~FunctionDecl() {COND_DEL(arguments); COND_DEL(block);}
};

struct ClassDecl : public Decl {
	std::string parent;
	Node* declarations;

	ClassDecl(Node* _return_type, std::string _name, std::string _parent, Node* _decls)
		: Decl(_return_type, eDeclType::CLASS, _name, eStmtType::CLASSDECL), parent(_parent), declarations(_decls) {}

	virtual ~ClassDecl() {COND_DEL(declarations);}

};

struct IfStmt :  public StmtNode {
	Node* condition;
	Node* true_block;
	Node* false_block;

	IfStmt(Node* _cond, Node* _true, Node* _false = NULL)
	:  StmtNode(eStmtType::IFSTMT), condition(_cond), true_block(_true), false_block(_false) {}

	virtual ~IfStmt() {COND_DEL(condition); COND_DEL(true_block); COND_DEL(false_block);}

	void passDown(Node* block) {
		if (false_block == NULL) {
			false_block = block;
		}
		else if (false_block->type == eNodeType::IFSTMT) {
			false_block->if_stmt->passDown(block);
		}
		else if (block->type == eNodeType::IFSTMT) {
			block->if_stmt->passDown(false_block);
			false_block = block;
		}
		else{
			COND_DEL(block);
			//std::cerr << "Got block of type " << block->type << std::endl;
			//std::cerr << "Got false_block of type " << false_block->type << std::endl;
		}
	}
};

struct WhileStmt :  public StmtNode {
	Node* condition;
	Node* block;

	WhileStmt(Node* _cond, Node* _block)
		: StmtNode(eStmtType::WHILESTMT), condition(_cond), block(_block) {}
	virtual ~WhileStmt() {COND_DEL(condition); COND_DEL(block);}
};

struct ForStmt :  public StmtNode {
	Node* begin;
	Node* condition;
	Node* counter;
	Node* block;

	ForStmt(Node* _begin, Node* _cond, Node* _counter, Node* _block)
		: StmtNode(eStmtType::FORSTMT), begin(_begin), condition(_cond), counter(_counter), block(_block) {}

	virtual ~ForStmt() {COND_DEL(begin);COND_DEL(condition);COND_DEL(counter);COND_DEL(block);}
};

struct ExprStmt :  public StmtNode {
	Node* expr;

	ExprStmt(Node* _expr)
		: StmtNode(eStmtType::EXPRSTMT),  expr(_expr) {}

	virtual ~ExprStmt() {COND_DEL(expr);}
};

struct ReturnStmt :  public StmtNode {
	Node* return_val;

	ReturnStmt(Node* rv = NULL)
		: StmtNode(eStmtType::RETURNSTMT),  return_val(rv) {}
	virtual ~ReturnStmt() {	if (return_val) { COND_DEL(return_val); } }
};

struct BreakStmt : public StmtNode {
	BreakStmt() : StmtNode(eStmtType::BREAKSTMT) {}
	virtual ~BreakStmt() {}
};
struct ContinueStmt : public StmtNode {
	ContinueStmt() : StmtNode(eStmtType::CONTINUESTMT) {}
	virtual ~ContinueStmt() {}
};

struct Program : public iVisitorNode {
	Node* declarations;

	Program() : declarations(NULL) {}

	virtual ~Program() {
		COND_DEL(declarations);
	}
};

} //namespace ast
NDESCRIPT_NS_END


