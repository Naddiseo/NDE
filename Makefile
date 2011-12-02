CXXFLAGS=-g -I. -std=c++0x -Weffc++ -Wall -Werror -Wfatal-errors -fPIC

SOURCES=rendering/Renderer.cpp \
		game/Game.cpp

OBJECTS=$(SOURCES:.cpp=.o)

library: nde.so

nde.so: $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) -shared -o $@

.cpp.o:
	$(CXX) -c $<  $(CXXFLAGS) -o $@
	
clean:
	-rm `find . -name "*.o" -print` *.so