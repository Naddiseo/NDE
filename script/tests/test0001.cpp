#include <string>
#include <cppunit/extensions/HelperMacros.h>

#include "Driver.hpp"
#include "ASTree.hpp"
#include "SemTree.hpp"

class ParserTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ParserTest);
	CPPUNIT_TEST(testValid1);
	CPPUNIT_TEST_SUITE_END();
public:

	void testValid1() {
		using namespace nde;
		script::ast::Program prog;
		script::sem::Program sem_prog;
		script::Driver driver(prog);

		std::string source =
		"int a = 0;";

		CPPUNIT_ASSERT(driver.parseString(source, "Test1"));

	}
};


CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);
