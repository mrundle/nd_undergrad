// Find max
// Turn max into individual digits

#include <stdio.h>
#include <math.h>

int main()
{

int r=394856;


int i=1;
int n;
int digits;
int cont=0;
int num=0;
int getrid=0;

while(cont==0){
	n=pow(10,i);		
	num=((r % n) - getrid)/(n/10);
	// draw number
	// x position - i*10/20/30/whatever
	getrid=(r % n);
	printf("num = %d\n\n",num);
	if ((r-n) < 0){
		digits=i;
		printf("%d digits\n",digits);	
		cont=1;
	}
	i++;
}	
printf("r is %d\n",r);

//int c;
//for(c=0;c<=digits;c++){		// for every digit

return 0;	
}
