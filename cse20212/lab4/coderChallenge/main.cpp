/*
WAR

Matt Rundle
cse20212.01
*/
#include "CardDeck.h"
#include <iostream>
#include <vector>
#include <deque>
#include <stdio.h>

using namespace std;

// Function to print a vector of ints
void printVec(const vector<int>& Vec){
	vector<int>::const_iterator i;
	for(i=Vec.begin(); i!=Vec.end(); i++){
		cout << *i << " ";
	}
	return;
}

int sumVec(const vector<int>& Vec){
	int sum = 0;
	vector<int>::const_iterator i;
	for(i=Vec.begin(); i!=Vec.end(); i++){
		sum += *i;
	}
	return sum;
}

void printHeader() {
	printf("\033[2J\033[H");
	cout << "################################" << endl;
	cout << "#            WAR               #" << endl;
	cout << "#        by Matt Rundle        #" << endl;
	cout << "################################\n" << endl;
	return;
}

// inserts the contents of a vector into the front of a deque
deque<int> insertVec(vector<int> source,deque<int> destination){
	vector<int>::const_iterator i;
	for(i=source.begin();i!=source.end();i++){
		destination.push_front(*i);
	}
	return destination;
}

int main(){
	CardDeck myDeck;

	myDeck.shuffle();

	deque<int> p1Cards;
	deque<int> p2Cards;
	vector<int> pot;	

	// Deal the shuffled deck out to the players
	while(myDeck.getSize()!=0){
		p1Cards.push_back(myDeck.Deal());
		p2Cards.push_back(myDeck.Deal());
	}

	bool gameOver = false;

	while(gameOver == false){

		if(p1Cards.size()==0){ 
			gameOver = true;
			cout << "\nPLAYER TWO WINS\n" << endl;
			continue;
		}
		if(p2Cards.size()==0){
			gameOver = true;
			cout << "\nPLAYER ONE WINS\n" << endl;
			continue;
		}

		// Both players show a card (added to pot)
		cout << "Player 1: " << p1Cards.back() << endl;
		pot.push_back(p1Cards.back());
		cout << "Player 2: " << p2Cards.back() << endl;
		pot.push_back(p2Cards.back());

		// Check to see who's card is the biggest
		if(p1Cards.back() > p2Cards.back()){
			cout << "Player 1 won the battle." << endl;
			p1Cards = insertVec(pot,p1Cards);
			pot.clear();
			p1Cards.pop_back();
			p2Cards.pop_back();
			continue;
		}

		if(p1Cards.back() < p2Cards.back()){
			cout << "Player 2 won the battle." << endl;
			p2Cards = insertVec(pot,p2Cards);
			pot.clear();
			p1Cards.pop_back();
			p2Cards.pop_back();
			continue;
		}

		if(p1Cards.back() == p2Cards.back()){
			cout << "Tie. War!" << endl;
			cout << "Player 1: ? ?" << endl;
			cout << "Player 2: ? ?" << endl;
			cout << "Both players put two cards in the pot." << endl;
			
			pot.push_back(p1Cards.back());
			p1Cards.pop_back();
			if(p1Cards.size() == 0) continue;
			pot.push_back(p1Cards.back());
			p1Cards.pop_back();
			
			pot.push_back(p2Cards.back());
			p2Cards.pop_back();
			if(p2Cards.size() == 0) continue;
			pot.push_back(p2Cards.back());
			p2Cards.pop_back();
			continue;
		}

	}

return 0; 

}
