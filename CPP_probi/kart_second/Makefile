all: war clean

card.o: card.hh card.cc
	g++ -c card.cc

main.o: main.cc
	g++ -c main.cc

war: card.o main.o
	g++ card.o main.o -o war

clean:
	rm -rf *.o
