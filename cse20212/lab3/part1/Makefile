all: main

main: main.o BankAccount.o carLoan.o
	g++ main.o BankAccount.o carLoan.o -o main

main.o: main.cpp
	g++ -c main.cpp
BankAccount.o: BankAccount.cpp
	g++ -c BankAccount.cpp
carLoan.o: carLoan.cpp
	g++ -c carLoan.cpp

clean:
	rm -f *.o main
