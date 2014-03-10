all: multi clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

semaphores.o: semaphores.cc
	g++ -c semaphores.cc

multi: basic.o semaphores.o
	g++ basic.o semaphores.o -o multi -lSDL -lSDL_image -lSDL_ttf

clean:
	rm -rf *.o
