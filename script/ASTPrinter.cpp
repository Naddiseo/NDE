#include "ASTPrinter.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

static const char* binop_map[] = {
	"error",
	"=", "|=", "&=", "^=", "<<=", ">>=", "+=", "-=", "*=", "/=", "%=",
	">", "<", "<=", ">=", "<<", ">>",
	"+", "-", "*", "/", "%", "||", "&&", "|", "&", "^", "==", "!="
};

static const char* uop_map[] = {
	"~", "!", "++", "--", "-"
};

Printer::Printer() : tabs(0) {}

Printer::~Printer() {}
void
Printer::tab() {
	for (size_t i = 0; i < tabs; i++) {
		std::cout << "\t";
	}
}

//#define walk(klass, var_name, enum_name) void Printer::walk(klass* _node) { }
//NODETYPE(PRINT)
void Printer::walk(VarType* _node) {
	if (_node->type == eReturnType::OBJECT) {
		std::cout << _node->class_name;
	}
	else {
		std::cout << _node->type;
	}
}

void Printer::walk(ExprNode* _node) { std::cerr << "Printing EXPRNODE"; }
void Printer::walk(StmtNode* _node) { std::cerr << "Printing STMTNODE"; }

void Printer::walk(expr_list_t* _node) {
	printlist(_node);
}
void Printer::walk(stmt_list_t* _node) {
	printlist(_node, ";\n", true, true);
}

void Printer::walk(EmptyExpression* _node) {}
void Printer::walk(BinaryExpr* _node) {
	std::cout << "(";
		walk(_node->lhs);
	std::cout << ")" << binop_map[static_cast<char>(_node->op)] << "(";
		walk(_node->rhs);
	std::cout << ")";

}
void Printer::walk(TernaryExpr* _node) {
	std::cout << "(";
		walk(_node->condition);
	std::cout << " ? ";
		walk(_node->true_cond);
	std::cout << " : ";
		walk(_node->false_cond);
	std::cout << ")";
}

void Printer::walk(UnaryExpr* _node) {
	std::cout << uop_map[static_cast<char>(_node->op)] << "(";
		walk(_node->expr);
	std::cout << ")";
}

void Printer::walk(PrimaryExpr* _node) { std::cerr << "Empty primary expr"; }

void Printer::walk(IdentNode* _node) {
	std::cout <<"ident(" << _node->ident << ") ";
}

void Printer::walk(LiteralExpr* _node) {
	std::cout << "(";
	switch (_node->type) {
	case eLiteralType::STRINGVAL:
		std::cout << '"' << _node->str_val << '"';
		break;
	case eLiteralType::FLOATVAL:
		std::cout << _node->flt_val << "f";
		break;
	case eLiteralType::INTVAL:
		std::cout << _node->int_val << "i";
		break;
	case eLiteralType::BOOLVAL:
		std::cout << _node->bool_val << "b";
		break;
	case eLiteralType::VECTORVAL:
	default:
		break;
	}

	std::cout << ")";
}

void Printer::walk(AttributeNode* _node) {
	std::cout << "(";
		walk(_node->lhs);
	std::cout << ".";
	walk(_node->ident);
	std::cout << ")";
}

void Printer::walk(SubscriptNode* _node) {

	std::cout << "(";
	walk(_node->base);
	std::cout << "[";
	walk(_node->subscript);
	std::cout << "])";
}

void Printer::walk(FunctionCall* _node) {

	if (_node->is_trigger) {
		std::cout << "trigger ";
	}
	walk(_node->name);
	std::cout << "(";
	walk(_node->arguments);
	std::cout << ")";
}

void Printer::walk(CodeBlock* _node) {

	std::cout << " {" << std::endl;
	tabs++;
	if (_node->children) {
		walk(_node->children);
	}
	tabs--;
	tab();
	std::cout << "}" << std::endl;
}

void Printer::walk(Decl* _node) {

	walk(_node->return_type);
	std::cout << " " <<_node-> name;
	if (_node->return_type->var_type->is_array) {
		std::cout << "[]";
	}
}

void Printer::walk(VarDecl* _node) {

	walk((Decl*)_node);
	if (_node->default_value) {
		std::cout << " = ";
		walk(_node->default_value);
	}
}

void Printer::walk(declarations_t* _node) {
	printlist_callback_t callback = [](Node* _node, bool is_last, std::string sep, bool print_last) {
		if (_node->decl_node->decl_type == eDeclType::VAR) {
			std::cout << ";\n";
		}

	};
	printlist(_node, "\n", true, true, callback);
}

void Printer::walk(vardecls_t* _node) {
	printlist(_node, ", ");
}

void Printer::walk(FunctionDecl* _node) {
	if (_node->is_event) {
		std::cout << "event ";
	}
	walk((Decl*)_node);
	std::cout << "(";
	walk(_node->arguments);
	std::cout << ")";
	walk(_node->block);
}

void Printer::walk(ClassDecl* _node) {

	std::cout << "class ";
	//Decl::walk(); // return type is null
	std::cout << _node->name;
	if (_node->parent.size()) {
		std::cout << " : " << _node->parent;
	}
	std::cout << " {" << std::endl;
	tabs++;
	walk(_node->declarations);
	tabs--;
	tab();
	std::cout << std::endl << "}" << std::endl;
}

void Printer::walk(IfStmt* _node) {

	std::cout << "if (";
	walk(_node->condition);
	std::cout << ")";
	walk(_node->true_block);
	tab();
	std::cout << " else ";
	walk(_node->false_block);
}

void Printer::walk(WhileStmt* _node) {
	std::cout << "while (";
	walk(_node->condition);
	std::cout << ")";
	walk(_node->block);

}

void Printer::walk(ForStmt* _node) {
	std::cout << "for (";
	walk(_node->begin);
	std::cout << ";";
	walk(_node->condition);
	std::cout << ";";
	walk(_node->counter);
	std::cout << ")";
	walk(_node->block);
}

void Printer::walk(ExprStmt* _node) {
	if (_node->expr != NULL) { // ExprStmt's expression can be empty
		walk(_node->expr);
	}
}

void Printer::walk(ReturnStmt* _node) {

	std::cout << "return (";
	walk(_node->return_val);
	std::cout << ")";
}

void Printer::walk(ContinueStmt* _node) {
	std::cout << "continue";
}

void Printer::walk(BreakStmt* _node) {
	std::cout << "break";
}

} // namespace nde

NDESCRIPT_NS_END
