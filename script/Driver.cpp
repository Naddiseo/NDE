#include <fstream>
#include <sstream>

#include "Driver.hpp"
#include "ScannerImpl.hpp"

namespace nde {
namespace script {

Driver::Driver(class ast::Program& _program)
	: trace_parsing(false), trace_scanning(false), program(_program)
{}

Driver::~Driver() {}

bool
Driver::parseStream(std::istream& in, const std::string& sname) {
	streamname = sname;

	Scanner scanner(&in);
#ifdef YYDEBUG
	scanner.set_debug(trace_scanning);
#endif
	this->lexer = &scanner;

	Parser parser(*this);
#ifdef YYDEBUG
	parser.set_debug_level(trace_parsing);
#endif
	return parser.parse() == 0;
}

bool
Driver::parseString(const std::string& input, const std::string& sname) {
	std::istringstream iss(input);
	return parseStream(iss, sname);
}

bool
Driver::parseFile(const std::string& filename) {
	std::ifstream in(filename.c_str());
	if (!in.good()) {
		return false;
	}

	return parseStream(in, filename);
}

void
Driver::error(const class location& l, const std::string& m) {
	std::cerr << l << ": " << m << std::endl;
}

void
Driver::error(const std::string& m) {
	std::cerr << m << std::endl;
}



} // namespace script
} // namespace nde
