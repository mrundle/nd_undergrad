/*
Matthew Rundle

*/

#include "cdl_list.h"
#include <iostream>

using namespace std;

int main() {

cdl_list<int> myList;

// add elements
// 1 2 9 4 3 6
myList.insertFromBack(4);
myList.insertFromBack(3);
myList.insertFromFront(9);
myList.insertFromFront(2);
myList.insertFromBack(6);
myList.insertFromFront(1);
myList.print();

// delete front and back
// 2 9 4 3
myList.deleteFront();
myList.deleteBack();
myList.print();

// check iterator
// 2
cout << myList.currentValue() << endl;
myList.next();
// 9
cout << myList.currentValue() << endl;
myList.previous();
// 2
cout << myList.currentValue() << endl;
++myList;
myList++;
//4
cout << myList.currentValue() << endl;
--myList;
// 9
cout << myList.currentValue() << endl;

// empty list and check
if(myList.isEmpty() == 1){
	cout << "myList is empty" << endl;
}else{
	cout << "myList is not empty" << endl;
}
myList.deleteBack();
myList.deleteBack();
myList.deleteBack();
myList.deleteBack();
if(myList.isEmpty() == 1){
	cout << "myList is empty" << endl;
}else{
	cout << "myList is not empty" << endl;
}

return 0;

}





