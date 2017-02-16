/*
Matt Rundle
cse20212
lab4, part 2

This is the implementation for the CardDeck class.
*/
#include "CardDeck.h"

CardDeck::CardDeck() {

	// iterate through the four suits
	int cardValue = 0;
	for(int suit=0; suit<4; suit++){ 
		for(int i=1; i<=13; i++){
			if(i==1) cardValue = 11; // Ace
			if((i>=2) && (i<=10)) cardValue = i; // Number Cards
			if(i>10) cardValue = 10; // Face Cards
			Deck.push_back(cardValue);
		}
	}

	// change the random number seed for the shuffle
	srand( unsigned(time(0)) );
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
	
	if(Deck.size() < 15){
		Deck.clear();
		// Repopulate deck
		int cardValue;
		for(int suit=0; suit<4; suit++){ 
			for(int i=1; i<=13; i++){
				if(i=1) cardValue = 11; // Ace
				if((i>=2) && (i<=10)) cardValue = i; // Number Cards
				if(i>10) cardValue = 10; // Face Cards
				Deck.push_back(cardValue);
			}
		}
	}

	return value;
}

int CardDeck::getSize(){
	return Deck.size();
}

void CardDeck::shuffle(){
	random_shuffle(Deck.begin(), Deck.end());
}


