/*
Matt Rundle
Matt Mahan
lab3
BankAccount.h

This is the header file for the BankAccount class
*/

#ifndef BANKACCOUNT_H_
#define BANKACCOUNT_H_

#include <string>
using namespace std;

class BankAccount {

	public:
		BankAccount();	// default constructor

	private:
		double Principal;
		double Rate;
		int accountNumber;
		string firstName;
		string lastName;
};

#endif
