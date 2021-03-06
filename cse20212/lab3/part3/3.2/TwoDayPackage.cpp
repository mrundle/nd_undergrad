/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
TwoDayPackage Implementation
*/				

#include "Package.h"
#include "TwoDayPackage.h"
#include<string>
#include<iostream>
using namespace std;

TwoDayPackage::TwoDayPackage(){
	FlatFee = 0;
	Package P;
}

TwoDayPackage::TwoDayPackage(string inName, string inAddress, string inCity, string inState, string inZipCode, double inWeight, double inCostPerOunce, double inFlatFee){
	FlatFee=inFlatFee;
	P.setName(inName);
	P.setAddress(inAddress);
	P.setCity(inCity);
	P.setState(inState);
	P.setZipCode(inZipCode);
	P.setWeight(inWeight);
	P.setCostPerOunce(inCostPerOunce);
}

double TwoDayPackage::CalculateCost(){
	return (P.CalculateCost()+FlatFee);
}

// Display the data members of a package class
void TwoDayPackage::Display(){
	P.Display();
	cout << FlatFee << endl;	
}

