MINGWDIR=C:/MinGW
MINGWINC=$(MINGWDIR)/include
MINGWLIB=$(MINGWDIR)/lib
CXX=$(MINGWDIR)/bin/g++

BULLETLIBS=BulletDynamics BulletSoftBody BulletCollision LinearMath
OTHERLIBS=opengl32 SDL glu32 glew ILU DevIL protobuf z
LIBS=$(OTHERLIBS) $(BULLETLIBS)
INCS=$(MINGWINC) $(MINGWINC)/bullet . ./includes

INCFLAGS=$(addprefix -I, $(INCS))
LINKFLAGS=-L$(MINGWLIB) $(addprefix -l, $(LIBS)) -static-libgcc -static-libstdc++
CXXFLAGS=-g $(INCFLAGS) $(LINKFLAGS) -DWINDOWS -DNDEBUG=1 -std=c++0x -Wall -Werror -Wfatal-errors

GAME_FILES=Camera.cpp Entity.cpp Game.cpp Input.cpp KeyboardMap.cpp Scene.cpp Settings.cpp World.cpp
GAME_SOURCES=$(addprefix src/game/, $(GAME_FILES))

GRAPHICS_FILES=Face.cpp GLAPI.cpp IsRendered.cpp OpenGL.cpp Renderer.cpp SkyBox.cpp
GRAPHICS_SOURCES=$(addprefix src/graphics/, $(GRAPHICS_FILES))

RESOURCES_FILES=Assets.cpp AssetsLoader.cpp Color.cpp Material.cpp Mesh.cpp Terrain.cpp
RESOURCES_SOURCES=$(addprefix src/resources/, $(RESOURCES_FILES))

SOURCES=$(GAME_SOURCES) $(GRAPHICS_SOURCES) $(RESOURCES_SOURCES)

OBJECTS=src/resources/pb/resource.pb.o $(SOURCES:.cpp=.o)

EXE=test01.exe

rebuild: clean all

all: library test01

test01: libNDE.a tests/test01.o tests/KeybaordMapSetup.o
	$(CXX) $^ -L. -lNDE  $(CXXFLAGS) -o $(EXE)

library: libNDE.a

libNDE.a: $(OBJECTS)
	$(AR) rs $@ $^ 

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS) -o $@

.c.o: 
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

src/resources/pb/resource.pb.o: src/resources/pb/resource.pb.cc
	$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

src/resources/pb/resource.pb.cc: src/resources/pb/resource.proto
	protoc --cpp_out=. $^

clean:
	-rm `find . \( -name "*.o" -o -name "*.bin" -o -name "*.exe" -o -name "*.so" -o -name "*.a" -o -name "*.yy.c" -o -name "*.pb.h" -o -name "*.pb.cc" -o -name "*.o" -o -name "*.output" \)  -print`

run:
	./$(EXE)
