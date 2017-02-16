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
		void Display(); // prints all data members and the cost
		
		// Get functions
		string getName();
		string getAddress();
		string getCity();
		string getState();
		string getZipCode();
		double getWeight();
		double getCostPerOunce();
		
		// Set functions
		void setName(string);
		void setAddress(string);
		void setCity(string);
		void setState(string);
		void setZipCode(string);
		void setWeight(double);
		void setCostPerOunce(double);

	private:

		string Name;
		string Address;
		string City;
		string State;
		string ZipCode;
	protected:
		double Weight;	// weight of package (ounces)
		double CostPerOunce; // cost per ounce
};

#endif
