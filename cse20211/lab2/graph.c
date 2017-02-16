/* graph.c
   Created by Matthew Rundle
   for cse20211.01, Sept. 2012
   This program generates a simple ASCII
   art graph of a mathematical function,
   x^3+x^2-x+2, and then notifies the user
   of the maximum and minimum values of 
   that function. */

#include <stdio.h>              // starting teh engines
#include <math.h>               // and teh maths
int main()

{

/* Declaring variables */
float x;  			 //declaring "x" variable
float y;  			 //declaring "y" variable
int stars; 			 //declaring variable to keep track of hashtag symbols
int counter; 			 //declaring a variable to use as a counter in the for loop later
float maxy=0;                    //initiailze maximum with low value
float miny=10000;                //initialize minimum with very high value
float minx;			 //declare variable to store x value of min
float maxx;			 //declare variable to store x value of max

/* Letting user know what's going on */
printf("\nPlot of x^3 + x^2 - x + 2 on domain -2<=x<=2.\n");    //declaring function
printf("    x     y\n");                                        //labeling "x" and "y" columns

/* Calculate range based on domain, list values, and graph */
for(x=-2;x<2;x=x+.01){           //domain is 2
  y=pow(x,3)+pow(x,2)-x+2;       //calculate y
  if (y>maxy){                   //each loop, compare y value to max
    maxy=y;                      //if new max, update maxy               
    maxx=x;                      //and update maxx
  }
  if (y<miny){                   //likewise, compare y value to min
    miny=y;                      //if new min, update miny
    minx=x;		         //and update minx
  }
  printf("%5.2f %5.2f ",x,y);    //Update columns of x and y with new values
  stars=ceil(y*10);              //This uses y value to generate the number of #'s needed
                                 //by multiplying by 10 and then rounding up to nearest integer.
  for (counter=stars;counter>=0;counter--){     //Print out however many # 
    printf("#");
  }
  printf("\n");   //new line
}
printf("\nThe maximum of %4.2f was at x=%3.2f.",maxy,maxx);     //Display max to user
printf("\nThe minimum of %3.2f was at x=%3.2f.\n",miny,minx);   //Display min to user

return 0;         //end program

}



