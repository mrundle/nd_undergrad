/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
TwoDayPackage Implementation
*/				

#include "Package.h"
#include "TwoDayPackage.h"
#include<string>
using namespace std;

TwoDayPackage::TwoDayPackage() : FlatFee(0), Package() {
	FlatFee = 0;
}

TwoDayPackage::TwoDayPackage(string inName, string inAddress, string inCity, string inState, string inZipCode, double inWeight, double inCostPerOunce, double inFlatFee) : FlatFee(inFlatFee), Package(inName,inAddress,inCity,inState,inZipCode,inWeight,inCostPerOunce){
	FlatFee=inFlatFee;
}

double TwoDayPackage::CalculateCost(){
	return (Package::CalculateCost()+FlatFee);
}

void TwoDayPackage::printLabel(){
 	cout << Name << endl;	
	cout << Address << endl;	
	cout << City << endl;	
	cout << State << endl;	
	cout << ZipCode << endl;
}

