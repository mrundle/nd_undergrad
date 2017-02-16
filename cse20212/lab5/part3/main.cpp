/*
Matthew Rundle

*/

#include "cdl_list.h"
#include <iostream>

using namespace std;

int main() {

cdl_list<int> myLine;

int n;

cout << "How many 'n' suitors are in Buttercup's line?\nn = ";
cin >> n;
cout << "\n";

// Populate line
for(int i=1;i<=n;i++){
	myLine.insertFromBack(i);
}

myLine.reset();
while(myLine.getSize() > 1){
	myLine.print();
	

	// Increment the current position twice
	++myLine;
	++myLine;

	myLine.removeNode();
}
myLine.print();

cout << "\nWesely should stand in position " << myLine.currentValue() << ".\n" << endl;

return 0;
}





