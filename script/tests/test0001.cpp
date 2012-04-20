#include <string>
#include <cppunit/extensions/HelperMacros.h>

#include "Driver.hpp"
#include "ASTree.hpp"
#include "SemTree.hpp"

static std::string valid_syntax_sources[] = {
	"int a;",
	"uint a;",
	"string a;",
	"bool a;",
	"float a;",

	"int a = 1;",
	"uint a = 1;",
	"string a = \"hello\";",
	"bool a = true;",
	"bool a = false;",
	"float a = 1.1;",

	"int a[];",
	"uint a[];",
	"string a[];",
	"bool a[];",
	"float a[];",

	"int a[] = 1;",
	"uint a[] = 1;",
	"string a[] = \"hello\";",
	"bool a[] = true;",
	"bool a[] = false;",
	"float a[] = 1.1;",

	"int a[] = b[4];",

	"void foo(){ a += 1; }",
	"void foo(){ a -= 1; }",
	"void foo(){ a *= 1; }",
	"void foo(){ a /= 1; }",
	"void foo(){ a %= 1; }",
	"void foo(){ a ^= 1; }",
	"void foo(){ a &= 1; }",
	"void foo(){ a |= 1; }",
	"void foo(){ a <<= 1; }",
	"void foo(){ a >>= 1; }",

	"int a = -1--1;",
	"int a = 1+0.4+1--1-1---1/4*(4%5^3);",

	"class B : A { int b;}",
	"void foo(){}",
	"int foo(){}",
	"uint foo(){}",
	"string foo(){}",
	"bool foo(){}",
	"float foo(){}",
};

class ParserTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ParserTest);
	CPPUNIT_TEST(testValidSyntax1);
	CPPUNIT_TEST_SUITE_END();
public:

	void testValidSyntax1() {
		using namespace nde;
		script::ast::Program prog;
		script::sem::Program sem_prog;
		script::Driver driver(prog);

		for (std::string& source : valid_syntax_sources) {

			CPPUNIT_ASSERT(driver.parseString(source, std::string("<syntax test>")));
		}
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);
