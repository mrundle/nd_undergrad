/*
   Matt Rundle
   cse20212.01
   main.cpp
   Play Connect 4!
*/

#include "C4Board.h"  // class definition for C4Board used below
#include <cstdio>

int main(){
	int gameOver=0;
	int userInput;
	while(gameOver==0){
		int computerPlayer=0;
		// Greet user, ask whether they want to play by themselves or with a friend
		while(computerPlayer!=1 && computerPlayer!=2){
			printf("\033[2J\033[H");
			cout << "Welcome to Connect Four!" << endl;
			cout << "To play against the computer, press 1." << endl;
			cout << "To play against a friend, press 2." << endl;
			cin >> computerPlayer;
		}
		// instantiate an instance of a C4Board object
		C4Board c4;
		// play game :D
		c4.play(computerPlayer);
		// after game is over, ask user if they want to play again
		cout << "Would you like to play again? Enter '1' for yes, and '-1' to quit: ";
		cin >> userInput;
		// handle bad input
		while(userInput!=1 && userInput!=-1){
			cout << "Huh? Try that again: ";
			cin >> userInput;
		}
		// say goodbye to user if they're done
		if(userInput==-1){
			cout << "Goodbye!\n";		
			return 0;  // program terminated by user, finished without errors
		}
	}
}
