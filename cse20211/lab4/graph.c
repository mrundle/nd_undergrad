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
        double torad=0.0174532925;	// converts degrees to radians
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
void draw_numeral(int x, int y, int n, int height)
{
        switch(n){
                case 1:
                        draw_one(x,y,height);
                        break;
                case 2:
                        draw_two(x,y,height);
                        break;
                case 3:
                        draw_three(x,y,height);
                        break;
                case 4:
                        draw_four(x,y,height);
                        break;
                case 5:
                        draw_five(x,y,height);
                        break;
                case 6:
                        draw_six(x,y,height);
                        break;
                case 7:
                        draw_seven(x,y,height);
                        break;
                case 8:
                        draw_eight(x,y,height);
                        break;
                case 9:
                        draw_nine(x,y,height);
                        break;
                case 0:
                        draw_zero(x,y,height);
                        break;
        }
}

// Draw maxima
void draw_maxima(int x, int y, int r)
{
        draw_curve(x,y,r,0,360);

	int i=1;	// for the loop, will increment
	int n;		// for the loop, will increment
	int cont=0;	
	int num=0;	// the actual digit that will be displayed to the screen
	int getrid=0;	// variable that will keep track of all numbers to the right of the next desired digit
	int ysize=700;  // size of the screen
	
	int y_disp=ysize-y;		// this is to deal with the inversion of the y axis on the screen
	// This next loop is used to break a large integer into each individual digit,
	// right to left, and then display them to the screen. It accomplishes this by moving incrementally through
	// powers of 10
	while(cont==0){
	        n=pow(10,i);
	        num=((y_disp % n) - getrid)/(n/10);
		draw_numeral(x-(i*10),y-20,num,16);
	        getrid=(y_disp % n);			// sets getrid to all numbers that will be to the right of the next desired digit
	        if ((y_disp-n) < 0){
	                cont=1;
	        }
		i++;
	}

}

// Draw function
void draw_function(int xsize, int ysize, double a, double b)
{
	// Draw axis
	gfx_line(0,ysize/2,xsize,ysize/2);

	// Draw function
	double x,y,y_plus,y_minus;
	for(x=0;x<=xsize;x+=.01){
		y=(ysize/2)-(a*x*sin(x/b));			// Negative to invert 
		y_plus=(ysize/2)-(a*(x+.01)*sin((x+.01)/b));  	// Negative to invert (bottom of screen is negative, top is positive)
		y_minus=(ysize/2)-(a*(x-.01)*sin((x-.01)/b));	// Negative to invert
		gfx_line(x,y,x+.01,y_plus);
		if (y<y_minus && y<y_plus){
			draw_maxima(x,y,5);
		}		
	}


}

// Change "a" value
double change_a(double a, char c)
{
	switch (c){
		case 'a':
			return a/2.0;
			break;
		case 's':
			return a*2.0;
			break;
	}
}

// Change "b" value
double change_b(double b, char c)
{
        switch (c){
                case 'z':
                        return b/2.0;
                        break;
                case 'x':
                        return b*2.0;
                        break;
        }
}


int main()
{

// Set screen size
int xsize=1000;
int ysize=700;

// Open window
gfx_open(xsize,ysize,"graph.c");

// Set initial conditions of a and b
double a=10;
double b=5;

while(1){

// Set drawing color
gfx_color(0,255,0);

// Draw function
draw_function(xsize,ysize,a,b);

// Clear screen
gfx_flush();

// Collect user input
	while (gfx_event_waiting()){
		char c=gfx_wait();
		switch (c){
			case 'a':		// decrease a
				a=change_a(a,c);
				gfx_clear();
				draw_function(xsize,ysize,a,b);
				break;
			case 's':		// increase a
				a=change_a(a,c);
				gfx_clear();
				draw_function(xsize,ysize,a,b);
				break;
			case 'z':		// decrease b
				b=change_b(b,c);
				gfx_clear();
				draw_function(xsize,ysize,a,b);
				break;
			case 'x':		// increase b
				b=change_b(b,c);
				gfx_clear();
				draw_function(xsize,ysize,a,b);
				break;
			case 'q':		// quit
				return 0;
			default:
				break;
		}
	}
}

}
