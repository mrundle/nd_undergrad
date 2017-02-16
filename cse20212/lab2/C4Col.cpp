/*
   Matt Rundle
   cse20212.01
   C4Col.cpp
   Implementation file for the C4Col class.
*/

#include <iostream>
#include "C4Col.h"

using namespace std;

/*
   Default constructor for class C4Col
*/
C4Col::C4Col(){
	numDiscs=0;
	maxDiscs=6;
	for(int i=0;i<maxDiscs;i++){
		Discs[i]=' ';
	}
}

/*
   Returns 1 if column full, 0 otherwise
*/
int C4Col::isFull(){
	if(Discs[maxDiscs-1]=='X' || Discs[maxDiscs-1]=='O') return 1;
	return 0;
}

/*
   Returns this element from a column
*/
char C4Col::getDisc(int value) const{
	return Discs[value];
}

/*
   Get function for maxDiscs data member
*/
int C4Col::getMaxDiscs() const{
	return maxDiscs;
}

/*
   Adds a character disc to column: 'X' or 'O' depending on player
*/
void C4Col::addDisc(char newDisc){
	Discs[numDiscs++]=newDisc;
}

/*
   Used for the AI, helper function for the computer choice
*/
int C4Col::getNumDiscs() const{
	return numDiscs;
}

/*

*/
C4Col C4Col::operator+=(char c){
	addDisc(c);
	return(*this);
}
