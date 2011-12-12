CXXSOURCES=*.cpp *.cc

all: test
	test.exe

protoclasses: resource.proto
	protoc --cpp_out=. resource.proto

test: protoclasses
	g++ $(CXXSOURCES) -I. -lprotobuff -o test.exe
