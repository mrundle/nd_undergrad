#ifndef HAND_H_
	#define HAND_H_

#include <vector>
#include <iostream>
using namespace std;

class Hand {

	public:

		Hand(); // default constructor
		void clearHand();
		int returnFirst();
		void addCard(int);
		void printCards();
		int sumCards();

	private:

		vector<int> Cards;

};

#endif
