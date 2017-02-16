/*
Matt Rundle
cse20212.01
lab4, Part 1

This program collects a series of integers from the user and determines whether or not they form a palindrome.
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main(){

vector<int> intVec;
int input;

cout << "This program will check to see if a sequence of numbers is a palindrome." << endl;

// Take input from user
string line;
getline(cin, line);
istringstream os(line);
int i;
while(os >> i)
	intVec.push_back(i);

// Reverse the given vector
vector<int> intVecRev = intVec;
reverse(intVecRev.begin(), intVecRev.end());

// Compare the normal and reversed vectors to see if matching
if( intVec == intVecRev ){
	cout << "This sequence IS a palindrome." << endl;
}else{
	cout << "This sequence IS NOT a palindrome." << endl;
}

return 0;
}
