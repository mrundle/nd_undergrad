/* mortgage.c
   Created by Matthew Rundle
   for cse20211.01, 2012
   This program asks the user to input the principal,
   interest rate, and desired monthly payment, and
   then displays an amortization table. At the end,
   the program displays how long it took to pay off
   the mortgage in years and months, as well as the 
   total amount of payments over that time. */

#include <stdio.h>
int main()

{

double p;   // principal
double ir;  // interest rate
double mp;  // monthly payment
int cont=0;  // tool for controlling user inputs

printf("This program will generate an amoritzation table\n");      //Explain to user
printf("as well as display how long it will take to pay off\n");
printf("the mortgage, as well as the total amount in payment\n");
printf("over that time.\n");
printf("Principal: $ ");      //ask for principal
while (cont==0){              //make sure value is good
  scanf("%lf",&p);
  if (p<0){
    printf("Please enter a positive principal: $ ");
  } else {
    cont=1;
  }
}
printf("Interest Rate (%%): ");   //ask for interest rate
cont=0;
while (cont==0){                 //make sure value is good
 scanf("%lf",&ir); 
 if (ir<0){
    printf("Please enter the rate as a positive percentage (%%): ");
  } else {
    cont=1;
  }
}
printf("Desired monthly payment: $ ");  //ask for monthly payment
cont=0;
while (cont==0){                        //make sure this value is good
  scanf("%lf",&mp);
  if (mp<0){
    printf("Please enter a positive monthly payment: $ ");
  } else {
    cont=1;
  }
}

printf("   Month    Payment       Interest          Balance");  //label columns
double bal=p;         // balance, which is initially = to the premium
int m=0;            // month
double intrst;      // interest
double tot=0;      // this variable will track total payments
while (bal>0){
  m=m+1;                     // increment month
  intrst=bal*((.01*ir)/(double)12);  // calculate interest
  if (mp>(bal+intrst)){      // ensure no negative balance
    mp=bal+intrst;           
  }
  tot=tot+mp;                // keep track of total amount paid
  bal=bal+intrst-mp;         // calculate new balance
  if (intrst>mp){            // prevent inf loop if mortgage will never be paid
    printf("\n\nThe starting interest is greater than your monthly payment,\n");
    printf("the mortgage will never be paid off.\n\n");
    return 0;
  }
  printf("\n%5d        $%5.02lf       $%5.02lf       $%8.02lf",m,mp,intrst,bal);  //fill columns with data        
  }
int years=m/12;      // declare variable for years and compute
int months=m%12;     // declare variable for months and compute using the modulus operator
printf("\n\nYou paid a total of $%.02f over %d years and %d months.\n",tot,years,months); // tell user whats up

return 0; //end program after telling user what is up
} 
