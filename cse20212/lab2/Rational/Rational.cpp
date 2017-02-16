// Matt Rundle
// lab2, part 3
// rational.cpp

#include <iostream>
#include <cmath>
#include "Rational.h"
using namespace std;

// default constructor
Rational::Rational(){
	Numerator=1;
	Denominator=1;
}

// non-default constructor
Rational::Rational(int n, int d){
	Numerator=n;	
	if(d==0){
		Denominator=1;
		cout << "Error: Denominator cannot be zero." << endl;
		cout << "Rational stored as " << Numerator << "/" << Denominator << endl;
	}else{
		Denominator=d;
	}
	
	// put it in reduced form
	reducedForm();
}

ostream &operator<< (ostream & print, const Rational & R){
	print << R.Numerator << "/" << R.Denominator;
	return print;
}

int Rational::getNumerator() const{
	return Numerator;
}

int Rational::getDenominator() const{
	return Denominator;
}

// puts the rational number in reduced form
// (private helper function, used in both the non-default constructor)
void Rational::reducedForm(){
	// find the smallest term
	int smallest_term;
		if(fabs(Numerator)>fabs(Denominator)) smallest_term=fabs(Denominator);
		if(fabs(Numerator)<fabs(Denominator)) smallest_term=fabs(Numerator);
		if(fabs(Numerator)==fabs(Denominator)){
			if(Numerator==Denominator){
				Numerator=Denominator=1;
				return;
			}
			Numerator=-1;
			Denominator=1;
			return;
		}

	// if numerator is 0, put denominator to 0 as well
	if(Numerator==0){
		Denominator=0;
		return;
	}

	// find the GCD
	int gcd;
	for(int i=1;i<=smallest_term;i++){
		if((Numerator%i)==0 && (Denominator%i)==0){
			gcd=i;
		}
	}
	Numerator=Numerator/gcd;
	Denominator=Denominator/gcd;

	// if the negative is in the denominator, move it to the numerator
	if(Denominator<0 && Numerator>0){
		Numerator=Numerator*(-1);
		Denominator=Denominator*(-1);
	}
}

void Rational::prepare(int *first_numerator,int *first_denominator,int *second_numerator,int *second_denominator){
	int temp_first_denominator=*first_denominator;
	*first_numerator=(*first_numerator) * (*second_denominator);
	*first_denominator=( *first_denominator) * (*second_denominator);
	*second_numerator=(*second_numerator) * temp_first_denominator;
	*second_denominator=(*second_denominator) * temp_first_denominator;
}

Rational Rational::operator+(const Rational & rational){
	int first_numerator=(*this).getNumerator();
	int first_denominator=(*this).getDenominator();
	int second_numerator=rational.getNumerator();
	int second_denominator=rational.getDenominator();

	prepare(&first_numerator,&first_denominator,&second_numerator,&second_denominator);

	int new_numerator, new_denominator;
	new_numerator=first_numerator+second_numerator;
	new_denominator=first_denominator;
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}

Rational Rational::operator-(const Rational & rational){
	int first_numerator=(*this).getNumerator();
	int first_denominator=(*this).getDenominator();
	int second_numerator=rational.getNumerator();
	int second_denominator=rational.getDenominator();
	
	prepare(&first_numerator,&first_denominator,&second_numerator,&second_denominator);

	int new_numerator, new_denominator;
	new_numerator=first_numerator-second_numerator;
	new_denominator=first_denominator;
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}

Rational Rational::operator*(const Rational & rational){
	int new_numerator, new_denominator;
	new_numerator = (*this).getNumerator() * rational.getNumerator();
	new_denominator = (*this).getDenominator() * rational.getDenominator();
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}

Rational Rational::operator/(const Rational & rational){
	int new_numerator, new_denominator;
	new_numerator = (*this).getNumerator() * rational.getDenominator();
	new_denominator = (*this).getDenominator() * rational.getNumerator();
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}

Rational Rational::operator%(const Rational & rational){
	int first_numerator=(*this).getNumerator();
	int first_denominator=(*this).getDenominator();
	int second_numerator=rational.getNumerator();
	int second_denominator=rational.getDenominator();

	int new_numerator, new_denominator;
	new_numerator=first_numerator+second_denominator;
	new_denominator=first_denominator+second_denominator;
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}
