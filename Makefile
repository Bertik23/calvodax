CXX := g++
CFLAGS := -Wall -pedantic -Wextra -Weffc++
LD := g++

SRC=$(wildcard src/*.cpp src/*/*.cpp)
HDR=$(wildcard src/*.h src/*/*.h)
OBJ=$(patsubst src/%.cpp, build/%.o, $(SRC))

all: clean build

run: build
	./calvodax

build: $(OBJ)
	$(LD) $(LDFLAGS) $^ -o calvodax

clean:
	rm -f ./calvodax
	rm -rf ./build

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
	
#main.o: main.cpp numbers/number.h numbers/../typedefs.h
#	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o ./build/$@
