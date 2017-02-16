/*
Matt Rundle
cse20212
lab4, part 2

This is the header file for the CardDeck class.
*/

#include <iostream>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class CardDeck {

friend ostream &operator<< (ostream &, const CardDeck &);

public:

	CardDeck();
	CardDeck(int);
	
	int getSize();
	void shuffle();
	int inOrder();
	int monkeySort();

private:

	deque<int> Deck;

};
