all: timer clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

main.o: ../headers/basic.hh timer.cc
	g++ -c timer.cc

timer: basic.o main.o
	g++ basic.o timer.o -o timer -lSDL_image -lSDL_ttf

clean:
	rm -rf *.o
