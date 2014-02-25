all: frames clean

basic.o: ../headers/basic.cc ../headers/basic.hh
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.cc ../headers/timer.hh
	g++ -c ../headers/timer.cc

control.o: control.cc
	g++ -c control.cc

frames: basic.o timer.o control.o
	g++ basic.o timer.o control.o -o frames -lSDL_image -lSDL_ttf

clean:
	rm -rf *.o
