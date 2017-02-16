all: main

main: main.o Distances.o
	g++ main.o Distances.o -o main

main.o: main.cpp
	g++ -c main.cpp
Distances.o: Distances.cpp
	g++ -c Distances.cpp

clean:
	rm -f *.o main
