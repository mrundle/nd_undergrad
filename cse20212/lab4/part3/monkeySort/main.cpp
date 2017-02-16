/*
Matt Rundle

Monkey Sort!
*/


#include "CardDeck.h"

int main(){

CardDeck sevenDeck(7);
CardDeck eightDeck(8);
CardDeck nineDeck(9);

int numShuffles;

for(int i=0;i<3;i++){
numShuffles = sevenDeck.monkeySort();
cout << "For a deck of seven, monkey sort took " << numShuffles << " shuffles to order the deck." << endl;
}

for(int i=0;i<3;i++){
numShuffles = eightDeck.monkeySort();
cout << "For a deck of eight, monkey sort took " << numShuffles << " shuffles to order the deck." << endl;
}

for(int i=0;i<3;i++){
numShuffles = nineDeck.monkeySort();
cout << "For a deck of nine, monkey sort took " << numShuffles << " shuffles to order the deck." << endl;
}

return 0;
}
