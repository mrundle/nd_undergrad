/*
Matt Rundle
cse20212.01
lab7

main.cpp (Driver function for the "Distances" class)
*/

#include "Distances.h"

int main(int argc, char* argv[]){

// Instantiate a "Distances" object with the first line argument
Distances myDistances(argv[1]);

// Print to user the possible travel locations
myDistances.printLocations();

// Collect user input on where they want to travel, calculate
// and display to them the distance traveled on their trip
myDistances.roadTrip();

return 0;
}
