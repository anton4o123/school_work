all: shape

point.o: point.cc point.hh
	g++ -c point.cc

circle.o: circle.cc circle.hh base.hh
	g++ -c circle.cc

line.o: line.cc line.hh base.hh
	g++ -c line.cc

main.o: main.cc line.hh base.hh circle.hh point.hh
	g++ -c main.cc

shape: main.o point.o circle.o line.o
	g++ main.o point.o circle.o line.o -o shape
	
clean:
	rm -rf *.o *~ shape a.out
