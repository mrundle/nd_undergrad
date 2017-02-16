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

		Puzzle(char*);
		void solve();
		void print();
		bool isComplete();
		int findPossible(int,int);

	private:

		vector< vector<int> > Board;
		vector< vector< vector<int> > > possibleValues;

};
