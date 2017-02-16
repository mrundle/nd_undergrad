/*
   Matt Rundle
   cse20212.01
   C4Board.cpp
   Implementation file for the C4Board class type; also contains the play() function
   that drives the game of Connect Four in the compiled program, either with two
   human players or with one human player against a simple human AI.
*/


#include <iostream>
#include <cstdio>
#include "C4Col.h"
#include "C4Board.h"

using namespace std;

/*
   Default constructor for class C4Board; creates an array of C4Col objects
*/
C4Board::C4Board(){
	numCols=7;
}

/*
   Deconstructor for class C4Board; releases the allocated array of C4Col objects
*/
C4Board::~C4Board(){
	//delete [] board;
}

/*
  Prints/displays the board
*/
ostream &operator<< (ostream & print, const C4Board & B){
	print << "Connect Four\n\n";
	for(int i=B.board[0].getMaxDiscs()-1;i>=0;i--){
		print << "|_";
		for(int j=0;j<B.numCols;j++){
			if(j<(B.numCols-1)) print << B.board[j].getDisc(i) << "_|_";
			if(j==(B.numCols-1)) print << B.board[j].getDisc(i) << "_|";
		}
		print << "\n";
	}
	print << "  0   1   2   3   4   5   6\n\n";  // Number the columns for user input reference
	return print;
}

/*
   Searches the board for winners; helper function for checkWinner(). This function consists of
   6 main searches, including one for a horizontal search, one for a vertical search, and four for
   the diagonal searching. Multiple functions were used in the diagonal searching because of
   convenience and to maintain implementation functionality for boards of differenct sizes.
*/
int C4Board::boardSearch(char c){
	int matches;

	// VERTICAL SEARCH
	for(int i=0;i<numCols;i++){
		matches=0;
		for(int j=0;j<board[0].getMaxDiscs();j++){
			if(board[i].getDisc(j)==c) matches++;
			if(board[i].getDisc(j)!=c) matches=0;
			if(matches==4) return 1;
		}
	}

	// HORIZONTAL SEARCH
	for(int i=0;i<board[0].getMaxDiscs();i++){
		matches=0;
		for(int j=0;j<numCols;j++){
			if(board[j].getDisc(i)==c) matches++;
			if(board[j].getDisc(i)!=c) matches=0;	
			if(matches==4) return 1;
		}
	}

	// DIAGONAL SEARCHES
	// Northwest->Southeast
	for(int i=3;i<board[0].getMaxDiscs();i++){
		matches=0;
		for(int j=0;j<(i+1);j++){
			if(board[j].getDisc(i-j)==c) matches++;
			if(board[j].getDisc(i-j)!=c) matches=0;
			if(matches==4) return 1;
		}
	}
	// Southeast->Northwest
	for(int i=0;i<3;i++){
		matches=0;
		for(int j=numCols-1;j>i;j--){
			if(board[j].getDisc((numCols-1)-j+i)==c) matches++;
			if(board[j].getDisc((numCols-1)-j+i)!=c) matches=0;
			if(matches==4) return 1;
		}
	}
	// Southwest->Northeast
	for(int i=0;i<3;i++){
		matches=0;
		for(int j=0;j<(numCols-1)-i;j++){
			if(board[j].getDisc(j+i)==c) matches++;
			if(board[j].getDisc(j+i)!=c) matches=0;
			if(matches==4) return 1;
		}
	}
	// Northeast->Southwest
	for(int i=3;i<board[0].getMaxDiscs();i++){
		matches=0;
		for(int j=(numCols-1);j>=(numCols-1)-i;j--){
			if(board[j].getDisc(j-((numCols-1)-i))==c) matches++;
			if(board[j].getDisc(j-((numCols-1)-i))!=c) matches=0;
			if(matches==4) return 1;
		}
	}

	// If it makes it through these checks, there is no winner
	return 0;
}

/*
   utilizes the boardSearch() function to check for winners of piece 'O' or 'X'. If winner is found, returns 1.
*/
int C4Board::checkWinner(){
	if(boardSearch('O')==1) return 1;
	if(boardSearch('X')==1) return 1;
}

/*
   Helper function for the computerMove() function, sees if another similar piece is around
	-finds the location of the next disc placed
	-j is the column, i is the row
	-checks 'O' character for matches because that is the computer's piece
	-if no adjacency found, return 0
*/
int C4Board::checkAdjacent(int i){
	int j=board[i].getNumDiscs();
	if(board[j].getDisc(i-1)=='O') return 1;	// South adjacency
	if(board[j-1].getDisc(i)=='O') return 1;	// West adjacency
	if(board[j-1].getDisc(i+1)=='O') return 1;	// Northwest adjacency
	if(board[j-1].getDisc(i-1)=='O') return 1;	// Southwest adjacency
	if(board[j+1].getDisc(i)=='O') return 1;	// East adjacency
	if(board[j+1].getDisc(i+1)=='O') return 1;	// Northeast adjacency
	if(board[j+1].getDisc(i-1)=='O') return 1;	// Southeast adjacency
	return 0;
}

/*
   Picks a column for the computer player to play; helper function of play(int).
	-First, loops through columns in ascending order and checks to see if it can find
	 an empty spot adjacent to one of its own pieces
	-If it can't find such position, it again loops through the columns in ascending
	 order and drops the piece into the first open space
	-If no move is possible for the computer, return 0 and end game
*/
int C4Board::computerMove(){
	int computerChoice;
	for(int computerChoice=0;computerChoice<numCols;computerChoice++){
		if(checkAdjacent(computerChoice)==1 && board[computerChoice].isFull()==0){
			board[computerChoice].addDisc('O');
			return 1;
		}
	}
	for(int computerChoice=0;computerChoice<numCols;computerChoice++){
		if(board[computerChoice].isFull()==0){
			board[computerChoice].addDisc('O');
			return 1;
		}
	}
	return 0;
}

/*
   Acquires and validates user move choice; helper function for play(int)
*/
int C4Board::playerMove(int player){
	int playerChoice;
	while(1){
		// ask user where the player wants to go
		cout << "Player " << player << ", which column would you like to drop your piece into?\n";
		cout << "To end the game, enter '-1'.\n";
		cin >> 	playerChoice;	

		// end the game if player chooses -1
		if(playerChoice==-1){
			cout << "Game ended by Player " << player << "." << endl;			
			return -1;
		}

		// handle bad input
		if(playerChoice<0 || playerChoice>(numCols-1)){
			cout << "Error: Column does not exist. Please choose again.\n";
			cin >> playerChoice;
			if(playerChoice==-1){
				cout << "Game ended by Player " << player << "." << endl;			
				return -1;
			}
			continue;
		}
		if(board[playerChoice].isFull()==1){
			cout << "Error: Invalid move, column is full. Choose another column.\n";
			cin >> playerChoice;
			continue;
		}

		// if valid move, place disc and return
		if(board[playerChoice].isFull()==0){
			//if(player==1) board[playerChoice].addDisc('X'); // OLD
			if(player==1) board[playerChoice]+=('X');
			//if(player==2) board[playerChoice].addDisc('O'); // OLD
			if(player==2) board[playerChoice]+=('O');
			return 1;
		}
	}
}

/*
   Play the game
   	-If computerPlayer==1, play against AI
*/
void C4Board::play(int computerPlayer){
	int gameOver=0;
	int turn=1;
	int player;
	int playerChoice;
	while(gameOver==0){
		//clear screen between each player's turn
		printf("\033[2J\033[H");

		// display board
		cout << *this;

		// Check for winner
		if(checkWinner()==1){
			cout << "Player " << player << " wins the game!" << endl;
			return;
		}

		// determine player
		turn++;
		player=(turn%2)+1;

		// Ask for input from player - if computer is player 2, skip this.
		// Add Disc in user selected column once move is validated 
		if(player==1 || (player==2 && computerPlayer!=1)){
			if(playerMove(player)==-1) return;
		}

		// if player 2 is the computer player, run AI to choose a move
		if(player==2 && computerPlayer==1){
			if(computerMove()==0) return;
		}
	}
}











