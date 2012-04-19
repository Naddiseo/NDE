/*
 * main.cpp
 *
 *  Created on: 2012-01-10
 *      Author: richard
 */
#include <iostream>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Driver.hpp"
#include "ASTree.hpp"
#include "SemTree.hpp"
#include "ASTPrinter.hpp"

int
main(int argc, char* argv[]) {
	using namespace nde;
	bool run_tests = false;
	char* filename = NULL;

	if (argc > 1) {
		script::ast::Program prog;
		script::sem::Program sem_prog;
		script::Driver driver(prog);

		for (int i = 1; i < argc; i++) {
			if (argv[i][0] == '-') {
				switch (argv[i][1]) {
				case 'p':
					driver.trace_parsing = true;
					break;
				case 'l':
					driver.trace_scanning = true;
					break;
				case 't':
					run_tests = true;
					break;
				default:
					break;
				}
			}
			else {
				filename = argv[i];
			}
		}
		try {
			if (run_tests) {
				CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

				CppUnit::TextUi::TestRunner runner;
				runner.addTest(suite);
				runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));

				return runner.run() ? 0 : 1;
			}
			else if (filename != NULL) {
				std::cout << "Parsing " << filename << std::endl;
				if (driver.parseFile(filename)) {
					std::cout << "Success" << std::endl;
					nde::script::ast::Printer printer;
					printer.Visitor::walk(prog.declarations);
					//printer.walk(prog.declarations);

					sem_prog.walk(&prog);
				}
				else {
					std::cerr << "Fail" << std::endl;
				}
			}
		} catch (std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;

		}
	}


	return 0;
}
