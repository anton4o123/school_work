all: advance clean

basic.o: ../headers/basic.cc ../headers/basic.hh
	g++ -c ../headers/basic.cc

main.o: advanced_timer.cc
	g++ -c advanced_timer.cc

advance: advanced_timer.o basic.o
	g++ advanced_timer.o basic.o -o timer -lSDL_image -lSDL_ttf

clean:
	rm -rf *.o
