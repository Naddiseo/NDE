#include <cppunit/extensions/HelperMacros.h>
#include "script/Lexer.hpp"
#include "script/Parser.hpp"
#include "tests/scripttests/progs.hpp"


class ParserTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ParserTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testValid1);
	CPPUNIT_TEST(testInvalid1);
	CPPUNIT_TEST(testValid2);
	CPPUNIT_TEST_SUITE_END();
public:

	void testConstructor() {
		nde::Lexer lex;
		lex.lex(prog1);

		CPPUNIT_ASSERT_NO_THROW(nde::Parser(lex.getTokens()));
	}

	void testValid1() {
		nde::Lexer lex;
		lex.lex(prog2);

		nde::Parser p(lex.getTokens());

		CPPUNIT_ASSERT(p.parse());
		int decl_count = p.getAST().declarations.size();
		CPPUNIT_ASSERT_EQUAL(3, decl_count);
	}

	void testInvalid1() {
		nde::Lexer lex;
		lex.lex(prog3);

		nde::Parser p(lex.getTokens());

		CPPUNIT_ASSERT(!p.parse());
	}

	void testValid2() {
		nde::Lexer lex;
		lex.lex(prog4);

		nde::Parser p(lex.getTokens());

		CPPUNIT_ASSERT(p.parse());
		int decl_count = p.getAST().declarations.size();
		CPPUNIT_ASSERT_EQUAL(3, decl_count);
	}


};


CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);
