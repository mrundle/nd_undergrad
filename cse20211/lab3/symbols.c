/*	symbol.c
	Created by Matthew Rundle
	for cse20211.01 in September 2012
	This program is a 'symbolic typewriter' which displays a 
	small symbol at the current mouse location.	*/

#include <stdio.h>
#include <math.h>
#include "gfx.h"

int main()
{

// DECLARE VARIABLES
// Descriptions are to the right side.
//

char c;
int x;
int y;
int xsize=500;
int ysize=250;
gfx_open(xsize,ysize,"Symbol.c");
float theta;
float twopi=(2.0*3.1415926535);	// value of 2*pi (360 degrees in radians)
float oldx;			// current y position for drawing radially
float newx;			// current x position for drawing radially
float oldy;
float newy;
float sides;			// angle to create sides of each polygon 
float i;			// converts char c into double
float r=15;			// radius for the shapes

while(1){

c=gfx_wait();	    	// Collect input from user (mouse click or other button)
x=gfx_xpos();		// Collect x-position of mouse
y=gfx_ypos();		// Collect y-position of mouse
switch(c){		// Switch based on user input
	case 1:		// Mouse button number 1 case should disp blue square outline
		gfx_color(0,0,255); 	// Set drawing color to blue
		gfx_line((x-r),(y+r),(x+r),(y+r));
		gfx_line((x-r),(y+r),(x-r),(y-r));
		gfx_line((x-r),(y-r),(x+r),(y-r));
		gfx_line((x+r),(y+r),(x+r),(y-r));
		break;
	case 't':	// Press of button 't' should disp green triangle
		gfx_color(106,168,82);	// Set drawing color to green
		gfx_line(x,(y-r),(x+r),(y+r));
		gfx_line(x,(y-r),(x-r),(y+r));
		gfx_line((x+r),(y+r),(x-r),(y+r));
		break;
	case 'c':
		gfx_color(255,255,255);  		// Set drawing color to white
		for (theta=0;theta<=twopi;theta=theta+.01){				
			oldx=x+(r*cos(theta));
			oldy=y+(r*sin(theta));
			newx=x+(r*cos(theta+.01));
			newy=y+(r*sin(theta+.01));
			gfx_line(oldx,oldy,newx,newy);	
		}
		break;										
	case '3':
		i=3;
		break;
	case '4':
		i=4;
		break;
	case '5':
		i=5;
		break;
	case '6':
		i=6;
		break;
	case '7':
		i=7;
		break;
	case '8':
		i=8;
		break;
	case '9':
		i=9;
		break;
	case 'q':
		break;
	default:
		printf("You pressed the wrong key.\n");	
}
   			
if (i>0){
	gfx_color(204,0,255);                   // Set drawing color to purple
	sides=twopi/i;
    	int loopno=0;
	for (theta=sides;theta<=twopi;theta=theta+sides){
          	oldx=x+(r*cos(theta));
		oldy=y+(r*sin(theta));
		newx=x+(r*cos(theta+sides));
           	newy=y+(r*sin(theta+sides));
          	gfx_line(oldx,oldy,newx,newy);
	}
}	

i=0;

if (c=='q'){
	break;
}

// End main while loop
//

}

// Return 0 and end main function.
//

return 0;
}
