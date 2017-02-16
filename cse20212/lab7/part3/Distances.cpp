/*
Matt Rundle
cse20212.01

Distances.cpp (implementation file for the "Distances" class)
*/

#include "Distances.h"

// Constructor
Distances::Distances(char* filename){

	// Initialize table size to zero
	tableSize = 0;

	// Initialize the ifstream and establish temporary line string
	ifstream inputFile;
    string tempLine;

	// Open file and check for errors
	inputFile.open(filename);
		if(!inputFile){
        	std::cerr << "Error loading file." << std::endl;
            exit(1);
		}

	// Go through each line of the file
	while(getline(inputFile, tempLine)){

		// Initialize temporary vector to hold line elements
		vector<string> tempVec;

		// Initialize stringstream, initialize temporary string vector to handle individual elements
		stringstream ss(tempLine);
		string tempString;

		// In each line, grab each (tab delineated) element and add it to temp vector
		while(getline(ss,tempString, '\t')){
			tempVec.push_back(tempString);
		}

		// Add the temporary vector into the object's 2D "distTable" vector 
		distTable.push_back(tempVec);

		// Increment table size after each line	
		tableSize++;
	}

}


// Print locations available for travel
void Distances::printLocations(){
	cout << "Locations:" << endl;
	for(int i=1;i<tableSize;i++){
		cout << i << ": " << distTable[0][i] << endl;
	}
}

void Distances::roadTrip(){

	// Address user, prompt for input
	cout << "\nTo calculate total travel distance, enter the number of each" << endl;
	cout << "destination sequentially, each separated by a space: ";

	// Collect list of locations from user, stick into a vector
	vector<int> intVec;
	string line;
	getline(cin, line);
	istringstream os(line);
	int i;
	while(os >> i)
		intVec.push_back(i);

	// Calculate and print to screen a list of distances between users locations
	string origin,destination;
	int distance;
	int total_distance = 0;
	cout << "\n========[TRIP REPORT]==============" << endl;
	for(int j=0;j<intVec.size()-1;j++){
		origin = distTable[0][intVec[j]];
		destination = distTable[0][intVec[j+1]];
		distance = atoi((distTable[intVec[j]][intVec[j+1]]).c_str());

		cout << origin << " -> " << destination << " = " << distance << " miles" << endl;

		total_distance += distance;
	}

	// Print total distance travelled on trip
	cout << "-----------------------------------";
	cout << "\nTotal travel distance: " << total_distance << " miles" << endl;
	cout << "===================================" << endl;

}


