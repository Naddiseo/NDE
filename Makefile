INCFLAGS=-I./includes -I.
LINKFLAGS=`pkg-config sdl gl glu ILU bullet protobuf --cflags --libs`
CXXFLAGS=-g $(INCFLAGS) $(LINKFLAGS) -DNDEBUG=1  -std=c++0x -Wall -Werror -Wfatal-errors 
CFLAGS=-g -I./includes 

GAME_FILES=Camera.cpp Entity.cpp Game.cpp Scene.cpp Settings.cpp World.cpp
GAME_SOURCES=$(addprefix src/game/, $(GAME_FILES))

GRAPHICS_FILES=Color.cpp Face.cpp IsRendered.cpp Renderer.cpp SkyBox.cpp
GRAPHICS_SOURCES=$(addprefix src/graphics/, $(GRAPHICS_FILES))

MATH_FILES=util.cpp
MATH_SOURCES=$(addprefix src/math/, $(MATH_FILES))

MISC_FILES=HasId.cpp
MISC_SOURCES=$(addprefix src/misc/, $(MISC_FILES))

RESOURCES_FILES=Assets.cpp AssetsLoader.cpp Material.cpp Mesh.cpp Terrain.cpp
RESOURCES_SOURCES=$(addprefix src/resources/, $(RESOURCES_FILES))

SOURCES=$(GAME_SOURCES) $(GRAPHICS_SOURCES) $(RESOURCES_SOURCES) $(MISC_SOURCES) $(MATH_SOURCES)

OBJECTS=src/resources/pb/resource.pb.o $(SOURCES:.cpp=.o)

all: clear library test01

test01: libNDE.a tests/test01.o
	$(CXX)  $^ -L ./ -lNDE $(LINKFLAGS)  $(CXXFLAGS)   -o nde.bin

library: libNDE.a

libNDE.a:  $(OBJECTS) 
	$(AR) rs $@ $^ 

.cpp.o:
	$(CXX) -c $<  $(CXXFLAGS) -o $@

.c.o: 
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

proto: src/resources/pb/resource.pb.o

src/resources/pb/resource.pb.o: src/resources/pb/resource.pb.cc
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-effc++ -Wno-all -Wno-fatal-errors -o $@

src/resources/pb/resource.pb.cc: src/resources/pb/resource.proto
	protoc --cpp_out=. $^

clean:
	-rm `find . \( -name "*.o" -o -name "*.bin" -o -name "*.so" -o -name "*.a" -o -name "*.yy.c" -o -name "*.pb.h" -o -name "*.pb.cc" -o -name "*.o" -o -name "*.output" \)  -print`

clear:
	clear

run:
	./nde.bin 