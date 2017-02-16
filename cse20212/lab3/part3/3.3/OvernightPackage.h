/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
OvernightPackage Header
*/

#ifndef OVERNIGHTPACKAGE_H_
	#define OVERNIGHTPACKAGE_H_

#include "Package.h"
#include<string>
#include <iostream>
using namespace std;

class OvernightPackage : public Package {

	public:
		OvernightPackage(); // default constructor
		OvernightPackage(string,string,string,string,string,double,double,double); // non-default constructor
		double CalculateCost();
		void printLabel();

	private:
		double extraCostPerOunce;
		
};


#endif
