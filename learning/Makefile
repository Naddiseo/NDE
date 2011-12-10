CXXFLAGS=-g -I. -DNDEBUG=1  -Weffc++ -std=c++0x -Wall -Wfatal-errors `pkg-config sdl gl glu --cflags --libs`

all:
	clear
	$(CXX) main.cpp $(CXXFLAGS) -o test.bin

run:
	clear
	./test.bin