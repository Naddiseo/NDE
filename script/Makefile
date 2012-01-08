YYDEBUG=0
CXXFLAGS=-I. -g3 -std=c++0x -DYYDEBUG=$(YYDEBUG) -Werror -Wfatal-errors -pipe -fomit-frame-pointer -D_FORTIFY_SOURCE=2 -fstack-protector-all

SCANNERBASE=scanner
PARSERBASE=parser

all: clear  lexer parser
	$(CXX) $(CXXFLAGS) -o ndes.bin Parser.cpp Scanner.cpp Driver.cpp

lexer: $(SCANNERBASE).ll
	flex -o Scanner.cpp --header-file=Scanner.hpp -Ce $(SCANNERBASE).ll
	
parser: $(PARSERBASE).yy
	bison -o Parser.cpp --defines=Parser.hpp -dv $(PARSERBASE).yy
	
$(SCANNERBASE).ll:
$(PARSERBASE).yy:

clean:
	- rm -v Scanner.[ch]pp Parser.output Parser.[ch]pp *.hh *.bin

clear:
	clear

run:
	./lcalc

.PHONY: $(SCANNERBASE).ll $(PARSERBASE).ypp