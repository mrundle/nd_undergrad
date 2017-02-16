// numbers.c
// Created by Matthew Rundle
// for cse20211.01, Lab 4
// This program opens a window and waits for user input.
// It then draws any input numeral at the position of the mouse.

#include <stdio.h>
#include <math.h>
#include "gfx.h"

// Draw curve with DEGREES 
void draw_curve(int x, int y, int r, double alpha, double beta)
{
	double torad=0.0174532925; 	// converts degrees to radians
	double theta;
	alpha=alpha*torad;
	beta=beta*torad;
	for (theta=alpha;theta<=beta;theta+=.01){
		gfx_line(x+r*cos(theta),y+r*sin(theta),x+r*cos(theta-.01),y+r*sin(theta-.01));
	}
}

// Draw number one
void draw_one(int x, int y, int height)
{
	gfx_line(x-height/4,y+height/2,x+height/4,y+height/2);
	gfx_line(x,y-height/2,x,y+height/2);
	gfx_line(x,y-height/2,x-height/4,y-height/4);
}

// Draw number two
void draw_two(int x, int y, int height)
{
	draw_curve(x,y-height/4,height/4,180,360);
	gfx_line(x+height/4,y-height/4,x-height/4,y+height/2);
	gfx_line(x-height/4,y+height/2,x+height/4,y+height/2);
}
	
// Draw number three
void draw_three(int x, int y, int height)
{
	draw_curve(x,y-height/4,height/4,180,450);
	draw_curve(x,y+height/4,height/4,-90,180);
}

// Draw number 4
void draw_four(int x, int y, int height)
{
	gfx_line(x+height/8,y-height/2,x+height/8,y+height/2);
	gfx_line(x-height/4,y,x+height/4,y);
	gfx_line(x+height/8,y-height/2,x-height/4,y);
}

// Draw number 5
void draw_five(int x, int y, int height)
{
	gfx_line(x+height/4,y-height/2,x-height/4,y-height/2);
	gfx_line(x-height/4,y-height/2,x-height/4,y);
	gfx_line(x-height/4,y,x,y);
	draw_curve(x,y+height/4,height/4,-90,90);
	gfx_line(x,y+height/2,x-height/4,y+height/2);
}

// Draw number 6
void draw_six(int x, int y, int height)
{
	draw_curve(x,y-height/4,height/4,180,360);
	gfx_line(x-height/4,y-height/4,x-height/4,y+height/4);
	draw_curve(x,y+height/4,height/4,0,360);
}

// Draw number 7
void draw_seven(int x, int y, int height)
{
	gfx_line(x-height/4,y-height/2,x+height/4,y-height/2);
	gfx_line(x+height/4,y-height/2,x-height/8,y+height/2);
}

// Draw number 8
void draw_eight(int x, int y, int height)
{
	draw_curve(x,y-height/4,height/4,0,360);
	draw_curve(x,y+height/4,height/4,0,360);
}

// Draw number 9
void draw_nine(int x, int y, int height)
{
        gfx_line(x+height/4,y-height/4,x+height/4,y+height/2);
        draw_curve(x,y-height/4,height/4,0,360);
}

// Draw number 0
void draw_zero(int x, int y, int height)
{
	draw_curve(x,y-height/4,height/4,180,360);
	draw_curve(x,y+height/4,height/4,0,180);
	gfx_line(x-height/4,y-height/4,x-height/4,y+height/4);
	gfx_line(x+height/4,y-height/4,x+height/4,y+height/4);
}

// Draw numeral
void draw_numeral(int x, int y, char n, int height)
{
	switch(n){
		case '1':
			draw_one(x,y,height);
			break;
		case '2':
			draw_two(x,y,height);
			break;
		case '3':
			draw_three(x,y,height);
			break;
		case '4':
			draw_four(x,y,height);
			break;
		case '5':
			draw_five(x,y,height);
			break;
		case '6':
			draw_six(x,y,height);
			break;
		case '7':
			draw_seven(x,y,height);
			break;
		case '8':
			draw_eight(x,y,height);
			break;
		case '9':
			draw_nine(x,y,height);
			break;
		case '0':
			draw_zero(x,y,height);
			break;
	}
}	
	


int main()
{

// Declare size of window
int xsize=500;
int ysize=700;

// Declare variables for x and y positions of location
int xpos;
int ypos;

// Declare height of each number 
int height=30;

// Open window, establish background color
gfx_open(xsize,ysize,"Numbers.c");
gfx_clear_color(250,250,232);
gfx_clear();

// DECORATION: Draw red line down left side of page,
// then blue lines horizontally down the page (looks like a notebook)
gfx_color(192,58,98);	//red
gfx_line(xsize/10,0,xsize/10,ysize);
gfx_color(115,151,235);	//blue
int liney;
int lineheight=20;
for (liney=ysize/10;liney<=ysize;liney+=lineheight){
	gfx_line(0,liney,xsize,liney);
}

// Waits for input, and then draws selected number in a dark color at location of mouse
gfx_color(78,79,81);
while(1){
	while (gfx_event_waiting()){
		char n=gfx_wait();
		xpos=gfx_xpos();	// mouse position x
		ypos=gfx_ypos();	// mouse position y
		draw_numeral(xpos,ypos,n,height);
		switch (n){
			case '=':		// increase size
				height+=10;
				break;
			case '-':
				height-=10;	// increase size
				if (height<0){
					height=0;
				}
				break;
			case 'q':		// quit
				return 0;
			default:
				break;
		}
	}
}

}
