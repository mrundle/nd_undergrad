/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
Package Header
*/

#ifndef PACKAGE_H_
	#define PACKAGE_H_

#include <string>
using namespace std;

class Package {

	public:

		Package(); // default constructor
		Package(string,string,string,string,string,double,double); // non-default constructor
		double CalculateCost(); // Calculates the cost of shipping
		virtual void printLabel() = 0; // prints all data members and the cost

	protected:

		string Name;
		string Address;
		string City;
		string State;
		string ZipCode;
		double Weight;	// weight of package (ounces)
		double CostPerOunce; // cost per ounce
};

#endif
