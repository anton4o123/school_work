all: key

basic.o: basic.cc basic.hh
	g++ -c basic.cc

key_states.o: key_states.cc
	g++ -c key_states.cc

key: key_states.o basic.o
	g++ key_states.o basic.o -lSDL_image -lSDL_ttf

clean:
	rm *.o
