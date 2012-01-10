#pragma once
#include <vector>
#include <string>
#include "Script.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

enum class eReturnType {
	VOID,
	INT,
	UINT,
	FLOAT,
	VECTOR,
	STRING,
	BOOL,
	OBJECT
};

enum class eDeclType {
	ERROR,
	VAR,
	FUNCTION,
	CLASS
};

enum class eBinaryOp {
	ERROR,
	ASSIGN,
	BORASSIGN,
	BANDASSIGN,
	BXORASSIGN,
	LSHIFTASSIGN,
	RSHIFTASSIGN,
	ADDASSIGN,
	SUBASSIGN,
	MULASSIGN,
	DIVASSIGN,
	MODASSIGN,

	GT,
	LT,
	GTE,
	LTE,

	LSHIFT,
	RSHIFT,

	ADD,
	SUB,

	MUL,
	DIV,
	MOD,

	OR,
	AND,
	BOR,
	BAND,
	BXOR,

	EQUAL,
	NEQUAL,
};

enum class eUnaryType {
	BNOT,
	NOT,
	INC,
	DEC
};

enum class eLiteralType {
	STRINGVAL,
	INTVAL,
	UINTVAL,
	BOOLVAL,
	TRUE,
	FALSE,
	FLOATVAL,
	VECTORVAL,
};


#define NODEFN(klass, var_name, enum_name)

#define NODETYPE \
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
	NODEFN(ContinueStmt, continue_stmt, CONTINUESTMT)
#undef NODEFN

enum class eNodeType {

#define NODEFN(klass, var_name, enum_name) enum_name,
	NODETYPE
#undef NODEFN
};

#define NODEFN(klass, var_name, enum_name) class klass;
NODETYPE
#undef NODEFN

struct Node {
	Node() {}
	virtual ~Node();

	union value_t {
#define NODEFN(klass, var_name, enum_name) klass* var_name;
		NODETYPE
#undef NODEFN
	};

	eNodeType type;
	value_t value;
#define NODEFN(klass, var_name, enum_name) Node(klass* _v) : type(eNodeType::enum_name) { value.var_name = _v; }
	NODETYPE
#undef NODEFN

#define NODEFN(klass, var_name, enum_name) operator klass*() { return value.var_name; }
	NODETYPE
#undef NODEFN

};

typedef std::vector<Node*> node_list_t;

template<typename T>
class NodeList  {
	typedef std::vector<T*> list_t;
	list_t nodes;
public:
	typedef typename std::vector<T*>::iterator iterator;

	virtual ~NodeList() {
		for (T* node : nodes) {
			delete node;
		}
	}

	void push_back(T* node) { nodes.push_back(node); }
	void push_back(Node* node) { nodes.push_back((T*)node); }

	iterator begin() { return nodes.begin(); }
	iterator end() { return nodes.end(); }
};

struct VarType {
	eReturnType type;
	std::string class_name; // if type == OBJECT
	bool is_array;

	VarType(eReturnType _t) : type(_t) {}
	VarType(eReturnType _t, std::string _class) : type(_t), class_name(_class) {}
	virtual ~VarType() {}
};

struct ExprNode {
	virtual ~ExprNode() {}
};
struct StmtNode  {
	virtual ~StmtNode() {}
};

struct expr_list_t : public NodeList<ExprNode> {};
struct stmt_list_t : public NodeList<StmtNode> {};

struct EmptyExpression : public ExprNode {
	virtual ~EmptyExpression() {}
};

struct BinaryExpr : public ExprNode {
	eBinaryOp op;
	Node* lhs;
	Node* rhs;

	virtual ~BinaryExpr() {}

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

	virtual ~TernaryExpr() {}
};

struct UnaryExpr : public ExprNode {
	eUnaryType op;
	Node* expr;

	UnaryExpr(eUnaryType _o, Node* _e)
		: op(_o), expr(_e) {}

	virtual ~UnaryExpr() {}
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
		size_t int_val;
	};
	bool bool_val;
	// Vector vector_val;

	virtual ~LiteralExpr() {}

	LiteralExpr(std::string _s)
		: type(eLiteralType::STRINGVAL), str_val(_s) {}
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

	virtual ~AttributeNode() {}
};

struct SubscriptNode : public PrimaryExpr {
	Node* base;
	Node* subscript;

	SubscriptNode(Node* _b, Node* _sub) : base(_b), subscript(_sub) {}
};

struct FunctionCall : public PrimaryExpr {
	bool is_trigger;
	Node* name;
	Node* arguments;

	FunctionCall(Node* _name, Node* _args) : is_trigger(false), name(_name), arguments(_args) {}
};

struct CodeBlock : public StmtNode {
	Node* children;
};

struct Decl : StmtNode {
	Node* return_type; // the data about the return. eg, if it's void/int/uint
	eDeclType decl_type; // whether it's a function/var/class
	std::string name; // name of the var/function/class

	Decl(Node* _return_type, eDeclType _t, std::string _name)
		: return_type(_return_type), decl_type(_t), name(_name) {}
	virtual ~Decl();
};

struct declarations_t : public NodeList<Decl> {};

struct VarDecl : public Decl {
	Node* default_value;
	VarDecl(Node* _return_type, std::string _name, Node* _default_value)
		: Decl(_return_type, eDeclType::VAR, _name), default_value(_default_value) {}
};

struct vardecls_t : public NodeList<VarDecl> {};

struct FunctionDecl : public Decl {
	bool is_event;
	Node* arguments;
	Node* block;

	FunctionDecl(Node* _return_type, std::string _name, Node* args, Node* b)
		: Decl(_return_type, eDeclType::FUNCTION, _name), is_event(false), arguments(args), block(b) {}

	FunctionDecl(Node* _return_type, std::string _name, bool i_e, Node* args, Node* b)
		: Decl(_return_type, eDeclType::FUNCTION, _name), is_event(i_e), arguments(args), block(b) {}
};

struct ClassDecl : public Decl {
	std::string parent;
	Node* declarations;

	ClassDecl(Node* _return_type, std::string _name, std::string _parent, Node* _decls)
		: Decl(_return_type, eDeclType::CLASS, _name), parent(_parent), declarations(_decls) {}
};

struct IfStmt :  public StmtNode {
	Node* condition;
	Node* true_block;
	Node* false_block;

	IfStmt(Node* _cond, Node* _true) : condition(_cond), true_block(_true), false_block(NULL) {}
	IfStmt(Node* _cond, Node* _true, Node* _false) : condition(_cond), true_block(_true), false_block(_false) {}

	void passDown(Node* block) {
		if (false_block == NULL) {
			false_block = block;
		}
		else {
			false_block->value.if_stmt->passDown(block);
		}
	}
};

struct WhileStmt :  public StmtNode {
	Node* condition;
	Node* block;

	WhileStmt(Node* _cond, Node* _block) : condition(_cond), block(_block) {}
};

struct ForStmt :  public StmtNode {
	Node* begin;
	Node* condition;
	Node* counter;
	Node* block;

	ForStmt(Node* _begin, Node* _cond, Node* _counter, Node* _block)
		: begin(_begin), condition(_cond), counter(_counter), block(_block) {}
};

struct ExprStmt :  public StmtNode {
	Node* expr;

	ExprStmt(Node* _expr) : expr(_expr) {}
};

struct ReturnStmt :  public StmtNode {
	Node* return_val;

	ReturnStmt() : return_val(NULL) {}
	ReturnStmt(Node* rv) : return_val(rv) {}
};

struct BreakStmt : public StmtNode {};
struct ContinueStmt : public StmtNode {};

struct Program {
	node_list_t declarations;
};

} //namespace ast
NDESCRIPT_NS_END


