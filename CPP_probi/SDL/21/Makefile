all: camera clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

scrolling.o: dot.hh scrolling.cc
	g++ -c scrolling.cc

camera: basic.o timer.o scrolling.o
	g++ basic.o timer.o scrolling.o -o camera -lSDL -lSDL_image

clean:
	rm -rf *.o
