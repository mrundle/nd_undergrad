/*
Matt Rundle
Matt Mahan
CSE20212 Lab 3
Driver
*/

#include<iostream>
#include<vector>
#include <stdio.h>
#include"Package.h"
#include"TwoDayPackage.h"
#include"OvernightPackage.h"
using namespace std;

int main(){

TwoDayPackage A("Aedon Cannon","3818 Tony Danza Blvd","South Park", "Colorado", "46556", 50,.33, 15);
TwoDayPackage* a = &A;
TwoDayPackage B("Daniel Gregory","845 Houdini Street  ","Quahog", "Rhode Island", "46556", 30,.50, 10);
TwoDayPackage* b = &B;
TwoDayPackage C("Matthew Murphy","24769 Rusty Trombone Rd","Billingham","South Dakota","651099", 28, .73, 8);
TwoDayPackage* c = &C;

OvernightPackage D("Billy Stengle","439 Abe Lincoln Way","Dingleberry","Michigan","46532", 34, .44, .07);
OvernightPackage* d = &D;
OvernightPackage E("Connor Schmidt","385 Hot Carl Avenue","Grundleton","Alabama","85467", 45, .54, .11);
OvernightPackage* e = &E;

vector<Package*> Packages;
Packages.push_back(a);
Packages.push_back(b);
Packages.push_back(c);
Packages.push_back(d);
Packages.push_back(e);

double total_cost;
vector<Package*>::const_iterator i;
for(i = Packages.begin(); i != Packages.end(); i++){
	(*i)->printLabel();
	cout << "\n";
	total_cost+=(*i)->CalculateCost();
}

printf("Total cost to send these packages is $ %.2lf \n",total_cost);

return 0;

}
