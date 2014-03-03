all: game clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

save.o: dot.hh save.cc
	g++ -c save.cc

game: basic.o timer.o save.o
	g++ basic.o timer.o save.o -o game -lSDL_image

clean:
	rm -rf *.o
