all: square clean

basic.o: ../headers/basic.cc ../headers/basic.hh
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.cc ../headers/timer.hh ../headers/basic.hh
	g++ -c ../headers/timer.cc

collision.o: ../headers/basic.hh square.hh collision.cc
	g++ -c collision.cc

square: basic.o timer.o collision.o
	g++ basic.o timer.o collision.o -o square -lSDL_image

clean:
	rm -rf *.o
