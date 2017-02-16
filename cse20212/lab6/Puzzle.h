/*
Puzzle.h
*/
#define PUZZLE_SIZE 9

#include <iostream>
#include <iomanip>
#include <cstdlib> // exit function
#include <fstream>
#include <vector>
using namespace std;

class Puzzle {

	public:

		Puzzle();
		Puzzle(char*);
		int solve();
		void print();

	private:

		vector< vector<int> > Board;
		vector< vector< vector<int> > > possibleValues;
		bool isComplete();
		bool isPossible(int,int,int);
		void findGuess(int&,int&);
		int badGuess();

};
