MINGWDIR=C:/MinGW
CXX=$(MINGWDIR)/bin/g++
INCFLAGS=-I$(MINGWDIR)/include -I.
LINKFLAGS=-lopengl32 -lSDL -lglu32 -lSDL_image -static-libgcc -static-libstdc++
CXXFLAGS=-g $(INCFLAGS) $(LINKFLAGS) -DWINDOWS -DNDEBUG=1 -Weffc++ -std=c++0x -Wall
FLEXFLAGS=-o resource.yy.c
BISONFLAGS=-dvt

SOURCES=main.cpp ResourceReader.cpp Color.cpp Terrain.cpp Camera.cpp Face.cpp misc.cpp SkyBox.cpp
CSOURCES=resource.yy.c resource.tab.c

BINARY_OBJ=$(SOURCES:.cpp=.o) $(CSOURCES:.c=.o)

all: lexer parser test.exe

test.exe: $(BINARY_OBJ)
	$(CXX) $^ $(CXXFLAGS) -o $@
	-rm *.o

run:
	./test

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

clean:
	-rm -v *.yy.c *.tab.[ch] *.o *.output