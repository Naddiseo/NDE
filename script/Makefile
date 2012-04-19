YYDEBUG=1
#CXX=/usr/bin/g++
CXXFLAGS= \
	-I. -I.. \
	-Wl,--no-as-needed -lcppunit \
	-g3 -std=c++0x \
	-DYYDEBUG=$(YYDEBUG) \
	-Wall -Werror -Wfatal-errors \
	-pipe -fomit-frame-pointer -D_FORTIFY_SOURCE=2 -fstack-protector-all

SCANNERBASE=scanner
PARSERBASE=parser

SOURCES=Parser.cpp Scanner.cpp Driver.cpp ASTree.cpp ASTPrinter.cpp ASTVisitor.cpp SemTree.cpp  main.cpp
TEST_SOURCES=tests/test0001.cpp
OBJECTS=$(SOURCES:.cpp=.o) $(TEST_SOURCES:.cpp=.o)
DEPFILES:=$(SOURCES:.cpp=.d)



all: clear $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o ndes.bin $(OBJECTS) 


Scanner.cpp: $(SCANNERBASE).ll
	flex -o Scanner.cpp --header-file=Scanner.hpp -Ce $(SCANNERBASE).ll
	

Parser.cpp: $(PARSERBASE).yy Scanner.hpp
	bison -o Parser.cpp --defines=Parser.hpp -dv $(PARSERBASE).yy
	
.cpp.o:
	@-#$(CXX) $< -MM -MF $(patsubst %.o,%.d, $@) $(CXXFLAGS) 
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
#$(SCANNERBASE).ll:
#$(PARSERBASE).yy:

Scanner.hpp: Scanner.cpp

Parser.hpp: Parser.cpp
#location.hh: Parser.cpp
#position.hh: Parser.cpp
#stack.hh: Parser.cpp

clean:
	- rm -v Scanner.[ch]pp Parser.output Parser.[ch]pp *.hh *.bin *.o *.d

clear:
	clear

run:
	./ndes.bin test.txt

test:
	./ndes.bin -t

.PHONY: $(SCANNERBASE).ll $(PARSERBASE).ypp


-include $(DEPFILES)