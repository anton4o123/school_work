all: gl clean

basic_GL.o: ../headers/basic_GL.hh ../headers/basic_GL.cc
	g++ -c ../headers/basic_GL.cc

main.o: main.cc
	g++ -c main.cc

gl: basic_GL.o main.o
	g++ basic_GL.o main.o -o gl -lGL -lGLU -lglut

clean:
	rm -rf *.o