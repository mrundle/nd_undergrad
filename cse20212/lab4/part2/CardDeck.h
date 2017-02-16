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

	CardDeck(int n = 52); // default constructor, with 52 cards as default value 
	
	int getSize();
	void shuffle();

private:

	deque<int> Deck;

};
