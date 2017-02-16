/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
Package Implementation
*/

#include "Package.h"
#include <iostream>
using namespace std;

// default constructor
Package::Package(){
	Name = "unspecified";
	Address = "unspecified";
	City = "unspecified";
	State = "unspecified";
	ZipCode = "unspecified";
	Weight = 0;
	CostPerOunce = 0;
}

// non-default constructor
Package::Package(string inName, string inAddress, string inCity, string inState, string inZipCode, double inWeight, double inCostPerOunce){

	Name=inName;
	Address=inAddress;
	City=inCity;
	State=inState;
	ZipCode=inZipCode;
	
	if(inWeight<0){
		cout << "Error: Entered a negative weight. Stored as 0 oz." << endl;
		Weight=0;
	}else{
		Weight=inWeight;
	}
	if(inCostPerOunce<0){
		cout << "Error: Entered a negative cost. Stored as 0 dollars." << endl;
		inCostPerOunce=0;
	}else{
		CostPerOunce=inCostPerOunce;
	}
}

//
double Package::CalculateCost(){

	return Weight*CostPerOunce;

}

void Package::Display(){
	cout << Name << endl;	
	cout << Address << endl;	
	cout << City << endl;	
	cout << State << endl;	
	cout << ZipCode << endl;	
	cout << Weight << endl;	
	cout << CostPerOunce << endl;	
	cout << CalculateCost() << endl;	
}
