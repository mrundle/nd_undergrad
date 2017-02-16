 /* prog3.c by Mattew Rundle
   This program computes the final velocity 
   of a projectile based on known
   initial speed, acceleration, and 
   duration (time) of motion.
   This is based on the equation:
   vf = vi + at */

#include<stdio.h>
int main(void)
{
float vi; /* initial velocity */
float a; /* acceleration */
float t; /* time */
float vf; /* final velocity */

printf("This program computes the final velocity of an object in motion\n");
printf("based on known initial speed, acceleration, and duration (time).\n");
printf("Enter a number to express the initial velocity of the object (m): ");
scanf("%f",&vi);
	if (vi < .000001){
		printf("Unable to calculate.\n ");
		return 0;
	}
printf("Enter a number to express the acceleration of the object (m/s^2): ");
scanf("%f",&a);
	if (a < .000001){
		printf("Unable to calculate.\n");
		return 0;
	}
printf("Enter an number to express the time that the object is in motion (s): ");
scanf("%f",&t);
	if (t < .000001){
		printf("Unable to calculate.\n");
		return 0;
	}

/* Calculate results */
vf=vi+a*t;

/* Display results */
printf("The final velocity of this object is %f m/s.\n", vf);

return 0;
}

