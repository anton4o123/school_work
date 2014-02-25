all: dot clean

basic.o: ../headers/basic.cc ../headers/basic.hh
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.cc ../headers/timer.hh
	g++ -c ../headers/timer.cc

motion.o: motion.cc dot.hh
	g++ -c motion.cc

dot: basic.o timer.o motion.o
	g++ basic.o timer.o motion.o -o dot -lSDL_image

clean:
	rm -rf *.o
