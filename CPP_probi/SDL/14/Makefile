all: frames clean

basic.o: ../headers/basic.cc ../headers/basic.hh
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.cc ../headers/timer.hh
	g++ -c ../headers/timer.cc

frame_rate.o: frame_rate.cc
	g++ -c frame_rate.cc

frames: basic.o timer.o frame_rate.o
	g++ basic.o timer.o frame_rate.o -o timer -lSDL_image -lSDL_ttf

clean:
	rm -rf *.o
