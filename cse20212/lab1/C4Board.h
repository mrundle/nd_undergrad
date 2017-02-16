/*
   Matt Rundle
   cse20212.01
   C4Board.h
   Header file for the C4Board class.
*/

// Preprocessing directive wrapper
#ifndef C4BOARD_H
#define C4BOARD_H

#include <iostream>
#include "C4Col.h"

using namespace std;

class C4Board {		// Connect 4 board

	public:

		C4Board();	// default constructor
		~C4Board();	// deconstructor
		void play(int);	// allows two players to play a game
		void display();	// display the current board in simple text

	private:

		int numCols;	// number of columns on board
		C4Col *board;	// pointer to constructed array of C4Col objects
		int playerMove(int);	// acquires and validates user move choice
		int checkWinner();   // checks to see if there is a winner to the game yet
		int boardSearch(char);   // searches the board for winners
		int computerMove();	 // picks a column for the computer player to play
		int checkAdjacent(int);	 // sees if another similar piece is around

};

#endif
