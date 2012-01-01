#include <string>
#include <vector>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include "script/Lexer.hpp"

using nde::TokenType;

static std::string prog1 =
	"void main() {\n"
	"}";
static nde::tokens_t prog1_expected = {
	{TokenType::VOID, 1, 1},
	{TokenType::IDENT, 1, 6, "main"},
	{TokenType::LPAREN, 1, 10},
	{TokenType::RPAREN, 1, 11},
	{TokenType::LBRACE, 1, 13},
	{TokenType::RBRACE, 2, 1},
};

class LexerTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(LexerTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testLex);
	CPPUNIT_TEST(testLexTokens1);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp() {}
	void tearDown() {}

	void testConstructor() { CPPUNIT_ASSERT_NO_THROW(nde::Lexer()); }
	void testLex() {
		nde::Lexer lex;
		bool ret;
		CPPUNIT_ASSERT_NO_THROW(ret = lex.lex(prog1));

		CPPUNIT_ASSERT(ret);
	}

	void testLexTokens1() {
		nde::Lexer lex;
		CPPUNIT_ASSERT(lex.lex(prog1));

		nde::tokens_t& expected = prog1_expected;
		const nde::tokens_t& actual = lex.getTokens();

		CPPUNIT_ASSERT_EQUAL_MESSAGE("Lexer should give the same number of tokens", expected.size(), actual.size());

		for (size_t i = 0; i < expected.size(); i++) {
			nde::Token a, b;
			CPPUNIT_ASSERT_NO_THROW(a = expected[i]);
			CPPUNIT_ASSERT_NO_THROW(b = actual[i]);
			CPPUNIT_ASSERT_MESSAGE(
					((std::string)a) + std::string(" == ") + (std::string)b, a.isExact(b)
			);
			//std::cout << "Matched" << ((std::string)a) << std::endl;
		}

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( LexerTest );


int main(int argc, char* argv[]) {
	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( suite );

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
													   std::cerr ) );
	// Run the tests.
	bool wasSucessful = runner.run();

	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;
}
