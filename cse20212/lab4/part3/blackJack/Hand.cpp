#include "Hand.h"

Hand::Hand() {}

void Hand::printCards() {
	vector<int>::const_iterator i;
	for(i=Cards.begin(); i!=Cards.end(); i++){
		cout << *i << " ";
	}
	return;
}

int Hand::sumCards() {
	int sum = 0;
	vector<int>::const_iterator i;
	for(i=Cards.begin(); i!=Cards.end(); i++){
		sum += *i;
	}
	return sum;
}

void Hand::addCard(int Card) {
	Cards.push_back(Card);
}

int Hand::returnFirst() {
	return Cards.front();
}

void Hand::clearHand() {
	Cards.clear();
}
