// warmup.c
// By Matthew Rundle
// for cse20211.01
// Fall 2012

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// print array
void print_array(double x[],int size)
{
	int i;
	for(i=0;i<size;i++){
		printf(" %.2lf",x[i]);	
	}
}

// Compute average of the list
void avg_and_stddev(double x[],int size)
{
        int i;
	
	// Compute Average
	double sum=0;
	double avg;
        for(i=0;i<size;i++){	
		sum+=x[i];
	}
	avg=sum/size;
	printf("\nThe average of the array is:   %.2lf\n",avg);
	
	// Compute Standard Deviation
	double stddev=0;
	for(i=0;i<size;i++){
		stddev+=(x[i]-avg)*(x[i]-avg);
	}
	stddev=stddev/(size-1);
	stddev=sqrt(stddev);
	printf("\nThe standard deviation of the array is:   %.2lf\n",stddev);
}

void bubble_sort(double x[],int size)
{
	int i,j,temp;
	
	//sort
	for (i=(size-1);i>0;i--){
		for(j=1;j<=i;j++){
			if(x[j-1]>x[j]){
				temp=x[j-1];
				x[j-1]=x[j];
				x[j]=temp;
			}
		}
	}
	
	//print
	printf("\nThe sorted array is: {");
	for (i=0;i<size;i++){
	   printf(" %.2lf",x[i]);
	}
	printf(" }\n\n");
}

int main (void) 
{

int size=10;
double x[size];

// read in values
printf("\nEnter ten values to populate the array.\n");
printf("The average, standard deviation, and sorted listing will be displayed.\n");
int i;
for(i=0;i<size;i++){
	printf("%d: ",i+1);
	scanf("%lf",&x[i]);
}

// output data
printf("\nYou entered: {");
print_array(x,size);
printf(" }\n");
avg_and_stddev(x,size);
bubble_sort(x,size);

return 0;

}
