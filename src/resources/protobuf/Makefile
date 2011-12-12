CXXSOURCES=*.cpp *.cc

all: test
	test.exe

protoclasses: resource.proto
	protoc --cpp_out=. resource.proto

test: protoclasses
	g++ $(CXXSOURCES) -I. -lprotobuf -o test.exe

clean:
	-rm *.pb.h *.pb.cc *.exe