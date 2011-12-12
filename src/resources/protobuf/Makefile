CXXSOURCES=*.cpp *.cc
LIBPATH=C:/MinGW/lib
LIBS=-lprotobuf
INCLUDES=-I.
CXXFLAGS=$(INCLUDES) -L$(LIBPATH) $(LIBS)

all: test
	test.exe test.txt

protoclasses: resource.proto
	protoc --cpp_out=. resource.proto

test: protoclasses
	g++ $(CXXSOURCES) $(CXXFLAGS) -o test.exe
