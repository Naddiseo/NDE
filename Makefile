CXXFLAGS=-g -I./includes -std=c++0x -Weffc++ -Wall -Werror -Wfatal-errors -fPIC

SOURCES=src/rendering/Renderer.cpp \
		src/game/Game.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: library test01

test01: tests/test01.o
	$(CXX)  $^ -L ./ -lNDE $(CXXFLAGS)   -o test01.bin

library: libNDE.so

libNDE.so: $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) -shared -o $@

.cpp.o:
	$(CXX) -c $<  $(CXXFLAGS) -o $@
	
clean:
	-rm `find . -name "*.o" -print` *.so