/*
Matt Rundle
cse20212
lab4, part 2

This is the implementation for the CardDeck class.
*/
#include "CardDeck.h"

CardDeck::CardDeck() {

	// iterate through the four suits
	for(int suit=0; suit<4; suit++){ 
		for(int i=1; i<=13; i++){
			Deck.push_back(i);
		}
	}

}

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

int CardDeck::Deal(){
	int value = Deck.back();
	Deck.pop_back();

	return value;
}

int CardDeck::getSize(){
	return Deck.size();
}

void CardDeck::shuffle(){
	// change the random number seed for the shuffle
	srand( unsigned(time(0)) );

	random_shuffle(Deck.begin(), Deck.end());
}


