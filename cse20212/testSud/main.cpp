/*
main.cpp
*/

#include "Puzzle.h"

int main(int argc, char* argv[]){

Puzzle myPuzzle(argv[1]);

cout << "Unsolved:" << endl;
// Print insolved problem
myPuzzle.print();

myPuzzle.solve();
myPuzzle.print();

return 0;
}
