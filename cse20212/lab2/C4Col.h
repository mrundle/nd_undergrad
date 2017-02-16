/*
   Matt Rundle
   cse20212.01
   C4Col.h
   Header file for the C4Col class.
*/

// Preprocessing directive wrapper
#ifndef C4COL_H
#define C4COL_H

#include <iostream>

using namespace std;

class C4Col {   // column of a connect4 board

 public:

  C4Col();  // default constructor
  int isFull();        // returns 1 if column full, 0 otherwise
  void addDisc(char);  // adds a character disc to column: 'X' or 'O' depending on player
  char getDisc(int) const;   // returns this element from a column
  int getMaxDiscs() const;   // get function for maxDiscs data member
  int getNumDiscs() const;   // used for the AI, helper function for the computer choice
  C4Col operator+=(char); // calls the addDisc function

 private:
  
  int numDiscs;    // current number of discs, starts at 0
  int maxDiscs;    // maximum number of discs, 6 for normal game
  char Discs[10];  // static (aka fixed size) array to store disc chars

};

#endif
