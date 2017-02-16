// carnival.c
// By Matthew Rundle
// cse20211.01
// This program creates a model of a roller 
// coaster ride that would make you throw up.

#include <stdio.h>
#include <math.h>
#include "gfx.h"
#include <unistd.h>

// This function draws the circular wheels where the riders are strapped in
void draw_wheel(int x,int y,int r,double theta)
{
	double circtheta;
	double torad=0.0174532925;	// converts degrees to radians
	for (circtheta=0;circtheta<=(360*torad);circtheta+=.01){
		gfx_line(x+r*cos(circtheta-.01),y+r*sin(circtheta-.01),
			 x+r*cos(circtheta),y+r*sin(circtheta));
	}
	gfx_line(x+r*cos(theta),y+r*sin(theta),x+r*cos(theta+(180*torad)),y+r*sin(theta+(180*torad)));
	gfx_line(x+r*cos(theta+(90*torad)),y+r*sin(theta+(90*torad)),x+r*cos(theta+(270*torad)),y+r*sin(theta+(270*torad)));
}
	
// Draws rotating bar
void draw_rotbar(int x, int y, int r, double theta)
{
	gfx_line(x,y,x+r*cos(theta),y+r*sin(theta));
        gfx_line(x,y,x-r*cos(theta),y-r*sin(theta));
	draw_wheel(x+r*cos(theta),y+r*sin(theta),r/3,2*theta);
	draw_wheel(x-r*cos(theta),y-r*sin(theta),r/3,1.5*theta);
}

// Draws the main swinging rod
void draw_pendulum(int x, int y, int r, double theta)
{
	double degrees=0.01745329;
	int control_variable=5000;
	double inc=degrees*control_variable;
	gfx_line(x,y,x+r*cos(theta),y+r*sin(theta));
	draw_rotbar(x+r*cos(theta),y+r*sin(theta),r/2,theta*2);
}

// Draws the main structure
void draw_structure(int x, int y, int height, double theta)
{
	double basetheta;		// moves structure left and right
	double torad=0.0174532925;	// converts degrees to radians
	x=x+(x/6)*cos(theta);
	gfx_line(x,y,x-height/6,y+height);
	gfx_line(x,y,x+height/6,y+height);
	for (basetheta=0;basetheta<=(360*torad);basetheta+=.01){	
		gfx_line(x+(height/6)*cos(basetheta),(y+height)+(height/24)*sin(basetheta),
		         x+(height/6)*cos(basetheta),(y+height)+(height/24)*sin(basetheta));
	}
	for (basetheta=(20*torad);basetheta<=(360*torad);basetheta+=(60*torad)){
		gfx_line(x+(height/6)*cos(basetheta),(y+height)+(height/24)*sin(basetheta),x,y);
	}
	draw_pendulum(x,y,0.6*height,theta);
}

int main()
{

// Declare size of window, open window, determine background color
int xsize=1000;
int ysize=1000;
gfx_open(xsize,ysize,"CRAZY CARNIVAL WOOHOO");
gfx_clear_color(0,51,102);
gfx_clear();

// Initialize variables
double dt=.01;			// change in time
double torad=0.0174532925;	// converts degrees to radians
double theta=90*torad;		// sets initial theta to 90 degrees
double vtheta=2;		// initial velocity of motion
int height=5*ysize/12;		// height of structure



while(1){

// clear screen
gfx_clear();

// calculate new theta based on dt
theta=theta-vtheta*dt;

// set drawing color, draw structure
gfx_color(255,255,0);
draw_structure(xsize/2,5*ysize/12,height,theta);

// flush drawing to screen
gfx_flush();

// Sleep for dt (multiply by 1000000 because usleep uses microseconds)
usleep(dt*1000000);

// Handle user input
int xpos,ypos;
while(gfx_event_waiting()){
	char c=gfx_wait();
	switch (c){
		case 1:
			xpos=gfx_xpos();
			ypos=gfx_ypos();
			printf("%f\n",theta);
			break;		
		case 'q':
			return 0;
			break;
		case 'a':
			height-=5;
			break;
		case 'd':
			height+=5;
			break;
		case '=':		// Increase velocity
			vtheta+=.5;
			break;
		case '-':		// Decrease velocity
			vtheta-=.5;
			break;
	}
}

} // outside while loop closed

} // main fn closed




