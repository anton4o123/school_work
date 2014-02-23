all: music clean

basic.o: basic.hh basic.cc
	g++ -c basic.cc

main.o: main.cc basic.hh
	g++ -c main.cc

music: main.o basic.o
	g++ main.o basic.o -o music -lSDL_image -lSDL_ttf -lSDL_mixer

clean:
	rm -rf *.o
