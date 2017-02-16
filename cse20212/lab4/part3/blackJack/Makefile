all: main

main: main.o CardDeck.o Hand.o
	g++ main.o CardDeck.o Hand.o -o main

main.o: main.cpp
	g++ -c main.cpp
CardDeck.o: CardDeck.cpp
	g++ -c CardDeck.cpp
Hand.o: Hand.cpp
	g++ -c Hand.cpp

clean:
	rm -f *.o main
