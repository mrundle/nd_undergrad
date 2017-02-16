// Typewriter for Final Project
// Matt Mahan

/*
Typewriter.c For Dummies

    Download typewriter.c and typewriter.h into the same directory as the main program.
    Add #include "typewriter.h" to the main program .c file
    The prototype for the primary function is void draw_string(int x, int y, int height, char str[1000]); x and y are the x and y coordinates of the upper left hand corner of the first character in the string, height is the height of the characters, the string is a string, maximum of 1000 characters.
    It will take strings with capital letters, numbers, periods, commas, exclamation marks, question marks, and apostrophes. Note that the punctuation sucks.
    It will tell you if you try to use the function with improper characters, even if you don't get a compile error.
    To compile, the command is gcc main.c gcc.c typewriter.c -o main -lm -lX11
    Enjoy
*/

// Libraries
#include <stdio.h>
#include "gfx.h"
#include "typewriter.h"
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Global values
const double incr=.05;

// A function that draws an arc. Alpha and beta refer to angles on the unit 
// circle
void draw_arc(int x, int y, double r, double alpha, double beta)
{
  double theta;
  for (theta=alpha;theta<=beta;theta+=incr){
    gfx_line(x+r*cos(theta),y+r*sin(theta),x+r*cos(theta+incr),y+r*sin(theta+incr));
  }
}

// A function that draws a circle
void draw_circle(int x, int y, double r)
{
  draw_arc(x,y,r,0,2*M_PI);
}

// A function that draws a curve. yrad and xrad refer to the half the maximum 
// height of the ellipse of which a portion is being drawn and half the maximum
// width of the ellipse of which a portion is being drawn, respectively
void draw_curve(int x, int y, double xrad, double yrad, double alpha, double beta) 
{
  double theta;
  for (theta=alpha;theta<=beta;theta+=incr){
    gfx_line(x+xrad*cos(theta),y+yrad*sin(theta),x+xrad*cos(theta+incr),y+yrad*sin(theta+incr));
  }
}

// A function that draws a one
void draw_one(int x, int y, int height)
{
  gfx_line(x+height/4,y,x+height/4,y+height);
  gfx_line(x,y+height,x+height/2,y+height);
  gfx_line(x+height/4,y,x,y+height/4);
}

// A function that draws a two
void draw_two(int x, int y, int height)
{
  draw_arc(x+height/4,y+height/4,height/4,M_PI,2*M_PI);
  gfx_line(x+height/2,y+height/4,x,y+height);
  gfx_line(x,y+height,x+height/2,y+height);
}

// A function that draws a three
void draw_three(int x, int y, int height)
{
  draw_arc(x+height/4,y+height/4,height/4,M_PI,5*M_PI/2);
  draw_arc(x+height/4,y+3*height/4,height/4,3*M_PI/2,3*M_PI);
}

// A function that draws a four
void draw_four(int x, int y, int height)
{
  gfx_line(x,y,x,y+height/2);
  gfx_line(x,y+height/2,x+height/2,y+height/2);
  gfx_line(x+height/2,y,x+height/2,y+height);
}

// A function that draws a five
void draw_five(int x, int y, int height)
{
  gfx_line(x,y,x+height/2,y);
  gfx_line(x,y,x,y+height/2);
  gfx_line(x,y+height/2,x+height/4,y+height/2);
  draw_arc(x+height/4,y+3*height/4,height/4,-M_PI/2,M_PI);
}

// A function that draws a six
void draw_six(int x, int y, int height)
{
  draw_circle(x+height/4,y+3*height/4,height/4);
  draw_curve(x+height/2,y+3*height/4,height/2,3*height/4,M_PI,3*M_PI/2);
}

// A function that draws a seven
void draw_seven(int x, int y, int height)
{
  gfx_line(x,y,x+height/2,y);
  gfx_line(x+height/2,y,x,y+height);
}

// A function that draws an eight
void draw_eight(int x, int y, int height)
{
  draw_circle(x+height/4,y+height/4,height/4);
  draw_circle(x+height/4,y+3*height/4,height/4);
}

// A function that draws a nine
void draw_nine(int x, int y, int height)
{
  draw_circle(x+height/4,y+height/4,height/4);
  draw_curve(x,y+height/4,height/2,3*height/4,0,M_PI/2);
}

// A function that draws a zero
void draw_zero(int x, int y, int height)
{
  draw_curve(x+height/4,y+height/2,height/4,height/2,0,2*M_PI);
  gfx_line(x+height/4+height/4*cos(3*M_PI/4),y+height/2+height/2*sin(3*M_PI/4),x+height/4+height/4*cos(7*M_PI/4),y+height/2+height/2*sin(7*M_PI/4));
}

// A function that draws any numeral
void draw_numeral(int x, int y, char n, int height)
{
  switch (n){
  case '0': 
    draw_zero(x,y,height); 
    break;
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
  }
}

// Draws A
void draw_A(int x, int y, int height)
{
	gfx_line(x,y+height,x+height/4,y);
	gfx_line(x+height/4,y,x+height/2,y+height);
	gfx_line(x+height/8,y+height/2,x+3*height/8,y+height/2);
}

// Draws B
void draw_B(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	draw_curve(x,y+height/4,height/2,height/4,-M_PI/2,M_PI/2);
	draw_curve(x,y+3*height/4,height/2,height/4,-M_PI/2,M_PI/2);
}

// Draws C
void draw_C(int x, int y, int height)
{
	draw_curve(x+height/4,y+height/2,height/4,height/2,M_PI/3,5*M_PI/3);
}

// Draws D
void draw_D(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	draw_arc(x,y+height/2,height/2,-M_PI/2,M_PI/2);
}

// Draws E
void draw_E(int x, int y, int height)
{
	gfx_line(x,y,x+height/2,y);
	gfx_line(x,y,x,y+height);
	gfx_line(x,y+height/2,x+height/2,y+height/2);
	gfx_line(x,y+height,x+height/2,y+height);
}

// Draws F
void draw_F(int x, int y, int height)
{
	gfx_line(x,y,x+height/2,y);
	gfx_line(x,y,x,y+height);
	gfx_line(x,y+height/2,x+height/2,y+height/2);
}

// Draws G
void draw_G(int x, int y, int height)
{
	draw_curve(x+height/4,y+height/2,height/4,height/2,0,5*M_PI/3);
	gfx_line(x+height/4,y+height/2,x+height/2,y+height/2);
}

// Draws H
void draw_H(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	gfx_line(x+height/2,y,x+height/2,y+height);
	gfx_line(x,y+height/2,x+height/2,y+height/2);
}

// Draws I
void draw_I(int x, int y, int height)
{
	gfx_line(x+height/4,y,x+height/4,y+height);
	gfx_line(x+height/16,y,x+7*height/16,y);
	gfx_line(x+height/16,y+height,x+7*height/16,y+height);
}

// Draws J
void draw_J(int x, int y, int height)
{
	gfx_line(x,y,x+height/2,y);
	gfx_line(x+height/2,y,x+height/2,y+7*height/8);
	draw_curve(x+height/4,y+7*height/8,height/4,height/8,0,M_PI);
}

// Draws K
void draw_K(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	gfx_line(x,y+height/2,x+height/2,y);
	gfx_line(x,y+height/2,x+height/2,y+height);
}

// Draws L
void draw_L(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	gfx_line(x,y+height,x+height/2,y+height);
}

// Draws M
void draw_M(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	gfx_line(x+height/2,y,x+height/2,y+height);
	gfx_line(x,y,x+height/4,y+height/2);
	gfx_line(x+height/2,y,x+height/4,y+height/2);
}

// Draws N
void draw_N(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	gfx_line(x+height/2,y,x+height/2,y+height);
	gfx_line(x,y,x+height/2,y+height);
}

// Draws O
void draw_O(int x, int y, int height)
{
	draw_curve(x+height/4,y+height/2,height/4,height/2,0,2*M_PI);
}

// Draws P
void draw_P(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	draw_curve(x,y+height/4,height/2,height/4,-M_PI/2,M_PI/2);
}

// Draws Q
void draw_Q(int x, int y, int height)
{
	draw_curve(x+height/4,y+height/2,height/4,height/2,0,2*M_PI);
	gfx_line(x+3*height/8,y+3*height/4,x+height/2,y+height);
}

// Draws R
void draw_R(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	draw_curve(x,y+height/4,height/2,height/4,-M_PI/2,M_PI/2);
	gfx_line(x,y+height/2,x+height/2,y+height);
}

// Draws S
void draw_S(int x, int y, int height)
{
	draw_arc(x+height/4,y+height/4,height/4,M_PI/2,2*M_PI);
	draw_arc(x+height/4,y+3*height/4,height/4,-M_PI/2,M_PI);
}

// Draws T
void draw_T(int x, int y, int height)
{
	gfx_line(x,y,x+height/2,y);
	gfx_line(x+height/4,y,x+height/4,y+height);
}

// Draws U
void draw_U(int x, int y, int height)
{
	gfx_line(x,y,x,y+3*height/4);
	gfx_line(x+height/2,y,x+height/2,y+3*height/4);
	draw_curve(x+height/4,y+3*height/4,height/4,height/4,0,M_PI);
}

// Draws V
void draw_V(int x, int y, int height)
{
	gfx_line(x,y,x+height/4,y+height);
	gfx_line(x+height/2,y,x+height/4,y+height);
}

// Draws W
void draw_W(int x, int y, int height)
{
	gfx_line(x,y,x,y+height);
	gfx_line(x+height/2,y,x+height/2,y+height);
	gfx_line(x,y+height,x+height/4,y+height/2);
	gfx_line(x+height/2,y+height,x+height/4,y+height/2);
}

// Draws X
void draw_X(int x, int y, int height)
{
	gfx_line(x,y,x+height/2,y+height);
	gfx_line(x,y+height,x+height/2,y);
}

// Draws Y
void draw_Y(int x, int y, int height)
{
	gfx_line(x,y,x+height/4,y+height/2);
	gfx_line(x+height/2,y,x+height/4,y+height/2);
	gfx_line(x+height/4,y+height/2,x+height/4,y+height);
}

// Draws Z
void draw_Z(int x, int y, int height)
{
	gfx_line(x,y,x+height/2,y);
	gfx_line(x,y+height,x+height/2,y);
	gfx_line(x,y+height,x+height/2,y+height);
}

// Draws a period
void draw_period(int x, int y, int height)
{
	double r;
	for(r=height/16;r>=1;r--) draw_circle(x+height/4,y+14*height/16,r);
}

// Draws a comma
void draw_comma(int x, int y, int height)
{
	double r;
	for(r=height/16;r>=1;r--) draw_circle(x+height/4,y+14*height/16,r);
	draw_curve(x+3*height/16,y+14*height/16,height/8,height/8,0,M_PI/2);
}

// Draws an apostrophe
void draw_apostrophe(int x, int y, int height)
{
	double r;
	for(r=height/16;r>=1;r--) draw_circle(x+height/4,y+2*height/16,r);
	draw_curve(x+3*height/16,y+2*height/16,height/8,height/8,0,M_PI/2);
}

// Draws an exclamation mark
void draw_excl(int x, int y, int height)
{
	gfx_line(x+height/4,y,x+height/4,y+5*height/8);
	double r;
	for(r=height/16;r>=1;r--) draw_circle(x+height/4,y+14*height/16,r);
}

// Draws a question mark
void draw_ques(int x, int y, int height)
{
	gfx_line(x+height/4,y+height/2,x+height/4,y+5*height/8);
	draw_arc(x+height/4,y+height/4,height/4,-M_PI,M_PI/2);
	double r;
	for(r=height/16;r>=1;r--) draw_circle(x+height/4,y+14*height/16,r);
}

// Draws a character
void draw_char(int x, int y, char n, int height)
{
	if(isdigit(n)){
		draw_numeral(x,y,n,height);
		return;
	}
	switch(n){
	case 'A': 
		draw_A(x,y,height);
		break;
	case 'B': 
		draw_B(x,y,height);
		break;	
	case 'C': 
		draw_C(x,y,height);
		break;	
	case 'D': 
		draw_D(x,y,height);
		break;	
	case 'E': 
		draw_E(x,y,height);
		break;	
	case 'F': 
		draw_F(x,y,height);
		break;
		case 'G': 
		draw_G(x,y,height);
		break;
	case 'H': 
		draw_H(x,y,height);
		break;
	case 'I': 
		draw_I(x,y,height);
		break;
	case 'J': 
		draw_J(x,y,height);
		break;
	case 'K': 
		draw_K(x,y,height);
		break;
	case 'L': 
		draw_L(x,y,height);
		break;
	case 'M': 
		draw_M(x,y,height);
		break;
	case 'N': 
		draw_N(x,y,height);
		break;
	case 'O': 
		draw_O(x,y,height);
		break;
	case 'P': 
		draw_P(x,y,height);
		break;
	case 'Q': 
		draw_Q(x,y,height);
		break;
	case 'R': 
		draw_R(x,y,height);
		break;
	case 'S': 
		draw_S(x,y,height);
		break;
	case 'T': 
		draw_T(x,y,height);
		break;
	case 'U': 
		draw_U(x,y,height);
		break;
	case 'V': 
		draw_V(x,y,height);
		break;
	case 'W': 
		draw_W(x,y,height);
		break;
	case 'X': 
		draw_X(x,y,height);
		break;
	case 'Y': 
		draw_Y(x,y,height);
		break;
	case 'Z': 
		draw_Z(x,y,height);
		break;
	case '.': 
		draw_period(x,y,height);
		break;
	case ',': 
		draw_comma(x,y,height);
		break;
	case '!': 
		draw_excl(x,y,height);
		break;
	case '?': 
		draw_ques(x,y,height);
		break;
	case ' ': 
		break;
	default: 
		printf("Error: That symbol is not supported dude.\n");
		exit(1);	
	}
}

// Draw a string
void draw_string(int x, int y, int height, char str[1000])
{
	int i;
	for(i=0;i<strlen(str);i++){
		draw_char(x,y,str[i],height);
		x+=5*height/8;
	}
}
