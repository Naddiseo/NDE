INCFLAGS=-I./includes -I.
LINKFLAGS=`pkg-config sdl gl glu SDL_image --cflags --libs`
CXXFLAGS=-g $(INCFLAGS) $(LINKFLAGS) -DNDEBUG=1  -Weffc++ -std=c++0x -Wall -Werror -Wfatal-errors 
FLEXFLAGS=-o resource.yy.c
BISONFLAGS=-dvt
CFLAGS=-g -I./includes 

GAME_FILES=Camera.cpp Game.cpp Scene.cpp Settings.cpp World.cpp
GAME_SOURCES=$(addprefix src/game/, $(GAME_FILES))

GRAPHICS_FILES=Color.cpp Face.cpp IsRendered.cpp Renderer.cpp SkyBox.cpp
GRAPHICS_SOURCES=$(addprefix src/graphics/, $(GRAPHICS_FILES))

RESOURCES_FILES=AssetLoader.cpp Assets.cpp misc.cpp ResourceReader.cpp Terrain.cpp
RESOURCES_SOURCES=$(addprefix src/resources/, $(RESOURCES_FILES))

SOURCES=$(GAME_SOURCES) $(GRAPHICS_SOURCES) $(RESOURCES_SOURCES)

OBJECTS=$(SOURCES:.cpp=.o) resource.yy.o resource.tab.o

all: library test01

test01: tests/test01.o
	$(CXX)  $^ -L ./ -lNDE `pkg-config sdl glu gl --cflags --libs`  $(CXXFLAGS)   -o test01.bin

testc: test.o
	$(CC)  $^ -L ./ `pkg-config sdl glu gl --libs` -lglut  $(CFLAGS)   -o test.bin


library: lexer parser libNDE.a

libNDE.a: $(OBJECTS) 
	echo "Objects= $^"
	$(AR) rs $@ $^ 

.cpp.o:
	$(CXX) -c $<  $(CXXFLAGS) -o $@

.c.o: 
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@


lexer: resource.yy.c

parser: resource.tab.c

resource.yy.c: src/resources/resource.l
	flex $(FLEXFLAGS) $<

resource.tab.c: src/resources/resource.y
	bison $(BISONFLAGS) $<

clean:
	-rm `find . \( -name "*.o" -o -name "*.bin" -o -name "*.so" -o -name "*.a" -o -name "*.yy.c" -o -name "*.tab.[ch]" -o -name "*.o" -o -name "*.output" \)  -print`

run:
	./test01.bin 