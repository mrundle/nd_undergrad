/* bounce.c
   Created by Matthew Rundle
   for cse20211.01, September 2012
   This program creates the animation of a circle moving around the
   screen at a constant velocity, bouncing away from any of the 
   edges of the window. */

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "gfx.h"

int main()
{

// Declare variables. Descriptions provided to the right of each.
//

int xsize=300;			// x size of window
int ysize=300;			// y size of window
gfx_open(xsize,ysize,"bounce.c by Matt Rundle");	// open up window
gfx_clear_color(67,81,104);	// set 'clear' color 
gfx_clear();			// clear screen			
gfx_color(255,205,42);		// set drawing color 	
float x=100;			// initial x positionl, and declare variable
float y=100;			// initial y position, and declare variable
float newx,newy,oldx,oldy;	// these variables will help draw polygon
float r=40;			// radius of circle
float vx= 100;			// velocity in x direction
float vy= 100;			// velocity in y direction
float twopi=2.0*3.14159265;     // 2*pi
float theta;			// initialize theta
float newdirection;		// new direction on mouse click
float sides=twopi/8;		// makes an octagon (or replace # sides to make something else)
float dt=.01;			// time increment
char c;				// used later with gfx_wait
int seed;

while(1){

// SEED RANDOM NUMBER GENERATOR
seed=time(NULL);
srand(seed);

// COMPUTE NEW LOCATION
// Determines new x and y positions for the polygon based on velocity 
// (vx and vy, respectively) and time dt.
//

x=(float)x+vx*dt;					// Determines new x and y positions for the circle based on velocity and time
y=(float)y+vy*dt;						

// HANDLE OUT OF BOUNDS
// If out of bounds, move back in and revert direction
//

if ((x+r) > xsize){		
	x=xsize-(r+1);
	vx=(-1*vx);
} 
if ((x-r) < 0){
	x=(r+1);
	vx=(-1*vx);
}
if ((y+r) > ysize){		
	y=ysize-(r+1);
	vy=-vy;
}
if ((y-r) < 0){
	y=(r+1);
	vy=-vy;
}

// DRAW OBJECT
//

for (theta=sides;theta<=twopi;theta=theta+sides){
   	oldx=x+(r*cos(theta));
      	oldy=y+(r*sin(theta));
  	newx=x+(r*cos(theta+sides));
  	newy=y+(r*sin(theta+sides));
    	gfx_line(oldx,oldy,newx,newy);
}

// FLUSH GRAPHICS

gfx_flush();					// release graphics for drawing 


// HANDLE USER INPUT
// If button is pressed, do something.
//

if (gfx_event_waiting()){
	c=gfx_wait();
	switch(c){
		case 1:
			x=gfx_xpos();	// If the user has pressed the 1st mouse button, the position
			y=gfx_ypos();	// of the cursor provides the new x and y position of the circle
			newdirection=(rand() % 6);		// approx of pi
			vx=((rand()%10)*50)*cos(newdirection);		// and a new velocity is assigned.
			vy=((rand()%10)*50)*sin(newdirection);
			break;
		case 'q':
			return 0;
			break;
	}		
}

// WAIT
// dt is our time change, multiplied by 1,000,000 microseconds (1 second). usleep uses microseconds
//

usleep(dt*1000000); // dt is our time change, multiplied by 1,000,000 microseconds (1 second). usleep uses microseconds

// CLEAR SCREEN
gfx_clear();

// End main "while" loop
// 

}

// Return 0 and end main function.
//

return 0;
}

