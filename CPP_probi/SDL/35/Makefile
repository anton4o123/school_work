all: multi clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

mutex.o: mutex.cc
	g++ -c mutex.cc

multi: basic.o mutex.o
	g++ basic.o mutex.o -o multi -lSDL -lSDL_image

clean:
	rm -rf *.o
