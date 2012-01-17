#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "Script.hpp"
#include "ASTVisitor.hpp"
#include "ASTEnums.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

#define COND_DEL(name) { if (name != NULL) { delete name; name = NULL; } }


struct Node {
	Node() {}
	virtual ~Node();

	union {
#define TO_UNION(klass, var_name, enum_name) klass* var_name;
		NODETYPE(TO_UNION)
#undef TO_UNION
	};

	eNodeType type;
#define NodeConstructor(klass, var_name, enum_name) Node(klass* _v) : type(eNodeType::enum_name) { var_name = _v; }
	NODETYPE(NodeConstructor)
#undef NodeConstructor

	bool is_expr() const;
	bool is_stmt() const;
};


template<typename T>
class NodeList : public iVisitorNode  {
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

struct VarType : public iVisitorNode  {
	eReturnType type;
	std::string class_name; // if type == OBJECT
	bool is_array;

	VarType(eReturnType _t) : type(_t) {}
	VarType(eReturnType _t, std::string _class) : type(_t), class_name(_class) {}
	virtual ~VarType() {}
};

struct ExprNode : public iVisitorNode  {
	virtual ~ExprNode() {}
};
struct StmtNode : public iVisitorNode   {
	virtual ~StmtNode() {}
};

struct expr_list_t : public NodeList<Node> {};
struct stmt_list_t : public NodeList<Node> {};

struct EmptyExpression : public ExprNode {
	virtual ~EmptyExpression() {}
};

struct BinaryExpr : public ExprNode {
	eBinaryOp op;
	Node* lhs;
	Node* rhs;

	virtual ~BinaryExpr() { COND_DEL(lhs); COND_DEL(rhs);}

	BinaryExpr() : op(eBinaryOp::ERROR) {}
	BinaryExpr(eBinaryOp _o) : op(_o) {}
	BinaryExpr(Node* _lhs, eBinaryOp _op, Node* _rhs)
		: op(_op), lhs(_lhs), rhs(_rhs) {}
};

struct TernaryExpr : public ExprNode {
	Node* condition;
	Node* true_cond;
	Node* false_cond;

	TernaryExpr(Node* _c, Node* _t, Node* _f)
		: condition(_c), true_cond(_t), false_cond(_f) {}

	virtual ~TernaryExpr() {COND_DEL(condition); COND_DEL(true_cond);COND_DEL(false_cond);}
};

struct UnaryExpr : public ExprNode {
	eUnaryType op;
	Node* expr;

	UnaryExpr(eUnaryType _o, Node* _e)
		: op(_o), expr(_e) {}

	virtual ~UnaryExpr() {COND_DEL(expr);}
};

struct PrimaryExpr : public ExprNode {
	virtual ~PrimaryExpr() {}
};

struct IdentNode : public PrimaryExpr {
	std::string ident;

	IdentNode(std::string _i) : ident(_i) {}

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
		: type(eLiteralType::STRINGVAL) {

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
			: type(eLiteralType::FLOATVAL), flt_val(_f) {}
	LiteralExpr(size_t _i)
			: type(eLiteralType::INTVAL), int_val(_i) {}
	LiteralExpr(bool _b)
			: type(eLiteralType::BOOLVAL), bool_val(_b) {}
	//LiteralExpr(Vector _v)
	//		: type(eLiteralType::STRINGVAL), vector_val(_v) {}

};

struct AttributeNode : public PrimaryExpr {
	Node* lhs;
	Node* ident;

	AttributeNode(Node* _l, Node* _i)
		: lhs(_l), ident(_i) {}

	virtual ~AttributeNode() {COND_DEL(lhs); COND_DEL(ident);}
};

struct SubscriptNode : public PrimaryExpr {
	Node* base;
	Node* subscript;

	SubscriptNode(Node* _b, Node* _sub) : base(_b), subscript(_sub) {}
	virtual ~SubscriptNode() {COND_DEL(base); COND_DEL(subscript);}
};

struct FunctionCall : public PrimaryExpr {
	bool is_trigger;
	Node* name;
	Node* arguments;

	FunctionCall(Node* _name, Node* _args) : is_trigger(false), name(_name), arguments(_args) {}
	virtual ~FunctionCall() {COND_DEL(name); COND_DEL(arguments);}
};

struct CodeBlock : public StmtNode {
	Node* children;

	CodeBlock() : children(NULL) {}
	CodeBlock(Node* _c) : children(_c) {}
	virtual ~CodeBlock() {COND_DEL(children);}
};

struct Decl : StmtNode {
	Node* return_type; // the data about the return. eg, if it's void/int/uint
	eDeclType decl_type; // whether it's a function/var/class
	std::string name; // name of the var/function/class

	Decl(Node* _return_type, eDeclType _t, std::string _name)
		: return_type(_return_type), decl_type(_t), name(_name) {}
	virtual ~Decl() {COND_DEL(return_type);}
};

struct declarations_t : public NodeList<Node> {};

struct VarDecl : public Decl {
	Node* default_value;
	VarDecl(Node* _return_type, std::string _name, Node* _default_value)
		: Decl(_return_type, eDeclType::VAR, _name), default_value(_default_value) {}

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
		: Decl(_return_type, eDeclType::FUNCTION, _name), is_event(false), arguments(args), block(b) {}

	FunctionDecl(Node* _return_type, std::string _name, bool i_e, Node* args, Node* b)
		: Decl(_return_type, eDeclType::FUNCTION, _name), is_event(i_e), arguments(args), block(b) {}

	virtual ~FunctionDecl() {COND_DEL(arguments); COND_DEL(block);}
};

struct ClassDecl : public Decl {
	std::string parent;
	Node* declarations;

	ClassDecl(Node* _return_type, std::string _name, std::string _parent, Node* _decls)
		: Decl(_return_type, eDeclType::CLASS, _name), parent(_parent), declarations(_decls) {}

	virtual ~ClassDecl() {COND_DEL(declarations);}

};

struct IfStmt :  public StmtNode {
	Node* condition;
	Node* true_block;
	Node* false_block;

	IfStmt(Node* _cond, Node* _true) : condition(_cond), true_block(_true), false_block(NULL) {}
	IfStmt(Node* _cond, Node* _true, Node* _false) : condition(_cond), true_block(_true), false_block(_false) {}
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

	WhileStmt(Node* _cond, Node* _block) : condition(_cond), block(_block) {}
	virtual ~WhileStmt() {COND_DEL(condition); COND_DEL(block);}
};

struct ForStmt :  public StmtNode {
	Node* begin;
	Node* condition;
	Node* counter;
	Node* block;

	ForStmt(Node* _begin, Node* _cond, Node* _counter, Node* _block)
		: begin(_begin), condition(_cond), counter(_counter), block(_block) {}

	virtual ~ForStmt() {COND_DEL(begin);COND_DEL(condition);COND_DEL(counter);COND_DEL(block);}
};

struct ExprStmt :  public StmtNode {
	Node* expr;

	ExprStmt(Node* _expr) : expr(_expr) {}

	virtual ~ExprStmt() {COND_DEL(expr);}
};

struct ReturnStmt :  public StmtNode {
	Node* return_val;

	ReturnStmt() : return_val(NULL) {}
	ReturnStmt(Node* rv) : return_val(rv) {}
	virtual ~ReturnStmt() {	if (return_val) { COND_DEL(return_val); } }
};

struct BreakStmt : public StmtNode {
	virtual ~BreakStmt() {}
};
struct ContinueStmt : public StmtNode {
	virtual ~ContinueStmt() {}
};

struct Program : public iVisitorNode {
	Node* declarations;

	virtual ~Program() {
		if (declarations) {
			delete declarations;
		}
		//COND_DEL(declarations);
	}
};

} //namespace ast
NDESCRIPT_NS_END


