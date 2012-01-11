#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Script.hpp"

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
	X(DEC)
ENUM(eUnaryType, char, UnaryTypeEnum)

#define LiteralTypeEnum(X) \
	X(STRINGVAL) \
	X(INTVAL) \
	X(UINTVAL) \
	X(BOOLVAL) \
	X(TRUE) \
	X(FALSE) \
	X(FLOATVAL) \
	X(VECTORVAL)
ENUM(eLiteralType, char, LiteralTypeEnum)

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

	void print();
};

typedef std::vector<Node*> node_list_t;

extern const std::string LISTSEP;
extern const std::string STMTSEP;

template<typename T, const std::string& sep = LISTSEP>
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

	void print() {
		for (T* node : nodes) {
			node->print();
			std::cout << sep;
		}
	}
};

struct VarType {
	eReturnType type;
	std::string class_name; // if type == OBJECT
	bool is_array;

	VarType(eReturnType _t) : type(_t) {}
	VarType(eReturnType _t, std::string _class) : type(_t), class_name(_class) {}
	virtual ~VarType() {}

	void print() {
		if (type == eReturnType::OBJECT) {
			std::cout << class_name;
		}
		else {
			std::cout << type;
		}

		std::cout << ((is_array) ? "[] " : " ");
	}
};

struct ExprNode {
	virtual ~ExprNode() {}

	virtual void print() {}
};
struct StmtNode  {
	virtual ~StmtNode() {}
	virtual void print() {}
};

struct expr_list_t : public NodeList<ExprNode> {};
struct stmt_list_t : public NodeList<StmtNode, STMTSEP> {};

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

	void print() {
		std::cout << "((";
			lhs->print();
		std::cout << ")" << op << "(";
			rhs->print();
		std::cout << "))";
	}
};

struct TernaryExpr : public ExprNode {
	Node* condition;
	Node* true_cond;
	Node* false_cond;

	TernaryExpr(Node* _c, Node* _t, Node* _f)
		: condition(_c), true_cond(_t), false_cond(_f) {}

	virtual ~TernaryExpr() {}

	void print() {
		std::cout << "((";
			condition->print();
		std::cout << ") ? (";
			true_cond->print();
		std::cout << ") : (";
			false_cond->print();
		std::cout << "))";
	}
};

struct UnaryExpr : public ExprNode {
	eUnaryType op;
	Node* expr;

	UnaryExpr(eUnaryType _o, Node* _e)
		: op(_o), expr(_e) {}

	virtual ~UnaryExpr() {}

	void print() {
		std::cout << op << "(";
			expr->print();
		std::cout << ")";
	}
};

struct PrimaryExpr : public ExprNode {
	virtual ~PrimaryExpr() {}
};

struct IdentNode : public PrimaryExpr {
	std::string ident;

	IdentNode(std::string _i) : ident(_i) {}

	virtual ~IdentNode() {}

	void print() {
		std::cout << ident << " ";
	}
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

	void print() {
		std::cout << "(";
		switch (type) {
		case eLiteralType::STRINGVAL:
			std::cout << str_val;
			break;
		case eLiteralType::FLOATVAL:
			std::cout << flt_val;
			break;
		case eLiteralType::INTVAL:
			std::cout << int_val;
			break;
		case eLiteralType::BOOLVAL:
			std::cout << bool_val;
			break;
		case eLiteralType::VECTORVAL:
		default:
			break;
		}

		std::cout << ")";
	}
};

struct AttributeNode : public PrimaryExpr {
	Node* lhs;
	Node* ident;

	AttributeNode(Node* _l, Node* _i)
		: lhs(_l), ident(_i) {}

	virtual ~AttributeNode() {}

	void print() {
		std::cout << "(";
			lhs->print();
		std::cout << ".";
			ident->print();
		std::cout << ")";
	}
};

struct SubscriptNode : public PrimaryExpr {
	Node* base;
	Node* subscript;

	SubscriptNode(Node* _b, Node* _sub) : base(_b), subscript(_sub) {}
	virtual ~SubscriptNode() {}

	void print() {
		std::cout << "(";
			base->print();
		std::cout << "[";
			subscript->print();
		std::cout << "])";
	}
};

struct FunctionCall : public PrimaryExpr {
	bool is_trigger;
	Node* name;
	Node* arguments;

	FunctionCall(Node* _name, Node* _args) : is_trigger(false), name(_name), arguments(_args) {}
	virtual ~FunctionCall() {}

	void print() {
		if (is_trigger) {
			std::cout << "trigger ";
		}
		name->print();
		std::cout << "(";
			arguments->print();
		std::cout << ")";
	}
};

struct CodeBlock : public StmtNode {
	Node* children;

	CodeBlock() {}
	CodeBlock(Node* _c) : children(_c) {}
	virtual ~CodeBlock() {}

	void print() {
		std::cout << "{" << std::endl;
		if (children) {
			children->print();
		}
		std::cout << "}" << std::endl;
	}
};

struct Decl : StmtNode {
	Node* return_type; // the data about the return. eg, if it's void/int/uint
	eDeclType decl_type; // whether it's a function/var/class
	std::string name; // name of the var/function/class

	Decl(Node* _return_type, eDeclType _t, std::string _name)
		: return_type(_return_type), decl_type(_t), name(_name) {}
	virtual ~Decl() {}

	void print() {
		return_type->print();
		std::cout << " " << name;
	}
};

struct declarations_t : public NodeList<Decl> {};

struct VarDecl : public Decl {
	Node* default_value;
	VarDecl(Node* _return_type, std::string _name, Node* _default_value)
		: Decl(_return_type, eDeclType::VAR, _name), default_value(_default_value) {}

	virtual ~VarDecl() {}

	void print() {
		Decl::print();
		if (default_value) {
			std::cout << " = ";
			default_value->print();
		}
	}
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

	virtual ~FunctionDecl() {}

	void print() {
		Decl::print();
		std::cout << "(";
			arguments->print();
		std::cout << ")";
		block->print();
	}
};

struct ClassDecl : public Decl {
	std::string parent;
	Node* declarations;

	ClassDecl(Node* _return_type, std::string _name, std::string _parent, Node* _decls)
		: Decl(_return_type, eDeclType::CLASS, _name), parent(_parent), declarations(_decls) {}

	virtual ~ClassDecl() {}

	void print() {
		std::cout << "class ";
		Decl::print();
		if (parent.size()) {
			std::cout << " : " << parent;
		}
		std::cout << "{" << std::endl;
			declarations->print();
		std::cout << "}" << std::endl;
	}
};

struct IfStmt :  public StmtNode {
	Node* condition;
	Node* true_block;
	Node* false_block;

	IfStmt(Node* _cond, Node* _true) : condition(_cond), true_block(_true), false_block(NULL) {}
	IfStmt(Node* _cond, Node* _true, Node* _false) : condition(_cond), true_block(_true), false_block(_false) {}
	virtual ~IfStmt() {}

	void passDown(Node* block) {
		if (false_block == NULL) {
			false_block = block;
		}
		else {
			false_block->value.if_stmt->passDown(block);
		}
	}

	void print() {
		std::cout << "if (";
			condition->print();
		std::cout << ")";
			true_block->print();
		std::cout << " else ";
			false_block->print();

	}
};

struct WhileStmt :  public StmtNode {
	Node* condition;
	Node* block;

	WhileStmt(Node* _cond, Node* _block) : condition(_cond), block(_block) {}
	virtual ~WhileStmt() {}

	void print() {
		std::cout << "while (";
			condition->print();
		std::cout << ")";
			block->print();
	}
};

struct ForStmt :  public StmtNode {
	Node* begin;
	Node* condition;
	Node* counter;
	Node* block;

	ForStmt(Node* _begin, Node* _cond, Node* _counter, Node* _block)
		: begin(_begin), condition(_cond), counter(_counter), block(_block) {}

	virtual ~ForStmt() {}

	void print() {
		std::cout << "for (";
			begin->print();
		std::cout << ";";
			condition->print();
		std::cout << ";";
			counter->print();
		std::cout << ")";
			block->print();
	}
};

struct ExprStmt :  public StmtNode {
	Node* expr;

	ExprStmt(Node* _expr) : expr(_expr) {}

	virtual ~ExprStmt() {}

	void print() {
		expr->print();
	}
};

struct ReturnStmt :  public StmtNode {
	Node* return_val;

	ReturnStmt() : return_val(NULL) {}
	ReturnStmt(Node* rv) : return_val(rv) {}
	virtual ~ReturnStmt() {}

	void print() {
		std::cout << "return (";
			return_val->print();
		std::cout << ")";
	}
};

struct BreakStmt : public StmtNode {
	virtual ~BreakStmt() {}

	void print() { std::cout << "break"; }
};
struct ContinueStmt : public StmtNode {
	virtual ~ContinueStmt() {}

	void print() { std::cout << "continue"; }
};

struct Program {
	node_list_t declarations;

	void print() {
		std::cout << declarations.size() << " declarations" << std::endl;
		for (Node* node : declarations) {
			node->print();
		}
	}
};

} //namespace ast
NDESCRIPT_NS_END


