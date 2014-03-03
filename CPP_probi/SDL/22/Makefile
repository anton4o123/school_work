all: screen clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

scrolling.o: scrolling.cc
	g++ -c scrolling.cc

screen: basic.o timer.o scrolling.o
	g++ basic.o timer.o scrolling.o -o screen -lSDL_image

clean:
	rm -rf *.o
