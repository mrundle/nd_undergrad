#include <iostream>
#include "mortgage.h"   // includes class defnition defined in mortgage.h
#include <stdio.h>  // need this for amortization function

using namespace std;

// Default mortgage constructor
Mortgage::Mortgage(){
	Principal=100000;
	Rate=5;
	Payment=500;
} 

// Non-default mortgage constructor
Mortgage::Mortgage(double setPrincipal,double setRate,double setPayment){
	//do some error checking things
	Principal=setPrincipal;
	Rate=setRate;
	Payment=setPayment;
}

void Mortgage::credit(double value){
	Principal-=value;
}

double Mortgage::getPrincipal(){
	cout << "Current principal remaining is " << Principal << "." << endl;
}

void Mortgage::amortize(){
	cout << "   Month    Payment       Interest          Balance" << endl;
	double bal=Principal;         // balance, which is initially = to the premium
	int m=0;            // month
	double intrst;      // interest
	double tot=0;      // this variable will track total payments
	while (bal>0){
		m=m+1;                     // increment month
		intrst=bal*((.01*Rate)/(double)12);  // calculate interest
		if (Payment>(bal+intrst)){      // ensure no negative balance
		        Payment=bal+intrst;           
		}
		tot=tot+Payment;                // keep track of total amount paid
		bal=bal+intrst-Payment;         // calculate new balance
		if (intrst>Payment){            // prevent inf loop if mortgage will never be paid
			printf("\n\nThe starting interest is greater than your monthly payment,\n");
			printf("the mortgage will never be paid off.\n\n");
			break;
		  }
		printf("\n%5d        $%5.02lf       $%5.02lf       $%8.02lf",m,Payment,intrst,bal);  //fill columns with data        
	}
	int years=m/12;      // declare variable for years and compute
	int months=m%12;     // declare variable for months and compute using the modulus operator
	printf("\n\nYou paid a total of $%.02f over %d years and %d months.\n",tot,years,months); // tell user whats up
}
