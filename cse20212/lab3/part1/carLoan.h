/*
Matt Rundle
Matt Mahan
lab3
carLoan.h

This is the header file for the carLoan class, which inherits the BankAccount class
*/

#ifndef CARLOAN_H_
#define CARLOAN_H_

#include "BankAccount.h"
#include <string>
using namespace std;

class carLoan : public BankAccount {

	public:
		
		carLoan();	// default constructor

	private:

		string carModel;
		int Payment;

};

#endif
