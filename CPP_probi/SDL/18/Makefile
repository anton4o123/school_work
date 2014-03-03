all: dot clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

perpixel.o: dot.hh perpixel.cc
	g++ -c perpixel.cc

dot: basic.o timer.o perpixel.o
	g++ basic.o timer.o perpixel.o -o dot -lSDL_image

clean:
	rm -rf *.o
