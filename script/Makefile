YYDEBUG=0
CXXFLAGS=-I. -g3 -std=c++0x -DYYDEBUG=$(YYDEBUG) -Wfatal-errors

all: parser lexer
	$(CXX) $(CXXFLAGS) -o ndes.bin parser.tab.c lex.yy.c

lexer: tokenizer.l
	flex tokenizer.l
	
parser: parser.y
	bison -dv parser.y
	
tokenizer.l:
parser.y:

clean:
	- rm -v lex.yy.c calc.tab.c calc.tab.h calc.output

run:
	./lcalc

test:
	LHS=`./lcalc <test.0 2>&1` && \
	RHS=`cat test.0.res`&& [ $(LHS) = "\$RHS" ] && echo "Passed" || echo "Failed"
	
package:
	mkdir -p reames_as1
	cp calc.y calc.l Makefile reames_as1
	tar -zcf reames_as1.tgz reames_as1
	
.PHONY: tokenizer.l parser.y