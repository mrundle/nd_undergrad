/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
OvernightPackage Implementation
*/				

#include "Package.h"
#include "OvernightPackage.h"
#include<string>
#include<iostream>
using namespace std;

OvernightPackage::OvernightPackage(){
	extraCostPerOunce = 0;
	Package P;
}

OvernightPackage::OvernightPackage(string inName, string inAddress, string inCity, string inState, string inZipCode, double inWeight, double inCostPerOunce, double inextraCostPerOunce){
	extraCostPerOunce=inextraCostPerOunce;
	P.setName(inName);
	P.setAddress(inAddress);
	P.setCity(inCity);
	P.setState(inState);
	P.setZipCode(inZipCode);
	P.setWeight(inWeight);
	P.setCostPerOunce(inCostPerOunce);
}

// Is making weight protected instead of private allowed?
double OvernightPackage::CalculateCost(){
	return (P.CalculateCost()+extraCostPerOunce*P.getWeight());
}

// Display the data members of a package class
void OvernightPackage::Display(){
	P.Display();
	cout << extraCostPerOunce << endl;	
}

