// Matt Rundle
// lab2, part 3
// rational.h

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
using namespace std;

class Rational{

friend ostream &operator<< (ostream &, const Rational &);

public:
	Rational(); // default constructor
	Rational(int,int); // non-default constructor
	int getNumerator() const;
	int getDenominator() const;
	Rational operator+(const Rational &); // rational addition
	Rational operator-(const Rational &); // rational subtraction
	Rational operator*(const Rational &); // rational multiplication
	Rational operator/(const Rational &); // rational division
	Rational operator%(const Rational &); // rational Rundlean combinatory operator

private:
	int Numerator;
	int Denominator;
	void reducedForm(); // stores rational numbers in reduced form
	void prepare(int*,int*,int*,int*);

};

#endif
