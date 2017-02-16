
#include "CardDeck.h"
#include "Hand.h"
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;


void printHeader() {
	printf("\033[2J\033[H");
	cout << "################################" << endl;
	cout << "#          BLACKJACK           #" << endl;
	cout << "#        by Matt Rundle        #" << endl;
	cout << "################################\n" << endl;
	return;
}

int main(){
	CardDeck myDeck;

	myDeck.shuffle();

	char userInput;
	Hand Dealer;
	Hand User;

	int dealerWins = 0;
	int userWins = 0;

	bool gameOver = false;
	bool roundOver = false;
	bool userHit;

	while(gameOver == false){

		userHit = true;

		roundOver = false;

		// Initial draw, two cards each
		for(int i=0;i<2;i++){
			Dealer.addCard(myDeck.Deal());
			User.addCard(myDeck.Deal());
		}

		while(roundOver == false){
			userInput = 'z'; // sets to junk value, ensuring proper response

			printHeader();

			if(userHit == true){
				// Displays dealer cards; show first and 'hide' second
				cout << "Dealer Cards: ";
				cout << Dealer.returnFirst() << " ?";
				cout << "\n" << endl;
			}
			if(userHit == false){
				cout << "Dealer Cards: ";
				Dealer.printCards();
				cout << "(" << Dealer.sumCards() << ")\n" << endl;
			}
	
			// Displays user cards
			cout << "Your Cards: ";
			User.printCards();
			cout << "(" << User.sumCards() << ")" << endl;
			cout << "\n";

			// See if game is over
			if(User.sumCards() == 21){
				cout << "You win!\n" << endl;
				userWins++;
				roundOver = true;
				break;
			}
			if(User.sumCards() > 21){
				cout << "Bust. Dealer wins.\n" << endl;
				dealerWins++;
				roundOver = true;
				break;
			}
			if(Dealer.sumCards() > 21){
				cout << "You win!\n" << endl;
				userWins++;
				roundOver = true;
				break;
			}
			if(userHit == false){
				if(User.sumCards() > Dealer.sumCards()){
					cout << "You win!\n" << endl;
					userWins++;
				}
				if(User.sumCards() < Dealer.sumCards()){
					cout << "Dealer wins.\n" << endl;
					dealerWins++;
				}
				if(User.sumCards() == Dealer.sumCards()){
					dealerWins++;
					cout << "Dealer wins.\n" << endl;
				}
				roundOver = true;
				break;
			}

			// Collect user input
			cout << "Enter 'h' for hit or 's' for stand: ";
			cin >> userInput;
			if(userInput == 'h'){
				User.addCard(myDeck.Deal());
			}
			if(userInput == 's'){
				userHit = false;
				while(Dealer.sumCards() < 17){
					Dealer.addCard(myDeck.Deal());
				}
			}

		}

		cout << "User wins: " << userWins << endl;
		cout << "Dealer wins: " << dealerWins << "\n" << endl;
		cout << "Continue? [y/n]: ";
		userInput = 'z';
		while((userInput != 'y') && (userInput != 'n')){
			cin >> userInput;
		}
		if(userInput == 'n') gameOver = true;
		if(userInput == 'y'){
			User.clearHand();
			Dealer.clearHand();
		}
	}

return 0; // end program without errors

}
		
