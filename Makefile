INCFLAGS=-I./includes -I.
LINKFLAGS=`pkg-config sdl gl glu SDL_image ILU --cflags --libs`
CXXFLAGS=-g $(INCFLAGS) $(LINKFLAGS) -DNDEBUG=1  -Weffc++ -std=c++0x -Wall -Werror -Wfatal-errors 
CFLAGS=-g -I./includes 

GAME_FILES=Camera.cpp Game.cpp Scene.cpp Settings.cpp World.cpp
GAME_SOURCES=$(addprefix src/game/, $(GAME_FILES))

GRAPHICS_FILES=Color.cpp Face.cpp IsRendered.cpp Renderer.cpp SkyBox.cpp
GRAPHICS_SOURCES=$(addprefix src/graphics/, $(GRAPHICS_FILES))

RESOURCES_FILES=Assets.cpp Terrain.cpp
RESOURCES_SOURCES=$(addprefix src/resources/, $(RESOURCES_FILES))

SOURCES=$(GAME_SOURCES) $(GRAPHICS_SOURCES) $(RESOURCES_SOURCES)

OBJECTS=$(SOURCES:.cpp=.o)

all: library test01

test01: tests/test01.o
	$(CXX)  $^ -L ./ -lNDE $(LINKFLAGS)  $(CXXFLAGS)   -o test01.bin

library: libNDE.a

libNDE.a: $(OBJECTS) 
	$(AR) rs $@ $^ 

.cpp.o:
	$(CXX) -c $<  $(CXXFLAGS) -o $@

.c.o: 
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

clean:
	-rm `find . \( -name "*.o" -o -name "*.bin" -o -name "*.so" -o -name "*.a" -o -name "*.yy.c" -o -name "*.tab.[ch]" -o -name "*.o" -o -name "*.output" \)  -print`

run:
	./test01.bin 