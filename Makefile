#MAKEFLAGS = --jobs=8

CXX := g++
CXXFLAGS := -std=c++17 -Wall -pedantic -Wextra -Weffc++ -Wdiv-by-zero -Wmaybe-uninitialized -Wmisleading-indentation -fsanitize=undefined -fsanitize=address -O2
# CXXFLAGS := -Wall -Wextra -pedantic -Wabi-tag -Waddress -Waggregate-return -Waggressive-loop-optimizations   -Waligned-new -Walloca   -Walloc-zero   -Warray-bounds   -Wattributes  -Wbool-compare -Wbool-operation -Wbuiltin-declaration-mismatch -Wbuiltin-macro-redefined -Wcast-align -Wcast-qual -Wchar-subscripts  -Wclobbered -Wcomment -Wcomments  -Wconditionally-supported -Wconversion  -Wconversion-null -Wcoverage-mismatch -Wcpp -Wctor-dtor-privacy -Wdangling-else -Wdate-time  -Wdelete-incomplete -Wdelete-non-virtual-dtor -Wdeprecated -Wdeprecated-declarations  -Wdisabled-optimization   -Wdiv-by-zero -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond  -Weffc++ -Wempty-body -Wendif-labels -Wenum-compare -Wexpansion-to-defined -Wfloat-conversion -Wfloat-equal -Wformat -Wformat-contains-nul -Wformat-extra-args -Wformat-nonliteral -Wformat-overflow -Wformat-security -Wformat-signedness -Wformat-truncation -Wformat-truncation -Wformat-y2k -Wformat-zero-length -Wframe-address  -Wfree-nonheap-object  -Whsa -Wignored-attributes -Wignored-qualifiers -Wimport  -Winherited-variadic-ctor -Winit-self -Winline -Wint-in-bool-context -Wint-to-pointer-cast -Winvalid-memory-model -Winvalid-offsetof -Winvalid-pch -Wliteral-suffix -Wlogical-not-parentheses -Wlogical-op -Wlong-long -Wlto-type-mismatch -Wmain -Wmaybe-uninitialized -Wmemset-elt-size -Wmemset-transposed-args -Wmisleading-indentation -Wmissing-braces -Wmissing-declarations -Wmissing-field-initializers -Wmissing-include-dirs -Wmultichar -Wmultiple-inheritance -Wnamespaces -Wnarrowing -Wnoexcept -Wnoexcept-type -Wnonnull -Wnonnull-compare  -Wnon-template-friend -Wnon-virtual-dtor -Wnormalized -Wnull-dereference -Wodr -Wold-style-cast -Wopenmp-simd -Woverflow -Woverlength-strings -Woverloaded-virtual -Wpacked -Wpacked-bitfield-compat -Wpadded -Wparentheses -Wplacement-new -Wpmf-conversions -Wpointer-arith -Wpointer-compare -Wpragmas -Wpsabi -Wredundant-decls -Wregister -Wreorder -Wrestrict -Wreturn-local-addr -Wreturn-type -Wscalar-storage-order -Wsequence-point -Wshadow -Wshift-count-negative -Wshift-count-overflow -Wshift-negative-value -Wshift-overflow -Wshift-overflow -Wsign-compare -Wsign-conversion -Wsign-promo -Wsized-deallocation -Wsizeof-array-argument -Wsizeof-pointer-memaccess -Wstack-protector  -Wstrict-aliasing -Wstrict-null-sentinel -Wstrict-overflow -Wstringop-overflow -Wstringop-overflow -Wsubobject-linkage  -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch -Wswitch-bool -Wswitch-default -Wswitch-enum -Wswitch-unreachable -Wsync-nand -Wsynth -Wsystem-headers -Wtautological-compare -Wtemplates -Wterminate -Wtrampolines -Wtrigraphs -Wtype-limits -Wundef -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wunsafe-loop-optimizations -Wunused -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-const-variable -Wunused-const-variable -Wunused-function -Wunused-label -Wunused-local-typedefs -Wunused-macros -Wunused-parameter -Wunused-result -Wunused-value -Wunused-variable -Wuseless-cast -Wvarargs -Wvariadic-macros -Wvector-operation-performance -Wvirtual-inheritance -Wvirtual-move-assign -Wvla  -Wvolatile-register-var -Wwrite-strings -Wzero-as-null-pointer-constant

LD := g++
LDFLAGS := -fsanitize=undefined -fsanitize=address

SRC=$(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp)
HDR=$(wildcard src/*.h src/*/*.h src/*/*/*.h)
OBJ=$(patsubst src/%.cpp, build/%.o, $(SRC))

.PHONY: all run build clean doc build_ test build_test zip compile compile_

all: clean build

compile: build/Makefile.d compile_

compile_: $(OBJ)
	$(LD) $(LDFLAGS) $(filter-out build/test.o, $^) -o havlialb

run: build
	./calvodax

build: build/Makefile.d build_

build_: $(OBJ)
	$(LD) $(LDFLAGS) $(filter-out build/test.o, $^) -o calvodax
	cp ./calvodax ./havlialb

test: build/Makefile.d build_test
	./calvodax

build_test: $(OBJ)
	$(LD) $(LDFLAGS) $(filter-out build/main.o, $^) -o calvodax
	cp ./calvodax ./havlialb

clean:
	rm -rf ./havlialb
	rm -f havlialb.zip
	rm -f ./calvodax
	rm -rf ./build

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@
	
#main.o: main.cpp numbers/number.h numbers/../typedefs.h
#	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o ./build/$@

doc:
	rm -rf ./doc
	doxygen

zip:
	rm -f havlialb.zip
	rm -rf tmp
	mkdir -p tmp/havlialb
	cp -r src examples Doxyfile Grammar Makefile zadani.txt prohlaseni.txt README.md tmp/havlialb
	cd tmp && zip -ll -r ../havlialb havlialb
	rm -r tmp/havlialb

-include build/Makefile.d

build/Makefile.d: $(SRC) $(HDR)
	mkdir -p build
	rm -f build/Makefile.d
	$(foreach s, $(SRC), $(CXX) -MM $(s) -MT $(patsubst src/%.cpp, build/%.o, $(s)) -MP >> $@ ;)

