#include <string>
#include <vector>
#include <cppunit/extensions/HelperMacros.h>
#include "script/Lexer.hpp"
#include "tests/scripttests/progs.hpp"

using nde::TokenType;


#if 0
#	define PRINT_ACTUAL for(nde::Token t : actual) { std::cout << (std::string)t << std::endl; }
#else
#	define PRINT_ACTUAL
#endif

#define ASSERT_TOKEN_LIST(prog) do { \
	nde::Lexer lex; \
	CPPUNIT_ASSERT(lex.lex(prog)); \
	nde::tokens_t& expected = prog ## _expected; \
	const nde::tokens_t& actual = lex.getTokens(); \
	PRINT_ACTUAL \
	/*CPPUNIT_ASSERT_EQUAL_MESSAGE("Lexer should give the same number of tokens", expected.size(), actual.size());*/ \
	for (size_t i = 0; i < expected.size(); i++) { \
		nde::Token a, b; \
		CPPUNIT_ASSERT_NO_THROW(a = expected[i]); \
		CPPUNIT_ASSERT_NO_THROW(b = actual[i]); \
		CPPUNIT_ASSERT_MESSAGE( \
				((std::string)a) + std::string(" == ") + (std::string)b, a.isExact(b) \
		); \
		/*std::cout << "Matched" << ((std::string)a) << std::endl;*/ \
	} \
	} while (0)

class LexerTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(LexerTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testLex);
	CPPUNIT_TEST(testLexTokens1);
	CPPUNIT_TEST(testLexTokens2);
	CPPUNIT_TEST(testLexTokens3);
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
		ASSERT_TOKEN_LIST(prog1);
	}
	void testLexTokens2() {
		ASSERT_TOKEN_LIST(prog2);
	}
	void testLexTokens3() {
		ASSERT_TOKEN_LIST(prog3);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(LexerTest);



