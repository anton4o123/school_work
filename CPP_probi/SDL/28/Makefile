all: dot clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

engine.o: particle.hh dot.hh engine.cc
	g++ -c engine.cc

dot: basic.o timer.o engine.o
	g++ basic.o timer.o engine.o -o dot -lSDL_image

clean:
	rm -rf *.o
