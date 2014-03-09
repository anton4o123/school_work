all: dot clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

independent.o: dot.hh independent.cc
	g++ -c independent.cc

dot: basic.o timer.o independent.o
	g++ basic.o timer.o independent.o -o dot -lSDL -lSDL_image

clean:
	rm -rf *.o
