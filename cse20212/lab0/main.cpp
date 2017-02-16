#include <iostream>
#include "mortgage.h"   // includes class defnition defined in mortgage.h

using namespace std;

int main(){
	Mortgage first(10000,5.0,500);   //uses non-default initialization
	Mortgage second;

	second.credit(10000);	// credit 10,000
	cout << "Current balance after crediting second mortgage 10K: " << second.getPrincipal() << endl;
	cout << "Amortization schedule for first mortgage: " << endl;
	first.amortize();

return 0;
}
