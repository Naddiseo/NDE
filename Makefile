CXXFLAGS=-g -I./includes -std=c++0x -Wall -Werror -Wfatal-errors -fPIC
CFLAGS=-g -I./includes 

SOURCES=src/graphics/Renderer.cpp \
		src/game/AssetLoader.cpp \
		src/game/Assets.cpp \
		src/game/Game.cpp \
		src/game/Scene.cpp \
		src/game/World.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: library test01

test01: tests/test01.o
	$(CXX)  $^ -L ./ -lNDE `pkg-config sdl glu gl assimp --cflags --libs`  $(CXXFLAGS)   -o test01.bin

testc: test.o
	$(CC)  $^ -L ./ `pkg-config sdl glu gl assimp --libs` -lglut  $(CFLAGS)   -o test.bin


library: libNDE.so

libNDE.so: $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) -shared -o $@

.cpp.o:
	$(CXX) -c $<  $(CXXFLAGS) -o $@

.c.o: 
	$(CC) -c $< $(CFLAGS) `pkg-config sdl glu gl assimp --cflags` -o $@

clean:
	-rm `find . -name "*.o" -print` *.so

run:
	./test01.bin 