/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
Driver
*/

#include<iostream>
#include"Package.h"
#include"TwoDayPackage.h"
#include"OvernightPackage.h"
using namespace std;

int main(){

Package A; // default package constructor
Package B("Matt Rundle","407 Fisher Hall","Notre Dame", "Indiana", "46556", 30,.50); // non-default package constructor

TwoDayPackage C; // default two day package constructor
TwoDayPackage D("Matt Rundle","407 Fisher Hall","Notre Dame", "Indiana", "46556", 30,.50, 10); // non-default two day package constructor

OvernightPackage E; // default overnight package constructor
OvernightPackage F("Matt Rundle","407 Fisher Hall","Notre Dame", "Indiana", "46556", 30,.50, .50);

// Print package information
cout << "Default Package" << endl;
A.Display();
cout << endl;

cout << "Non-default Package" << endl;
B.Display();
cout << endl;

cout << "Default TwoDayPackage" << endl;
C.Display();
cout << endl;

cout << "Non-default TwoDayPackage" << endl;
D.Display();
cout << endl;

cout << "Default OvernightPackage" << endl;
E.Display();
cout << endl;

cout << "Non-default OvernightPackage" << endl;
F.Display();
cout << endl;

return 0;
}
