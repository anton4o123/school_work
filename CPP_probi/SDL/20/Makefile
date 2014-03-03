all: foo clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

animation.o: foo.hh animation.cc
	g++ -c animation.cc

foo: basic.o timer.o animation.o
	g++ basic.o timer.o animation.o -o foo -lSDL_image

clean:
	rm -rf *.o
