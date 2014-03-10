all: multi clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

thread.o: thread.cc
	g++ -c thread.cc

multi: basic.o thread.o
	g++ basic.o thread.o -o multi -lSDL -lSDL_image

clean:
	rm -rf *.o
