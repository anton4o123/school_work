all: dot clean

basic.o: ../headers/basic.hh ../headers/basic.cc
	g++ -c ../headers/basic.cc

timer.o: ../headers/timer.hh ../headers/timer.cc
	g++ -c ../headers/timer.cc

joystick: dot.hh joystick.cc
	g++ -c joystick.cc

dot: basic.o timer.o joystick.o
	g++ basic.o timer.o joystick.o -o dot -lSDL_image

clean:
	rm -rf *.o
