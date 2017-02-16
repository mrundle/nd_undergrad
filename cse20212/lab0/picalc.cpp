// Matt Rundle
// Lab 0, Problem 1
// Estimating Pi


#include <iostream>
#include <iomanip>
using namespace std;

int main(){

int terms; // number of terms to calculate
double c; // loop counter
int neg=-1; // keeps track of alternating negative
double pi=0; // initialize pi at 4 for the calculating sequence

cout << "\nThis program calculates the value of pi from an infinite series equation.\n";

int checkTerms=0;
while(checkTerms==0){
	cout << "Please enter thenumber of terms in the series: ";
	cin >>  terms;
	if(terms >= 2) break;	// validate number of terms 
}

cout << "\n";

for(c=0;c<=terms;c++){
	// Calculate pi
	if(c==0){
		pi+=4;
	}
	if(c>0){
		pi+=((neg)*(4/(c*2+1)));
		neg*=(-1);
	}
	// Print the result
	cout << "Estimate after " << c+1 << " term(s): " << std::setprecision(4)<< pi << endl;
}

return 0;
}
