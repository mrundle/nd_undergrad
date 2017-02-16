// Matt Rundle
// lab2, part 3
// calc.cpp

#include <iostream>
#include "Rational.h"

using namespace std;


// prepares them for addition and subtraction
void prep(int *first_numerator,int *first_denominator,int *second_numerator,int *second_denominator){
	int temp_first_denominator=*first_denominator;
	*first_numerator=(*first_numerator) * (*second_denominator);
	*first_denominator=( *first_denominator) * (*second_denominator);
	*second_numerator=(*second_numerator) * temp_first_denominator;
	*second_denominator=(*second_denominator) * temp_first_denominator;
}

// add the two numbers
Rational add(Rational first_number,Rational second_number){
	int first_numerator=first_number.getNumerator();
	int first_denominator=first_number.getDenominator();
	int second_numerator=second_number.getNumerator();
	int second_denominator=second_number.getDenominator();
	prep(&first_numerator,&first_denominator,&second_numerator,&second_denominator);

	int new_numerator, new_denominator;
	new_numerator=first_numerator+second_numerator;
	new_denominator=first_denominator;
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}

// subtract the second from the first
Rational subtract(Rational first_number,Rational second_number){
	int first_numerator=first_number.getNumerator();
	int first_denominator=first_number.getDenominator();
	int second_numerator=second_number.getNumerator();
	int second_denominator=second_number.getDenominator();
	prep(&first_numerator,&first_denominator,&second_numerator,&second_denominator);

	int new_numerator, new_denominator;
	new_numerator=first_numerator-second_numerator;
	new_denominator=first_denominator;
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}

// multiply the two numbers
Rational multiply(Rational first_number,Rational second_number){
	int new_numerator, new_denominator;
	new_numerator = first_number.getNumerator() * second_number.getNumerator();
	new_denominator = first_number.getDenominator() * second_number.getDenominator();
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}

// divide the first by the second
Rational divide(Rational first_number,Rational second_number){
	int new_numerator, new_denominator;
	new_numerator = first_number.getNumerator() * second_number.getDenominator();
	new_denominator = first_number.getDenominator() * second_number.getNumerator();
	Rational new_number(new_numerator,new_denominator);
	return new_number;
}

int main(){
//Rational fraction(3,0);
//cout << fraction;

int numerator_one, numerator_two, denominator_one, denominator_two;

cout << "Welcome to the rational number calculator." << endl;
cout << "After you enter two rational numbers, the calculator will perform a few calulations." << endl;

// Collect the first number
cout << "Please enter a NUMERATOR for the first number: ";
cin >> numerator_one;
cout << "Please enter a DENOMINATOR for the first number: ";
cin >> denominator_one;
Rational number_one(numerator_one,denominator_one);

// Collect the second number
cout << "Please enter a NUMERATOR For the second number: ";
cin >> numerator_two;
cout << "Please enter a DENOMINATOR for the second number: ";
cin >> denominator_two;
Rational number_two(numerator_two,denominator_two);

// Confirm numbers with user
cout << "You entered " << number_one << " for the first number and " << number_two << " for the second number.\n" << endl;

// Do some calculations and display them to the user
cout << "Addition:       " << number_one << " + " << number_two << " = " << number_one+number_two	<< endl;
cout << "Subtraction:    " << number_one << " - " << number_two << " = " << number_one-number_two	<< endl;
cout << "Multiplication: " << number_one << " * " << number_two << " = " << number_one*number_two	<< endl;
cout << "Division:       " << number_one << " / " << number_two << " = " << number_one/number_two	<< endl;
cout << "Rundlean:       " << number_one << " ? " << number_two << " = " << number_one%number_two	<< endl;

return 0;

}
