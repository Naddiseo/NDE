#include "SemTree.hpp"
#include <iostream>
#include "ASTree.hpp"

NDESCRIPT_NS_BEGIN
namespace sem {

#define ASSERT(__expr, msg) { if (!(__expr)) { sem_error(msg); } };
#define DIE_IF(__expr, msg) { if (!(__expr)) { throw CompileError(msg); } }
#define DIE_UNLESS(__expr, msg) DIE_IF(!(__expr), msg)
#define LOG(msg) std::cerr << __FILE__ << ":" << __LINE__ << " " << msg << std::endl;
#define warn(msg) std::cerr << "Warn: " << msg << std::endl;
#define PASS_NODE(to) { to->ast = _node; to->loc = _node->loc; };

std::string
to_string(const location& loc) {
	std::stringstream ss;
	ss << loc;
	return ss.str();
}

SymbolEntry::SymbolEntry() : symtype(), level(0) {}

SymbolEntry::SymbolEntry(pClassDecl k)
	: symtype(CLASS), klass(k), level(0) {}

SymbolEntry::SymbolEntry(pVarDecl v)
	: symtype(VARIABLE), var(v), level(0) {}

SymbolEntry::SymbolEntry(pFunctionDecl f)
	: symtype(FUNCTION), func(f), level(0) {}

SymbolEntry::SymbolEntry(pClassDecl k, size_t _level)
	: symtype(CLASS), klass(k), level(_level) {}

SymbolEntry::SymbolEntry(pVarDecl v, size_t _level)
	: symtype(VARIABLE), var(v), level(_level) {}

SymbolEntry::SymbolEntry(pFunctionDecl f, size_t _level)
	: symtype(FUNCTION), func(f), level(_level) {}


location&
SymbolEntry::get_location() {
	switch (symtype) {
	case CLASS:
		return klass->loc;
	case VARIABLE:
		return var->loc;
	case FUNCTION:
		return func->loc;
	}
	throw std::runtime_error("Unknown symbol type");
}

SymbolEntry::~SymbolEntry() {}

//std::map<std::string, pSymbolEntry> sym_map;

SymbolTable::~SymbolTable() {}

void SymbolTable::pushScope() {
	level++;
}
void SymbolTable::popScope() {

	for (std::pair<std::string, pSymbolEntry> entry : sym_map) {
		pSymbolEntry current = entry.second;
		if (current->level == level) {
			if (current->next) {
				current->next->prev.reset();
				sym_map[entry.first] = current->next;
			}
			else {
				if (sym_map.find(entry.first) != sym_map.end()) {
					warn("Erasing " << entry.first);
				//TODO: sym_map.erase(entry.first);
				}
			}
		}
	}

	level--;
}

void SymbolTable::pushSymbol(std::string sym, pSymbolEntry& e) {
	e->level = level;
	if (sym_map.find(sym) != sym_map.end()) {
		pSymbolEntry current = sym_map[sym];
		if (current->level == level) {
			std::stringstream ss;
			ss
				<< e->get_location()
				<< ", symbol '"
				<< sym
				<< "' redefined. First defined "
				<< current->get_location();

			throw SymbolRedefinedError(ss.str());
		}
		e->next = current;
		current->prev = e;
	}

	sym_map[sym] = e;
}

void
SymbolTable::pushSymbol(std::string sym, pClassDecl& k) {
	pSymbolEntry e(new SymbolEntry(k, level));

	pushSymbol(sym, e);
}

void
SymbolTable::pushSymbol(std::string sym, pVarDecl& v) {
	pSymbolEntry e(new SymbolEntry(v, level));

	pushSymbol(sym, e);
}

void
SymbolTable::pushSymbol(std::string sym, pFunctionDecl& f) {
	pSymbolEntry e(new SymbolEntry(f, level));
	pushSymbol(sym, e);
}

bool
VarType::operator==(const ast::eReturnType& other) const {
	if ((ast->type == ast::eReturnType::OBJECT) && (other == ast->type)) {
		// test name/symbol?
	}
	else if ((ast->type == ast::eReturnType::LAST) || (other == ast::eReturnType::LAST)) {
		throw CompileError(to_string(ast->loc) + ", Return type == LAST");
	}

	return ast->type == other;
}



Program::~Program() {}

/*
void
Program::walk(ast::Node* _node) {
	switch (_node->type) {
#define SWITCH_WALK(klass, var_name, enum_name) case ast::eNodeType::enum_name: { walk(_node->var_name); } break;
	NODETYPE(SWITCH_WALK)
	default: break;
	}
}
*/

void Program::walk(ast::Node* _node, pExprNode expr) {
	//expr = pExprNode(new ExprNode());
	switch(_node->type) {
#define WALK(klass, var, enum_val) \
	case ast::eNodeType::enum_val: { \
		expr = p##klass(new klass()); \
		walk((ast::klass*)_node->var, expr); \
	}; break;

	EXPRTYPE(WALK)
#undef WALK

	default:
		throw CompileError(to_string(_node->loc) + ", Unknown expression type");
		break;
	}
}

void Program::walk(ast::Node* _node, pStmtNode stmt) {
	switch (_node->type) {
#	define WALK(klass, var, enum_val) \
		case ast::eNodeType::enum_val: { \
			stmt = p##klass(new klass()); \
			walk((ast::klass*)_node->var, stmt); \
		}; break;

	STMTTYPE(WALK)

#	undef WALK
	default:
		throw CompileError(to_string(_node->loc) + ", Unknown statement type");
		break;
	}
}

void
Program::walk(ast::Program* prog) {
	if (prog->declarations == NULL) {
		return;
	}

	ast = prog;

	for (ast::Node* decl : *prog->declarations->declarations) {
		switch (decl->type) {
		case ast::eNodeType::VARDECL: {
			pVarDecl var(new VarDecl());
			walk(decl->var_decl, var);

			global_vars.push_back(var);
		};
			break;
		case ast::eNodeType::FUNCTIONDECL: {
			pFunctionDecl f(new FunctionDecl());
			walk(decl->function_decl, f);

			global_functions.push_back(f);
		};
			break;
		case ast::eNodeType::CLASSDECL: {
			pClassDecl k(new ClassDecl());
			walk(decl->class_decl, k);

			classes.push_back(k);
		};
			break;
		default:
			std::cerr << "Unknown type " << decl->type << std::endl;
			break;
		}
	}

	ASSERT(in_breakable == 0, "Unmatched breaking?");
}

void Program::walk(ast::VarType* _node, pVarType var) {
	PASS_NODE(var);
}

void Program::walk(ast::ExprNode* _node, pExprNode expr) {
}

void Program::walk(ast::StmtNode* _node, pStmtNode stmt) {}

void Program::walk(ast::expr_list_t* _node, expr_list& elist) {}

void Program::walk(ast::stmt_list_t* _node, stmt_list& slist) {
#define PUSH_CAST(v) slist.push_back(std::dynamic_pointer_cast<StmtNode>(v));
	for (ast::Node* stmt : *_node) {
		switch (stmt->type) {
		case ast::eNodeType::IFSTMT: {
			pIfStmt ifstmt(new IfStmt());
			walk(stmt->if_stmt, ifstmt);
			PUSH_CAST(ifstmt);
		};
			break;
		case ast::eNodeType::WHILESTMT: {
			pWhileStmt whilestmt(new WhileStmt());
			walk(stmt->while_stmt, whilestmt);
			PUSH_CAST(whilestmt);
		};
			break;
		case ast::eNodeType::FORSTMT: {
			pForStmt forstmt(new ForStmt());
			walk(stmt->for_stmt, forstmt);
			PUSH_CAST(forstmt);
		};
			break;
		case ast::eNodeType::EXPRSTMT: {
			pExprStmt exprstmt(new ExprStmt());
			walk(stmt->expr_stmt, exprstmt);
			PUSH_CAST(exprstmt);
		};
			break;
		case ast::eNodeType::RETURNSTMT: {
			pReturnStmt returnstmt(new ReturnStmt());
			walk(stmt->return_stmt, returnstmt);
			PUSH_CAST(returnstmt);
		};
			break;
		case ast::eNodeType::CONTINUESTMT: {
			pContinueStmt contstmt(new ContinueStmt());
			walk(stmt->continue_stmt, contstmt);
			PUSH_CAST(contstmt);
		};
			break;
		case ast::eNodeType::BREAKSTMT: {
			pBreakStmt breakstmt(new BreakStmt());
			walk(stmt->break_stmt, breakstmt);
			PUSH_CAST(breakstmt);
		};
			break;
		case ast::eNodeType::VARDECL: {
			pVarDecl varstmt(new VarDecl());
			walk(stmt->var_decl, varstmt);
			PUSH_CAST(varstmt);
		};
			break;
		case ast::eNodeType::STMTNODE:
		default:
			throw CompileError((std::string)"Unknown Statement type " + ast::eNodeType_str[(size_t)stmt->type]);
		}
	}
}

void Program::walk(ast::EmptyExpression* _node, pExprNode expr) { throw CompileError("Shouldn't get here"); }

void Program::walk(ast::BinaryExpr* _node, pBinaryExpr expr) {
	PASS_NODE(expr);

	expr->op = _node->op;

	expr->lhs = pExprNode(new ExprNode);
	expr->rhs = pExprNode(new ExprNode);

	walk(_node->lhs, expr->lhs);
}

void Program::walk(ast::TernaryExpr* _node, pExprNode expr) {}

void Program::walk(ast::UnaryExpr* _node, pExprNode expr) {}

void Program::walk(ast::PrimaryExpr* _node, pExprNode expr) {}


void Program::walk(ast::IdentNode* _node, pExprNode expr) {}

void Program::walk(ast::LiteralExpr* _node, pExprNode expr) {}

void Program::walk(ast::AttributeNode* _node, pExprNode expr) {}

void Program::walk(ast::SubscriptNode* _node, pExprNode expr) {}


void Program::walk(ast::FunctionCall* _node, pExprNode expr) {
	PASS_NODE(expr);

	pFunctionCall func(new FunctionCall());

	walk(_node->name, func->name);
	// grab args
	walk(_node->arguments->expr_list, func->arguments);

	expr = func;

}

void Program::walk(ast::CodeBlock* _node, pCodeBlock block) {
	PASS_NODE(block);

	symtab.pushScope();
	walk(_node->children->stmt_list, block->stmts);
	symtab.popScope();
}

void Program::walk(ast::Decl* _node) { throw CompileError("Should not get here"); }

void Program::walk(ast::VarDecl* _node, pVarDecl var) {
	ASSERT(_node->get_return_type() != ast::eReturnType::VOID, "Variables cannot be declared void");

	var->name = _node->name;
	var->is_array = _node->is_array();
	var->return_type = _node->get_return_type();
	PASS_NODE(var);

	symtab.pushSymbol(var->name, var);
}

void Program::walk(ast::declarations_t* _node) { throw CompileError("Should not get here"); }

void Program::walk(ast::vardecls_t* _node, var_decls& decls) {

	for (ast::Node* decl : *_node) {
		pVarDecl var(new VarDecl());
		walk(decl->var_decl, var);
		decls.push_back(var);
	}
}

void Program::walk(ast::FunctionDecl* _node, pFunctionDecl func) {
	func->name = _node->name;
	PASS_NODE(func);

	current_fn = func;

	walk(_node->return_type->var_type, func->return_type);

	symtab.pushSymbol(func->name, func);
	symtab.pushScope();

	// grab args
	walk(_node->arguments->var_decls, func->arguments);
	// do code block
	walk(_node->block->code_block, func->body);

	symtab.popScope();

	current_fn.reset();
}

void Program::walk(ast::ClassDecl* _node, pClassDecl klass) {
	PASS_NODE(klass);
	klass->name = _node->name;

	symtab.pushSymbol(klass->name, klass);

	symtab.pushScope();
	for (ast::Node* decl : *_node->declarations->declarations) {
		switch (decl->type) {
		case ast::eNodeType::VARDECL: {
			pVarDecl var(new VarDecl());
			walk(decl->var_decl, var);

			klass->vars.push_back(var);
		};
			break;
		case ast::eNodeType::FUNCTIONDECL: {
			pFunctionDecl func(new FunctionDecl());
			walk(decl->function_decl, func);

			klass->funcs.push_back(func);
		};
			break;
		case ast::eNodeType::CLASSDECL: {
			throw CompileError("Classes cannot contain other classes");
		};
			break;
		default:
			std::cerr << "Unknown type " << decl->type << std::endl;
			break;
		}
	}
	symtab.popScope();

}

void Program::walk(ast::IfStmt* _node, pIfStmt stmt) {
	PASS_NODE(stmt);

	walk(_node->condition, stmt->condition);

	stmt->true_block = pCodeBlock(new CodeBlock());
	walk(_node->true_block->code_block, stmt->true_block);

	walk(_node->false_block, stmt->false_block);
}

void Program::walk(ast::WhileStmt* _node, pWhileStmt stmt) {
	PASS_NODE(stmt);

	walk(_node->condition, stmt->condition);

	in_breakable++;
	stmt->body = pCodeBlock(new CodeBlock());
	walk(_node->block->code_block, stmt->body);
	in_breakable--;
}

void Program::walk(ast::ForStmt* _node, pForStmt stmt) {
	PASS_NODE(stmt);

	stmt->begin = pExprStmt(new ExprStmt());
	stmt->condition = pExprStmt(new ExprStmt());
	stmt->counter = pExprStmt(new ExprStmt());

	symtab.pushScope(); // make sure any vars declared in for(var;;) don't escape

	walk(_node->begin, stmt->begin->expr);
	walk(_node->condition, stmt->condition->expr);
	walk(_node->counter, stmt->counter->expr);


	in_breakable++;
	stmt->body = pCodeBlock(new CodeBlock());
	walk(_node->block->code_block, stmt->body);
	in_breakable--;
	symtab.popScope();
}

void Program::walk(ast::ExprStmt* _node, pExprStmt stmt) {
	stmt->expr = pExprNode(new ExprNode());
	walk(_node->expr, stmt->expr);
}

void Program::walk(ast::ReturnStmt* _node, pReturnStmt stmt) {
	if (!current_fn) {
		throw CompileError(to_string(_node->loc) + ", cannot return from here.");
	}
	else {

		ast::eReturnType expr_return = get_expr_type(_node->return_val);

		LOG("Returning from " << current_fn->name << ", which returns " << ast::eReturnType_str[static_cast<int>(current_fn->return_type)]);
		if (*current_fn->return_type == ast::eReturnType::VOID and expr_return != ast::eReturnType::VOID) {
			throw CompileError(to_string(_node->loc) + ", cannot return non-void from void function");
		}

		if (*current_fn->return_type != expr_return) {
			throw CompileError(to_string(_node->loc) + ", mismatching return type");
		}
		else if (expr_return == ast::eReturnType::OBJECT) {
			// must be the same kind of object
		}


	}

}

void Program::walk(ast::ContinueStmt* _node, pContinueStmt stmt) {
	if (in_breakable <= 0) {
		std::cout << "in_breakable " << in_breakable;
		throw CompileError(to_string(_node->loc) + ", cannot continue from here");
	}
}
void Program::walk(ast::BreakStmt* _node, pBreakStmt stmt) {
	if (in_breakable <= 0) {
		throw CompileError(to_string(_node->loc) + ", cannot break from here");
	}
}

void
Program::sem_error(std::string msg) {
	std::cerr << "Semantic Error: " << msg << std::endl;
}

ast::eReturnType
Program::get_expr_type(ast::Node* _node) {
	ast::Node* expr = _node;
	ASSERT(_node, "Got null");
	if (_node->is_stmt() and !_node->is_expr_stmt()) {
		throw CompileError(to_string(_node->loc) + "Cannot determine return type of a statement");
	}

	if (_node->is_expr_stmt()) {
		expr = _node->expr_stmt->expr;

		if (expr == NULL) { // no return
			return ast::eReturnType::VOID;
		}
	}

	if (_node->is_expr_node() or _node->is_empty_expression()) {
		return ast::eReturnType::LAST; // should this be an error?
	}

	if (expr->is_literal_expr()) {
		ast::LiteralExpr* lit = expr->literal_expr;
		switch (lit->type) {
		case ast::eLiteralType::BOOLVAL:
		case ast::eLiteralType::FALSE:
		case ast::eLiteralType::TRUE:
			return ast::eReturnType::BOOL;
		case ast::eLiteralType::FLOATVAL:
			return ast::eReturnType::FLOAT;
		case ast::eLiteralType::INTVAL:
			return ast::eReturnType::UINT;
		case ast::eLiteralType::UINTVAL:
			return ast::eReturnType::INT;
		case ast::eLiteralType::STRINGVAL:
			return ast::eReturnType::STRING;
		case ast::eLiteralType::VECTORVAL:
			return ast::eReturnType::VECTOR;
		default:
			throw CompileError(to_string(lit->loc) + ", Unknown type");
		}
	}



	throw CompileError(to_string(_node->loc) + ", Could not determine return type");
	return ast::eReturnType::LAST;
}

} // namespace sem
NDESCRIPT_NS_END
