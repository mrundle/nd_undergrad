#include <iostream>
#include <iomanip>

using namespace std;

class Mortgage{
	public:
		Mortgage();			// default constructor, no arguments
		Mortgage(double setPrincipal,double setRate,double setPayment); // Non-default constructor
		void credit(double value);		// deducts value from the principal remaining
		double getPrincipal();		// returns the current principal remaining
		void amortize();		//calculates and displays amortization table
		
	private:
		double Principal;
		double Rate;
		double Payment;
};

