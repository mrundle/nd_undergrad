/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
Package Implementation
*/

#include "Package.h"
#include <iostream>
#include <string>
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

// Calculate the cost of the package
double Package::CalculateCost(){

	return Weight*CostPerOunce;

}

// Display the data members of a package class
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

// Get Functions
string Package::getName(){
	return Name;
}
string Package::getAddress(){
	return Address;
}
string Package::getCity(){
	return City;
}
string Package::getState(){
	return State;
}
string Package::getZipCode(){
	return ZipCode;
}
double Package::getWeight(){
	return Weight;
}
double Package::getCostPerOunce(){
	return CostPerOunce;
}

// Set Functions
void Package::setName(string inName){
	Name=inName;
}
void Package::setAddress(string inAddress){
	Address=inAddress;
}
void Package::setCity(string inCity){
	City=inCity;
}
void Package::setState(string inState){
	State=inState;
}
void Package::setZipCode(string inZipCode){
	ZipCode=inZipCode;
}
void Package::setWeight(double inWeight){
	Weight=inWeight;
}
void Package::setCostPerOunce(double inCostPerOunce){
	CostPerOunce=inCostPerOunce;
}
