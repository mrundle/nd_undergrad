/* prog2.c by Matthew Rundle
   This program collects the number of
   touchdowns, field goals, extra points,
   and safeties scored by the Irish and
   outputs the final result. */

#include<stdio.h>
int main(void)
{

/* Declare variables */
int td; /* Touchdowns */
int fg; /* Field goals */
int ep; /* Extra points */
int sf; /* Safeties */
int result; /* Result */

/* Collect data */
printf("How many touchdowns did the Irish score? Enter an integer\n");
scanf("%d",&td);
printf("How many field goals did the Irish score? Enter an integer\n");
scanf("%d",&fg);
printf("How many extra points did the Irish score? Enter an integer\n");
scanf("%d",&ep);
printf("How many safeties did the Irish score? Enter an integer\n");
scanf("%d",&sf);

/* Calculate result */
result=(6*td)+(3*fg)+(1*ep)+(2*sf);

/* Display result to user */
printf("The total scored by the Irish  was %d\n",result);

return 0;
}
