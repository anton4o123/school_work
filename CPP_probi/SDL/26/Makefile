all: size clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

resize.o: window.hh resize.cc
	g++ -c resize.cc

size: basic.o resize.o
	g++ basic.o resize.o -o size -lSDL_image

clean:
	rm -rf *.o
