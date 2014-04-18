all: gl clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

open.o: open.cc
	g++ -c open.cc

gl: basic.o timer.o open.o
	g++ basic.o timer.o open.o -o gl -lSDL -lSDL_image -lGL -lGLU

clean:
	rm -rf *.o