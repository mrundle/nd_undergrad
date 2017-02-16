/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
OvernightPackage Implementation
*/				

#include "Package.h"
#include "OvernightPackage.h"
#include<string>
using namespace std;

OvernightPackage::OvernightPackage() : extraCostPerOunce(0),Package() {
	extraCostPerOunce = 0;
}

OvernightPackage::OvernightPackage(string inName, string inAddress, string inCity, string inState, string inZipCode, double inWeight, double inCostPerOunce, double inextraCostPerOunce) : extraCostPerOunce(inextraCostPerOunce), Package(inName,inAddress,inCity,inState,inZipCode,inWeight,inCostPerOunce){
	extraCostPerOunce=extraCostPerOunce;
}

// Is making weight protected instead of private allowed?
double OvernightPackage::CalculateCost(){
	return (Package::CalculateCost()+extraCostPerOunce*Weight);
}

