all: calc

calc: calc.o Rational.o
	g++ calc.o Rational.o -o calc

main.o: calc.cpp
	g++ -c calc.cpp
Rational.o: Rational.cpp
	g++ -c Rational.cpp

clean:
	rm -f *.o calc
