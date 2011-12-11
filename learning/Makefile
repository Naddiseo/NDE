CXXFLAGS=-g -I. -DNDEBUG=1  -Weffc++ -std=c++0x -Wall -Werror -Wfatal-errors `pkg-config sdl gl glu SDL_image --cflags --libs`
FLEXFLAGS=-o resource.yy.c
BISONFLAGS=-dvt

SOURCES=main.cpp ResourceReader.cpp Color.cpp Terrain.cpp Camera.cpp
CSOURCES=resource.yy.c resource.tab.c

BINARY_OBJ=$(SOURCES:.cpp=.o) $(CSOURCES:.c=.o)

all: clear lexer parser test.bin

run:
	clear
	./test.bin

test.bin: $(BINARY_OBJ)
	$(CXX) $^ $(CXXFLAGS) -o $@
	- rm *.o

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS) -o $@

.c.o:
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

	
lexer: resource.yy.c

parser: resource.tab.c

resource.yy.c: resource.l
	flex $(FLEXFLAGS) $<

resource.tab.c: resource.y
	bison $(BISONFLAGS) $<

tar:
	tar vjcf ogltest.tar.bz2 $(SOURCES) *.hpp brick.tga Makefile resource.l resource.y

clear:
	clear

clean:
	-rm -v *.yy.c *.tab.[ch] *.o *.output
