/* table.c
   Created by Matthew Rundle
   This program displays an integer
   multiplication table based on a grid
   sized X by Y, per input of the user. */

#include <stdio.h>
int main(void)

{

int sizex;  // Declare variable to store size of x column
int sizey;  // Declare variable to store size of y column

/* Explain program to user, ask for input */
printf("This program displays an integer multiplication table.\n");  //Explain stuff to user
printf("Enter two integers to represent the size \n");                
printf("of the desired graph (for example, 5 5):\n");
scanf("%d %d",&sizex,&sizey);                                        //Collect size of x and y columns from user

/* Declare variables, initialize for loop */ 
int x;     // Declare variable for "x" value
int y;     // Declare variable for "y" value
int tr;    // Top row 

/* Display top row */
for (tr=0;tr<(sizex+1);tr++){    //This for loop displays top row based on size of x input by user
  if (tr==0){                    //Top row was done 'stand alone' to properly insert "*" character
    printf("   *");              //Inserting "*" character when x=0
  }else{
    printf("%4d",tr);            //Filling in values for x
  }
}

/* Calculate the rest of table and display */
for (y=1;y<(sizey+1);y++){            //starting with y=1 and going until limit decided by user
  printf("\n%4d",y);                  //this loop then enters another loop in which it fills in
  for (x=1;x<(sizex+1);x++){          //the current row of the graph using the equation x*y
    printf("%4d",x*y);
  }   
}
printf("\n");  // Return cursor

return 0;      // End program
}
