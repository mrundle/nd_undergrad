/*
Matt Rundle
cse20212
lab4, part 2

This is the header file for the CardDeck class.
*/
#ifndef CARDDECK_H_
	#define CARDDECK_H_

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
	
	int Deal();
	int getSize();
	void shuffle();

private:

	deque<int> Deck;

};

#endif
