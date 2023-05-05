CXX := g++
CFLAGS := -Wall -pedantic -Wextra -Weffc++

all: clean build

run: build
	./calvodax

build: build/main.o
	mkdir -p build
	$(CXX) $(CFLAGS) 

clean:
	rm -f ./calvodax
	rm -rf ./build

$(wildcard *.o): ($wildcard *.cpp)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o ./build/$@
	
#main.o: main.cpp numbers/number.h numbers/../typedefs.h
	#$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o ./build/$@
