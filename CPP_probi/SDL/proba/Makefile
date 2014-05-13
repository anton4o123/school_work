all: main clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

proba.o: proba.cc
	g++ -c proba.cc

main: basic.o proba.o
	g++ basic.o proba.o -lSDL -lSDL_image

clean:
	rm -rf *.o
