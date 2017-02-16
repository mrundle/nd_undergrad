/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
TwoDayPackage Header
*/

#ifndef TWODAYPACKAGE_H_
	#define TWODAYPACKAGE_H_

#include "Package.h"
#include<string>
using namespace std;

class TwoDayPackage{

	public:
		TwoDayPackage(); // default constructor
		TwoDayPackage(string,string,string,string,string,double,double, double); // non-default constructor
		double CalculateCost();
		void Display();
		
	private:
		double FlatFee;
		Package P;
};


#endif
