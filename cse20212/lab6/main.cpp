/*
main.cpp
*/

#include "Puzzle.h"

int main(int argc, char* argv[]){

Puzzle myPuzzle(argv[1]);

// Print insolved problem
cout << "Unsolved:\n" << endl;
myPuzzle.print();

// Solve and print
myPuzzle.solve();

return 0;
}
