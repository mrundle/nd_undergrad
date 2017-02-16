/*
Matthew Rundle
cse20212.01
lab4

This is the driver for the CardDeck class. It creates a deck of 10 cards,
displays the deck, shuffles the cards, and then prints the deck again.
*/

#include "CardDeck.h"

int main(){

CardDeck myDeck(10);

cout << myDeck;

myDeck.shuffle();

cout << myDeck;

}
