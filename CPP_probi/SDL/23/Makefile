all: input clean

basic.o: ../headers/basic.cc ../headers/basic.hh
	g++ -c ../headers/basic.cc

writing.o: string_input.hh writing.cc
	g++ -c writing.cc

input: basic.o writing.o
	g++ basic.o writing.o -o input -lSDL -lSDL_image -lSDL_ttf

clean:
	rm -rf *.o
