INCFLAGS=-I. `pkg-config sdl gl glu ILU bullet protobuf --cflags`
LINKFLAGS=`pkg-config sdl gl glu ILU bullet protobuf --libs`
CXXFLAGS=-g $(INCFLAGS) $(LINKFLAGS) -DUSE_OPENGL=1 -DNDEBUG=1  -std=c++0x -Wall -Werror -Wfatal-errors 
CFLAGS=-g -I.

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

SCRIPT_FILES=Lexer.cpp Token.cpp
SCRIPT_SOURCES=$(addprefix script/, $(SCRIPT_FILES))

SOUND_FILES=
SOUND_SOURCES=$(addprefix sound/, $(SOUND_FILES))

SYS_FILES=
SYS_SOURCES=$(addprefix sys/, $(SYS_FILES))

TESTS_FILES=scripttests/lexer.cpp scripttests/progs.cpp main.cpp
TESTS_SOURCES=$(addprefix tests/, $(TESTS_FILES))

TOOLS_FILES=
TOOLS_SOURCES=$(addprefix tools/, $(TOOLS_FILES))

UI_FILES=
UI_SOURCES=$(addprefix ui/, $(UI_FILES))

SOURCES=$(AI_SOURCES) $(GAME_SOURCES) $(GRAPHICS_SOURCES) $(LIB_SOURCES) $(MATH_SOURCES) \
		$(PHYSICS_SOURCES) $(RESOURCES_SOURCES) $(SCRIPT_SOURCES) $(SOUND_SOURCES) $(SYS_SOURCES) \
		$(TOOLS_SOURCES) $(UI_SOURCES)

OBJECTS= $(SOURCES:.cpp=.o)

ifeq ($(NPROCS),)
OS:=$(shell uname -s)

ifeq ($(OS),Linux)
	NPROCS:=$(shell echo "1+$(shell grep -c ^processor /proc/cpuinfo)"|bc)
endif
	

%:
	$(MAKE) -j$(NPROCS) NPROCS=$(NPROCS) $@
else

all: clear library scripttests

scripttests: libNDE.a $(TESTS_SOURCES:.cpp=.o)
	$(CXX)  $^ -L ./ -lNDE -lcppunit $(LINKFLAGS)  $(CXXFLAGS) -o ndetests.bin

library: libNDE.a

libNDE.a:  $(OBJECTS) 
	$(AR) rs $@ $^ 

.cpp.o:
	$(CXX) -c $<  $(CXXFLAGS) -o $@

.c.o: 
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

proto: src/resources/pb/resource.pb.o

src/resources/pb/resource.pb.o: src/resources/pb/resource.pb.cc
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

src/resources/pb/resource.pb.cc: src/resources/pb/resource.proto
	protoc --cpp_out=. $^

clean:
	-rm `find . \( -name "*.o" -o -name "*.bin" -o -name "*.so" -o -name "*.a" -o -name "*.yy.c" -o -name "*.pb.h" -o -name "*.pb.cc" -o -name "*.o" -o -name "*.output" \)  -print`

clear:
	clear

test: clear library scripttests
	./ndetests.bin

run:
	./nde.bin 

endif