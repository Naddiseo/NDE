#include "script/ASTree.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

Decl::~Decl() {}

Node::~Node() {
	switch (type) {
#define NODEFN(klass, var_name, enum_name) case eNodeType::enum_name: { delete value.var_name; }; break;
	NODETYPE;
	}

}


} // namespace ast
NDESCRIPT_NS_END
