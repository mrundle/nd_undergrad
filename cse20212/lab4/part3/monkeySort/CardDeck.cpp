/*
Matt Rundle
cse20212
lab4, part 2

This is the implementation for the CardDeck class.
*/
#include "CardDeck.h"

CardDeck::CardDeck() {
	int n = 52;
}

CardDeck::CardDeck(int n){

	for(int i=0; i<n; i++){
		Deck.push_back(i);
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
	
int CardDeck::getSize(){
	return Deck.size();
}

void CardDeck::shuffle(){
	random_shuffle(Deck.begin(), Deck.end());
}

int CardDeck::inOrder(){
	deque<int>::const_iterator i;
	for(i=(Deck.begin()+1); i!=Deck.end(); i++){
		if(*i < *(i-1)) return 0;
	}
	return 1;
}

int CardDeck::monkeySort(){
	int sortCounter=0;
	this->shuffle();
	while((this->inOrder()) == 0){
		this->shuffle();
		sortCounter++;
	}
	return sortCounter;
}
