/*
Matt Rundle
cse20212
lab4, part 2

This is the implementation for the CardDeck class.
*/
#include "CardDeck.h"

// Constructor (default value of n is 52)
CardDeck::CardDeck(int n){

	for(int i=0; i<n; i++){
		Deck.push_back(i);
	}

	// change the random number seed for the shuffle
	srand( unsigned(time(0)) );
}

// Overloading of the << operator to print the contents of the deck
ostream &operator<< (ostream & print, const CardDeck & C){
	deque<int>::const_iterator i;

	for(i=C.Deck.begin(); i!=C.Deck.end(); i++){
		if(i!=(C.Deck.end()-1)){
			print << *i << ", ";
		}else{
			print << *i;
		}	
	}
	print << "\n";

	return print;
}

// Returns the size of the deck	
int CardDeck::getSize(){
	return Deck.size();
}

// Shuffles the deck 
void CardDeck::shuffle(){
	random_shuffle(Deck.begin(), Deck.end());
}
