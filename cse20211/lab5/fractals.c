// fractals.c
// Matthew Rundle

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "gfx.h"


// Draw triangle
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	gfx_line(x1,y1,x2,y2);
	gfx_line(x2,y2,x3,y3);
	gfx_line(x3,y3,x1,y1);
}

// Draw square
void draw_square(int x,int y,int side_length)
{
	gfx_line(x-side_length/2,y-side_length/2,x+side_length/2,y-side_length/2);
	gfx_line(x+side_length/2,y-side_length/2,x+side_length/2,y+side_length/2);
	gfx_line(x+side_length/2,y+side_length/2,x-side_length/2,y+side_length/2);
	gfx_line(x-side_length/2,y+side_length/2,x-side_length/2,y-side_length/2);
}


// Draw Sierpinski Triangle
void fractal_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	double torad=0.01745329;
	// Base case
	if (abs(x2-x1) < 5) return;

	// Drawing step
	draw_triangle(x1,y1,x2,y2,x3,y3);

	// Recursive step
	fractal_triangle(x1,y1,(x1+x2)/2,(y1+y2)/2,(x1+x3)/2,(y1+y3)/2);
	fractal_triangle((x1+x2)/2,(y1+y2)/2,x2,y2,(x2+x3)/2,(y2+y3)/2);
	fractal_triangle((x1+x3)/2,(y1+y3)/2,(x2+x3)/2,(y2+y3)/2,x3,y3);
}

// Draw Shrinking Squares
void fractal_square(int x,int y, int side_length)
{
	if(side_length < 3) return;
	
	// Drawing step
	draw_square(x,y,side_length);

	// Recursive step
	fractal_square(x-side_length/2,y-side_length/2,17*side_length/36);
	fractal_square(x+side_length/2,y-side_length/2,17*side_length/36);
	fractal_square(x+side_length/2,y+side_length/2,17*side_length/36);
	fractal_square(x-side_length/2,y+side_length/2,17*side_length/36);
}

// Draw line based on base point, direction, and length
void draw_line(double x, double y, double length, double direction)
{
	gfx_line(x,y,x+length*cos(direction),y+length*sin(direction));
}

// Draw Tree
void fractal_tree(int x, int y, int length, double direction)
{
	if(length < 2) return;

	// Drawing step
	draw_line(x,y,length,direction);

	// Recursive step
	fractal_tree( x+length*cos(direction), y+length*sin(direction), 3*length/4 , direction + 0.785398);
	fractal_tree( x+length*cos(direction), y+length*sin(direction), 3*length/4, direction - 0.785398);
}

// Draw fractal fern
void fractal_fern(double x, double y, double length, double direction)
{
	// Limiting step
	if (length < 2) return;

	// Drawing step
	draw_line(x,y,length,direction);

	// Recursive step
	fractal_fern(x+(length/4)*cos(direction),y+(length/4)*sin(direction),length/3,direction+.524);
	fractal_fern(x+(length/4)*cos(direction),y+(length/4)*sin(direction),length/3,direction-.524);
	fractal_fern(x+(length/2)*cos(direction),y+(length/2)*sin(direction),length/3,direction+.524);
	fractal_fern(x+(length/2)*cos(direction),y+(length/2)*sin(direction),length/3,direction-.524);
	fractal_fern(x+(3*length/4)*cos(direction),y+(3*length/4)*sin(direction),length/3,direction+.524);
	fractal_fern(x+(3*length/4)*cos(direction),y+(3*length/4)*sin(direction),length/3,direction-.524);
	fractal_fern(x+(length)*cos(direction),y+(length)*sin(direction),length/3,direction+.524);
	fractal_fern(x+(length)*cos(direction),y+(length)*sin(direction),length/3,direction-.524);

}

// Draw snowflake
void fractal_snowflake(int x, int y, int r)
{
	if(r<2) return;
	double angle=1.2566371;		// 72 degrees (360/5 is 72)

	// Drawing step
	draw_line(x,y,r,angle);
	draw_line(x,y,r,2*angle);
	draw_line(x,y,r,3*angle);
	draw_line(x,y,r,4*angle);
	draw_line(x,y,r,5*angle);

	// Recursive step
	fractal_snowflake(x+r*cos(angle),y+r*sin(angle),15*r/36);
	fractal_snowflake(x+r*cos(2*angle),y+r*sin(2*angle),15*r/36);
	fractal_snowflake(x+r*cos(3*angle),y+r*sin(3*angle),15*r/36);
	fractal_snowflake(x+r*cos(4*angle),y+r*sin(4*angle),15*r/36);
	fractal_snowflake(x+r*cos(5*angle),y+r*sin(5*angle),15*r/36);
}

// Draw circle
void draw_circle(int x, int y, int r)
{
	double theta;
	for (theta=0;theta<=6.283185;theta+=.01){
		gfx_line(x+r*cos(theta),y+r*sin(theta),x+r*cos(theta+.01),y+r*sin(theta+.01));
	}
}

// Draw circular lace
void fractal_lace(int x, int y, int r)
{
	// Base case
	if (r<2) return;
	
	// Declare constant
	double angle=1.04719755;

	// Drawing step
	draw_circle(x,y,r);

	// Recursive step
	fractal_lace(x+r*cos(angle),y+r*sin(angle),r/3);
	fractal_lace(x+r*cos(2*angle),y+r*sin(2*angle),r/3);
	fractal_lace(x+r*cos(3*angle),y+r*sin(3*angle),r/3);
	fractal_lace(x+r*cos(4*angle),y+r*sin(4*angle),r/3);
	fractal_lace(x+r*cos(5*angle),y+r*sin(5*angle),r/3);
	fractal_lace(x+r*cos(6*angle),y+r*sin(6*angle),r/3);
}	

// Draw spiral of squares
void fractal_spiral_sq(int x, int y, float r, double theta)
{
        // Base case
        if (r<4) return;

        //Draw
	draw_square(x+r*cos(theta),y+r*sin(theta),r/3);

        //Recursive
        fractal_spiral_sq(x,y,r*.9,theta+0.522);
}

// Draw a single point
void draw_point(int x, int y)
{
	gfx_line(x,y,x,y);
}

// Draw spiral of spiral of spirals
void fractal_spirals(int x, int y, float rmax,double theta)
{
	if (rmax<2) return;

	float r;
	// Drawing step
	for (r=rmax;r>1;r*=.95){
		draw_point(x+r*cos(theta),y+r*sin(theta));
		fractal_spirals(x+r*cos(theta),y+r*sin(theta),r/4,0);
		theta+=.5;
	}
}


// MAIN FUNCTION
int main()
{

// Open window
int xsize=800;
int ysize=800;
gfx_open(xsize,ysize,"Fun with Fractals");

// Main loop
while(1){
	while(gfx_event_waiting()){
		char c=gfx_wait();
		switch (c){
			case 'q':		//quit
				return 0;
			case '1':		//draw fractal triangle
				gfx_clear();
				fractal_triangle(25,25,xsize-25,25,xsize/2,ysize-25);
				break;
			case '2':		//draw fractal square
				gfx_clear();
				fractal_square(xsize/2,ysize/2,400);
				break;
			case '3':		//draw spiral of squares
				gfx_clear();
				fractal_spiral_sq(xsize/2,ysize/2,500,0);
				break;
			case '4':		//draw circular lace
				gfx_clear();
				fractal_lace(xsize/2,ysize/2,250);
				break;
			case '5':		//draw snowflake lol
				gfx_clear();
				fractal_snowflake(xsize/2,ysize/2,250);
				break;
			case '6':		//draw tree
				gfx_clear();
                                fractal_tree(xsize/2,ysize-10,200,-1.57079633);
                                break;
			case '7':		//draw fern
				gfx_clear();	
				fractal_fern(xsize/2,ysize-100,ysize-400,-1.57079633);
				break;
			case '8':		//draw a badass spiral of spirals
				gfx_clear();
				fractal_spirals(xsize/2,ysize/2,500,0);
				break;			
		}
	}
}

}
