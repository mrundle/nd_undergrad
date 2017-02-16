/*
Matt Rundle
cse20212.01

Distances.h (header file for the "Distances" class)
*/

#ifndef DISTANCES_H
	#define DISTANCES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h> // atoi
using namespace std;

class Distances {

	public:

		Distances(char*);	// constructor
		void printLocations();	// displays locations present in input file from 1 to n
		void roadTrip();	// computes the distance to go from between these integer locations
							// that should be stored in an STL vector

	private:
 
		vector< vector<string> > distTable;	// distance table
		int tableSize;	// size of the table

};

#endif
