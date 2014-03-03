all: dot clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

circular.o: dot.hh circular.cc
	g++ -c circular.cc

dot: basic.o timer.o circular.o
	g++ basic.o timer.o circular.o -o dot -lSDL_image

clean:
	rm -rf *.o
