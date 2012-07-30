INCFLAGS=-I./includes -I.
LINKFLAGS=`pkg-config sdl gl glu ILU bullet protobuf python --cflags --libs`
CXXFLAGS=-g $(INCFLAGS) $(LINKFLAGS) -DUSE_OPENGL=1 -DNDEBUG=1  -std=c++0x -Wall -Werror -Wfatal-errors 
CFLAGS=-g -I./includes 

AI_FILES=
AI_SOURCES=$(addprefix ai/, $(AI_FILES))

GAME_FILES=
GAME_SOURCES=$(addprefix game/, $(GAME_FILES))

GRAPHICS_FILES=
GRAPHICS_SOURCES=$(addprefix graphics/, $(GRAPHICS_FILES))

LIB_FILES=
LIB_SOURCES=$(addprefix lib/, $(LIB_FILES))

MATH_FILES=
MATH_SOURCES=$(addprefix math/, $(MATH_FILES))

PHYSICS_FILES=
PHYSICS_SOURCES=$(addprefix physics/, $(PHYSICS_FILES))

RESOURCES_FILES=
RESOURCES_SOURCES=$(addprefix resources/, $(RESOURCES_FILES))

SCRIPT_FILES=
SCRIPT_SOURCES=$(addprefix script/, $(SCRIPT_FILES))

SOUND_FILES=
SOUND_SOURCES=$(addprefix sound/, $(SOUND_FILES))

SYS_FILES=
SYS_SOURCES=$(addprefix sys/, $(SYS_FILES))

TESTS_FILES=
TESTS_SOURCES=$(addprefix tests/, $(TESTS_FILES))

TOOLS_FILES=
TOOLS_SOURCES=$(addprefix tools/, $(TOOLS_FILES))

UI_FILES=
UI_SOURCES=$(addprefix ui/, $(UI_FILES))

SOURCES=$(AI_SOURCES) $(GAME_SOURCES) $(GRAPHICS_SOURCES) $(LIB_SOURCES) $(MATH_SOURCES) \
		$(PHYSICS_SOURCES) $(RESOURCES_SOURCES) $(SCRIPT_SOURCES) $(SOUND_SOURCES) $(SYS_SOURCES) \
		$(TOOLS_SOURCES) $(UI_SOURCES)

OBJECTS=$(SOURCES:.cpp=.o)

all: clear library test01

test01: libNDE.a game/main.o
	$(CXX)  $^ -L ./ -lNDE $(LINKFLAGS)  $(CXXFLAGS)   -o nde.bin

library: libNDE.a

libNDE.a:  $(OBJECTS) 
	$(AR) rs $@ $^ 

.cpp.o:
	$(CXX) -c $<  $(CXXFLAGS) -o $@

.c.o: 
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@


clean:
	-rm `find . \( -name "*.o" -o -name "*.bin" -o -name "*.so" -o -name "*.a" -o -name "*.yy.c" -o -name "*.pb.h" -o -name "*.pb.cc" -o -name "*.o" -o -name "*.output" \)  -print`

clear:
	clear

run:
	./nde.bin 