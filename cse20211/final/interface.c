/* Matt Mahan and Matt Rundle
	Interface Function for Tower Program
	It draws the interface, taking in the player's lives and money.
*/

// Libraries
#include<stdio.h>
#include"gfx.h"
#include"typewriter.h"
#include<math.h>

// Global variables
const int SIZE=600; // interface width=SIZE
const int CHARS=16; // Standard text height

// Functions

// Title
void draw_title(void){
	gfx_color(0,100,0);
	draw_string(SIZE+20,10,30,"GEOMETRY");
	draw_string(SIZE+40,45,30,"DEFENSE");
}

// Money
void draw_money(int money){
	char moneystr[1000];
	gfx_color(0,0,0);
	sprintf(moneystr,"MONEY %d",money);
	draw_string(SIZE+SIZE/20,100,CHARS,moneystr);
}

// Lives
void draw_lives(int lives){
	char livesstr[1000];
	gfx_color(0,0,0);
	sprintf(livesstr,"LIVES %d",lives);
	draw_string(SIZE+SIZE/20,120,CHARS,livesstr);
}	

// Count Destroyed
void draw_count(int count){
	char countstr[1000];
	gfx_color(0,0,0);
	sprintf(countstr,"DESTROYED %d",count);
	draw_string(SIZE+SIZE/20,140,CHARS,countstr);
}

// Wave
void draw_waves(int wave){
	char wavestr[1000];
	gfx_color(0,0,0);
	sprintf(wavestr,"WAVE %d",wave);
	draw_string(SIZE+SIZE/20,160,CHARS,wavestr);
}

// Draw Tower 1 (Lazer)
void draw_T1(int r){
	// Name
	gfx_color(49,79,79);
	draw_string(SIZE+45,290,CHARS,"LAZER  250");
	// Draw Tower image
	double toTheta=0.0174533;	// multiply degrees by this to get theta
	double theta;	
	int T1xpos=SIZE+70;
	int T1ypos=250;
	gfx_color(0,0,128);
	for(theta=0;theta<=(toTheta*360);theta+=((360/8)*toTheta)){
		gfx_line(T1xpos+r*cos(theta),T1ypos+r*sin(theta),
		                         T1xpos+r*cos(theta+(360/8)*toTheta),T1ypos+r*sin(theta+(360/8)*toTheta));
	}
	// Key
	gfx_color(255,69,0);
	draw_numeral(SIZE+150,240,'1',20);
}

// Draw Tower 2 (Slow)
void draw_T2(int size){
	// Name
	gfx_color(49,79,79);
	draw_string(SIZE+45,405,CHARS,"SLOW  500");
	// Tower image
	gfx_color(0,100,0);
	int T2xpos=SIZE+70;
	int T2ypos=370;
	gfx_line(T2xpos,T2ypos-size,T2xpos-size,T2ypos+size);
	gfx_line(T2xpos,T2ypos-size,T2xpos+size,T2ypos+size);
	gfx_line(T2xpos-size,T2ypos+size,T2xpos+size,T2ypos+size);
	// Key
	gfx_color(255,69,0);
	draw_numeral(SIZE+150,360,'2',20);
}

// Draw Tower 3 (Bomb)
void draw_T3(int r){
	// Name
	gfx_color(49,79,79);
	draw_string(SIZE+45,515,CHARS,"BOMB  750");
	// Tower image
	int x=SIZE+70; //T3xpos
	int y=480; //T3ypos
	gfx_color(178,34,34);
	gfx_line(x-r,y,x,y-r);
	gfx_line(x,y-r,x+r,y);
	gfx_line(x+r,y,x,y+r);
	gfx_line(x,y+r,x-r,y);
	int side=r/5;
	gfx_line(x-side,y-side,x+side,y-side);
	gfx_line(x+side,y-side,x+side,y+side);
	gfx_line(x+side,y+side,x-side,y+side);
	gfx_line(x-side,y+side,x-side,y-side);
	// Key
	gfx_color(255,69,0);
	draw_numeral(SIZE+150,y-10,'3',20);
}


// Draw Towers
void draw_towertypes(void){
	int size=30; // Regulates size of tower images
	draw_T1(size);
	draw_T2(size);
	draw_T3(size);
}

// Draw the buttons for pause and quit
void draw_controls(void){
	gfx_color(0,0,100);
	// Pause
	draw_string(SIZE+10,544,CHARS,"PRESS P FOR PAUSE");
	// And Instructions
	draw_string(SIZE+20,562,CHARS,"AND INSTRUCTIONS");
	// Quit
	draw_string(SIZE+10,580,CHARS,"PRESS Q TO QUIT");
}

// Draws the interface
void interface(int money, int lives, int count, int wave)
{
	draw_title();
	draw_money(money);
	draw_lives(lives);
	draw_count(count);
	draw_waves(wave);
	
	// Draw Press Key
	gfx_color(49,79,79);
	draw_string(SIZE+105,200,CHARS,"PRESS KEY");
	
	draw_towertypes();
	draw_controls();
}
