//******************************//
//				//
//	towers.c		//
//	cse20211.01		//
//	Final Project		//
//	Matt Rundle		//
//	Matt Mahan		//
//				//
//******************************//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "gfx.h"
#include "typewriter.h"
#define SIZE 600

struct bad_guy{
	double x_pos;	// x-position of the bad dude
	double y_pos;	// y-position of the bad dude
	double health;	// health of the bad dude, x/100
	double max_health;
	int type;	// type of bad dude, there can be multiple
	int velocity;	// determined by type
	int max_velocity;
};

struct Tower{
	double x_pos;
	double y_pos;
	int range;
	int damage; //per second
	int type;
	int cooldown;
};

struct bombs{
	int x_pos,y_pos;
	int x_init,y_init;
	int x_final,y_final;
	double velocity;
	double theta;
	int range;
};

void draw_big_F(double x, double y, double height){
	int i;
	for(i=x;i<=x+height/6;i++){
		gfx_line(i,y-height/2,i,y+height/2);
	}
	for(i=y-height/2;i<=y-height/3;i++){
		gfx_line(x+height/6,i,x+height/2,i);
	}
	for(i=y-height/6;i<=y;i++){
		gfx_line(x+height/6,i,x+height/3,i);
	}
}

//void draw_string(int x, int y, int height, char str[1000]); 
//x and y are the x and y coordinates of the upper left hand corner of the first character in the string
//height is the height of the characters, the string is a string, maximum of 1000 characters.

// Draws the 15*15 grid
void draw_grid(){
	gfx_color(205,201,201);
	int i;
	for(i=SIZE/15;i<=SIZE;i+=(SIZE/15)){
		gfx_line(i,0,i,SIZE);
		gfx_line(0,i,SIZE,i);
	}
}

// Draws path onto grid
void draw_path(){
	gfx_color(0,0,0);
	gfx_line(120,0,120,120);
	gfx_line(120,120,400,120);
	gfx_line(400,120,400,200);
	gfx_line(40,200,400,200);
	gfx_line(40,200,40,520);
	gfx_line(40,520,280,520);
	gfx_line(280,520,280,320);
	gfx_line(280,320,360,320);
	gfx_line(360,320,360,400);
	gfx_line(360,400,480,400);
	gfx_line(480,400,480,560);
	gfx_line(480,560,600,560);
	gfx_line(160,0,160,80);
	gfx_line(160,80,440,80);
	gfx_line(440,80,440,240);
	gfx_line(440,240,80,240);
	gfx_line(80,240,80,480);
	gfx_line(80,480,240,480);
	gfx_line(240,480,240,280);
	gfx_line(240,280,400,280);
	gfx_line(400,280,400,360);
	gfx_line(400,360,520,360);
	gfx_line(520,360,520,520);
	gfx_line(520,520,600,520);
}

// Draws bar on screen to separate the board and the menu, thickness 3 px
void draw_bar(){
	int i;
	// black
	gfx_color(0,0,0);
	for(i=0;i<4;i++){
		gfx_line(SIZE+i,0,SIZE+i,SIZE);
	}
}
		

// Draw bad guy 
void draw_badguy(struct bad_guy *badguy,int number_badguy,double size){
	int i;
	double toTheta=0.0174533;	// multiply degrees by this to get theta
	double theta;	
	//loop through each badguy
	if(number_badguy>0){
	for(i=0;i<number_badguy;i++){
		gfx_color(178,34,34);
		if(badguy[i].type==1){
			for(theta=0;theta<=(toTheta*360);theta+=(toTheta*45)){
				gfx_line(badguy[i].x_pos,badguy[i].y_pos,badguy[i].x_pos+size*cos(theta),badguy[i].y_pos+size*sin(theta));
			}
		}
		if(badguy[i].type==2){
			gfx_line(badguy[i].x_pos-size,badguy[i].y_pos-size,badguy[i].x_pos+size,badguy[i].y_pos-size);
			gfx_line(badguy[i].x_pos-size,badguy[i].y_pos-size,badguy[i].x_pos,badguy[i].y_pos+size);
			gfx_line(badguy[i].x_pos+size,badguy[i].y_pos-size,badguy[i].x_pos,badguy[i].y_pos+size);
		}
		if(badguy[i].type==3){
			gfx_line(badguy[i].x_pos-size,badguy[i].y_pos-size,badguy[i].x_pos+size,badguy[i].y_pos-size);
			gfx_line(badguy[i].x_pos+size,badguy[i].y_pos-size,badguy[i].x_pos+size,badguy[i].y_pos+size);
			gfx_line(badguy[i].x_pos+size,badguy[i].y_pos+size,badguy[i].x_pos-size,badguy[i].y_pos+size);
			gfx_line(badguy[i].x_pos-size,badguy[i].y_pos+size,badguy[i].x_pos-size,badguy[i].y_pos-size);
		}
		//draw health bar
		if(badguy[i].health>=(.7*badguy[i].max_health)) gfx_color(0,100,0);
		if(badguy[i].health<(.7*badguy[i].max_health) && badguy[i].health>=(.4*badguy[i].max_health)) gfx_color(218,165,32);
		if(badguy[i].health<.4*badguy[i].max_health) gfx_color(178,34,34);
		gfx_line(badguy[i].x_pos-(size),badguy[i].y_pos-(size+2),badguy[i].x_pos-(size)+2*size*(badguy[i].health/badguy[i].max_health),badguy[i].y_pos-(size+2));
		gfx_line(badguy[i].x_pos-(size),badguy[i].y_pos-(size+3),badguy[i].x_pos-(size)+2*size*(badguy[i].health/badguy[i].max_health),badguy[i].y_pos-(size+3));
	}
	}
}

// Remove a badguy
void delete_badguy(struct bad_guy *badguy,int x,int *number_badguy){
	int i;
	for(i=x;i<*number_badguy;i++){
		badguy[i]=badguy[i+1];
	}
	*number_badguy=*number_badguy-1;
}

// Add the tower to the array, while checking to make sure it isn't on the path and it is centered
int place_tower(struct Tower *tower,int number_tower,int x_pos,int y_pos,int type,int *money){ 
	// Center the tower
	x_pos=x_pos-(x_pos%40)+20;
	y_pos=y_pos-(y_pos%40)+20;
	// Check to make sure it isn't on path
	if( (x_pos==140 && y_pos==20) || (x_pos==140 && y_pos==60) || (x_pos==140 && y_pos==100) || (x_pos==180 && y_pos==100) ||
	    (x_pos==220 && y_pos==100)|| (x_pos==260 && y_pos==100)|| (x_pos==300 && y_pos==100) || (x_pos==340 && y_pos==100) ||
	    (x_pos==380 && y_pos==100)|| (x_pos==420 && y_pos==100)|| (x_pos==420 && y_pos==140) || (x_pos==420 && y_pos==180) ||
	    (x_pos==420 && y_pos==220)|| (x_pos==380 && y_pos==220)|| (x_pos==340 && y_pos==220) || (x_pos==300 && y_pos==220) ||
	    (x_pos==260 && y_pos==220)|| (x_pos==220 && y_pos==220)|| (x_pos==180 && y_pos==220) || (x_pos==140 && y_pos==220) ||
	    (x_pos==100 && y_pos==220)|| (x_pos==60 && y_pos==220) || (x_pos==60 && y_pos==260)  || (x_pos==60 && y_pos==300)  ||
	    (x_pos==60 && y_pos==340) || (x_pos==60 && y_pos==380) || (x_pos==60 && y_pos==420)  || (x_pos==60 && y_pos==460)  ||
	    (x_pos==60 && y_pos==500) || (x_pos==100 && y_pos==500)|| (x_pos==140 && y_pos==500) || (x_pos==180 && y_pos==500) ||
	    (x_pos==220 && y_pos==500)|| (x_pos==260 && y_pos==500)|| (x_pos==260 && y_pos==460) || (x_pos==260 && y_pos==420) ||
	    (x_pos==260 && y_pos==380)|| (x_pos==260 && y_pos==340)|| (x_pos==260 && y_pos==300) || (x_pos==300 && y_pos==300) ||
	    (x_pos==340 && y_pos==300)|| (x_pos==380 && y_pos==300)|| (x_pos==380 && y_pos==340) || (x_pos==380 && y_pos==380) ||
	    (x_pos==420 && y_pos==380)|| (x_pos==460 && y_pos==380)|| (x_pos==500 && y_pos==380) || (x_pos==500 && y_pos==420) ||
	    (x_pos==500 && y_pos==460)|| (x_pos==500 && y_pos==500)|| (x_pos==500 && y_pos==540) || (x_pos==540 && y_pos==540) ||
            (x_pos==580 && y_pos==540) ) return 0;
	// check to make sure another tower isn't there
	int i;
	for(i=0;i<(number_tower);i++){
		if(x_pos==tower[i].x_pos && y_pos==tower[i].y_pos) return 0;
	}
	// check to make sure you have enough money
	if(*money<250) return 0;

	tower[number_tower].type=type;
	tower[number_tower].x_pos=x_pos;
	tower[number_tower].y_pos=y_pos;
	tower[number_tower].range=100;
	if(tower[number_tower].type==1){
		tower[number_tower-1].damage=30; //per second
		*money-=250;
	}
	if(tower[number_tower].type==2){
		*money-=250;
	}
	if(tower[number_tower].type==3){
		tower[number_tower].cooldown=0; //seconds
		*money-=250;
	}
	return 1;
}

// Draw tower
void draw_tower(struct Tower *tower,int number_tower){
	int i;
	int r=15; //radius of tower
	double toTheta=0.0174533;	// multiply degrees by this to get theta
	double theta;	
	//loop through each tower
	if(number_tower>0){
	for(i=0;i<=number_tower;i++){
		if(tower[i].type==1){
			gfx_color(0,0,128);
			for(theta=0;theta<=(toTheta*360);theta+=((360/8)*toTheta)){
				gfx_line(tower[i].x_pos+r*cos(theta),tower[i].y_pos+r*sin(theta),
		                         tower[i].x_pos+r*cos(theta+(360/8)*toTheta),tower[i].y_pos+r*sin(theta+(360/8)*toTheta));
			}
		}
		if(tower[i].type==2){
			gfx_color(0,100,0);
			gfx_line(tower[i].x_pos,tower[i].y_pos-15,tower[i].x_pos-(15),tower[i].y_pos+15);
			gfx_line(tower[i].x_pos,tower[i].y_pos-15,tower[i].x_pos+(15),tower[i].y_pos+15);
			gfx_line(tower[i].x_pos-(15),tower[i].y_pos+15,tower[i].x_pos+(15),tower[i].y_pos+15);		
		}
		if(tower[i].type==3){
			gfx_line(tower[i].x_pos-15,tower[i].y_pos-15,tower[i].x_pos,tower[i].y_pos);
			gfx_line(tower[i].x_pos-15,tower[i].y_pos+15,tower[i].x_pos,tower[i].y_pos);
			gfx_line(tower[i].x_pos+15,tower[i].y_pos-15,tower[i].x_pos,tower[i].y_pos);
			gfx_line(tower[i].x_pos+15,tower[i].y_pos+15,tower[i].x_pos,tower[i].y_pos);
			gfx_line(tower[i].x_pos-15,tower[i].y_pos-15,tower[i].x_pos-15,tower[i].y_pos+15);
			gfx_line(tower[i].x_pos+15,tower[i].y_pos-15,tower[i].x_pos+15,tower[i].y_pos+15);
		}
	}
	}

}

// Follow path
void apply_path(struct bad_guy *badguy,int *number_badguy,int *number_removed,int *lives,double dt){
	int i;
	//loop through each badguy
	if(*number_badguy>0){
	for(i=0;i<*number_badguy;i++){
		//and for each, apply path rules using unique speed
		if(badguy[i].y_pos<=100) badguy[i].y_pos+=(badguy[i].velocity*dt);
		if(badguy[i].y_pos>100 && badguy[i].y_pos<120 && badguy[i].x_pos<420) badguy[i].x_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>=420 && badguy[i].x_pos<440 && badguy[i].y_pos>100 && badguy[i].y_pos<220) badguy[i].y_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>60 && badguy[i].x_pos<440 && badguy[i].y_pos<240 && badguy[i].y_pos>=220) badguy[i].x_pos-=(badguy[i].velocity*dt);
		if(badguy[i].x_pos<=60 && badguy[i].x_pos>40 && badguy[i].y_pos>=220 && badguy[i].y_pos<500) badguy[i].y_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>40 && badguy[i].x_pos<260 && badguy[i].y_pos>=500 && badguy[i].y_pos<520) badguy[i].x_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>=260 && badguy[i].x_pos<280 && badguy[i].y_pos<520 && badguy[i].y_pos>300) badguy[i].y_pos-=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>=260 && badguy[i].x_pos<380 && badguy[i].y_pos<=300 && badguy[i].y_pos>280) badguy[i].x_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>=380 && badguy[i].x_pos<400 && badguy[i].y_pos>280 && badguy[i].y_pos<380) badguy[i].y_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>=360 && badguy[i].x_pos<500 && badguy[i].y_pos>=380 && badguy[i].y_pos<400) badguy[i].x_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>=500 && badguy[i].x_pos<520 && badguy[i].y_pos>360 && badguy[i].y_pos<540) badguy[i].y_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>=480 && badguy[i].y_pos>=540 && badguy[i].y_pos<560) badguy[i].x_pos+=(badguy[i].velocity*dt);
		if(badguy[i].x_pos>600){
			delete_badguy(badguy,i,number_badguy);
			*number_removed=*number_removed+1;
			*lives=*lives-1;
		}
		//reset all speeds to max speed
		badguy[i].velocity=badguy[i].max_velocity;
	}
	}
}

// Draw shots from tower to badguys and apply effects of these shots
void apply_draw_shots(struct bad_guy *badguy,struct Tower *tower,int *number_badguy,int number_tower,int *number_removed,int *total_removed,double dt){
	int i,j;
	//loop through each tower
	if(number_tower>0){
	for(i=0;i<number_tower;i++){
		//loop through each badguy, find most threatening bad guy in range and shoot it
		//NOTE: most threatening will be lowest number in list, because it was created first
		if(*number_badguy>0 && tower[i].type!=3){	
		for(j=0;j<*number_badguy;j++){
			double distance=sqrt(pow(tower[i].x_pos-badguy[j].x_pos,2)+pow(tower[i].y_pos-badguy[j].y_pos,2));
			if(distance<=tower[i].range){
				// Draw color of beam (possibly based on tower type)
				if(tower[i].type==1){
					gfx_color(0,0,128);
					gfx_line(tower[i].x_pos,tower[i].y_pos,badguy[j].x_pos,badguy[j].y_pos);
					// Apply the damage to the badguy, get rid if dead
					badguy[j].health-=(tower[i].damage*dt);
				}
				if(tower[i].type==2){
					gfx_color(0,100,0);
					// gfx_line(tower[i].x_pos,tower[i].y_pos,badguy[j].x_pos,badguy[j].y_pos);
					// Slow the badguy down
					badguy[j].velocity=(0.5*badguy[j].velocity);
					if(badguy[j].velocity<5) badguy[j].velocity=5;
				}
				if(badguy[j].health<=0 || badguy[j].velocity==0){
					delete_badguy(badguy,j,number_badguy);
					*number_removed=*number_removed+1;
					*total_removed=*total_removed+1;
				}
				// Make sure to skip to the end of the list of badguys, we have our victim. Next tower.
				if(tower[i].type==1) j=*number_badguy+1;
			}
		}
		}
	}
	}
}

void apply_draw_bombs(struct bad_guy *badguy,struct Tower *tower,struct bombs *bomb,&number_badguy,&number_tower, 
		      &number_bomb,&number_removed,&total_removed,dt){
	int i,j;
	for(i=0;i<number_tower;i++){
		// Reduce cooldown for all tower 3 types
		if(tower[i].type==3){
			if(tower[i].cooldown>0) tower[i].cooldown-=dt;
			if(tower[i].cooldown<0) tower[i].cooldown=0;
		}
		// Spawn bomb if cooldown <=0
		if(tower[i].type==3 && tower[i].cooldown<=0){
			number_bomb++;
			bomb[number_bomb-1].x_init=tower[i].x_pos;
			bomb[number_bomb-1].y_init=tower[i].y_pos;
			bomb[number_bomb-1].x_pos=x_init;
			bomb[number_bomb-1].y_pos=y_init;
			//loop through badguys to find target
			if(*number_badguy>0){	
			for(j=0;j<*number_badguy;j++){
				double distance=sqrt(pow(tower[i].x_pos-badguy[j].x_pos,2)+pow(tower[i].y_pos-badguy[j].y_pos,2));
				if(distance<=tower[i].range){
					bomb[number_bomb-1].x_final=badguy[j].x_pos;
					bomb[number_bomb-1].y_final=badguy[j].y_pos;
					j=*number_badguy+1;  // Have found the badguy to track, want to exit now
				}
			}
			}
			// Give projectile explosion radius (you can play around with this)
			bomb[number_bomb-1].range=25;
			//CALCULATE THETA FOR PROJECTILE
				//bomb[number_bomb-1].theta=
			//Re-start the 2 second cooldown for the spawning tower
			tower[i].cooldown=2;
		}	
	}

	// Draw bombs
	// loop through each bomb
	if(number_bomb>0){
	for(i=0;i<number_bomb;i++){
		//
		//  IF X_POS==X_FINAL && Y_POS==Y_FINAL, BOMB EXPLODES. TO EXECUTE THIS, LOOP THROUGH EACH BADGUY
		//		if(*number_badguy>0){	
		//		for(j=0;j<*number_badguy;j++){
		//
		//  AND FOR EACH ONE IN RANGE 
		//	  double distance=sqrt(pow(tower[i].x_pos-badguy[j].x_pos,2)+pow(tower[i].y_pos-badguy[j].y_pos,2));
		//		if(distance<=tower[i].range){
		//
		//  SUBTRACT A NET DAMAGE FROM THE BADGUYS
		//		badguy[j].health-=30;
		//
		//  MAKE SURE TO CHECK EACH BADGUY WITHIN RADIUS, DON'T STOP AFTER FIRST ONE
		//
		//  LASTLY, DELETE THE BOMB (CREATE FUNCTION SIMILAR TO remove_badguy)
}

void display_intro(){
// Set background color 
gfx_clear_color(0,100,0);
gfx_clear();
gfx_color(255,255,255);

draw_string(60, 200, 40, "MATT RUNDLE AND MATT MAHAN");
gfx_flush();
usleep(2000000); //hold a few seconds

gfx_clear();
draw_big_F(100,250,250);
draw_string(100,50,20,"A");
draw_string(180,283,90, "ISHER HALL");
draw_string(450,400,20,"PRODUCTION");
gfx_flush();
usleep(2000000); //hold a few seconds

gfx_clear_color(255,245,238);
gfx_clear();

}

void instructions(){
	char ch;
	gfx_clear();
	gfx_color(0,0,0);
	draw_string(200,50,50,"INSTRUCTIONS");
	draw_string(25,200,30,"TO PLACE A TOWER, PRESS EITHER 1, 2, OR 3");
	draw_string(25,250,30,"THE TOWER WILL APPEAR AT THE LOCATION");
	draw_string(25,300,30,"OF YOUR MOUSE, PROVIDED THAT");
	draw_string(25,350,30,"YOU HAVE ENOUGH MONEY TO BUY IT.");
	ch=gfx_wait();		
}

int main()
{
// Open window
int size_x=SIZE+200; //200 for sidebar to the right
int size_y=SIZE;
gfx_open(size_x,size_y,"Geometry Defense");

// Display intro Fisher Hall Productions, Matt Rundle and Matt Mahan. Green and White
//display_intro();

// Set background color 
gfx_clear_color(255,245,238);
gfx_clear();

// Run game	
struct bad_guy badguy[1024];  // array of bad guys; maximum number of bad guys = 1024
struct Tower tower[256];      // array of towers; maximum number of towers = 256
struct bombs bomb[128];	      // array of bombs

int number_badguy=0;
int number_tower=0;
int number_bomb=0;
int game_over=0;
int level_over=0;
int number_removed=0;
int total_removed=0;
int level=0;
char choice;
double dt=.1;
int money=250;
double clock=0;
int lives=1;	// INTIAL AMOUNT OF USER LIVES
while(game_over==0){
	// increment the level
	level++;
	money+=250;
	number_removed=0;
	level_over=0;

	while(level_over==0){
		// Take user input
		while(gfx_event_waiting()){
			choice=gfx_wait();
			int x_pos=gfx_xpos();	// mouse position x
			int y_pos=gfx_ypos();	// mouse position y
			char ch;
			switch(choice){
				case 'q':
					return 0;
				case 'p':
					// Pause the game until more input is given
					instructions();
					break;
				case '1':
					number_tower+=place_tower(tower,number_tower,x_pos,y_pos,1,&money);
					break;
				case '2':
					number_tower+=place_tower(tower,number_tower,x_pos,y_pos,2,&money);
					break;
				case '3':
					number_tower+=place_tower(tower,number_tower,x_pos,y_pos,3,&money);
			}
		}

		//Clear screen
		gfx_clear();

		// Draw grid,path,and line separating the menu from the play board
		draw_grid();
		draw_path();
		draw_bar();

		// Clear screen, draw monsters, draw towers
		draw_badguy(badguy,number_badguy,5);
		draw_tower(tower,number_tower);

		// Apply rules of shooting, draw shots from tower to badguy
		apply_draw_shots(badguy,tower,&number_badguy,number_tower,&number_removed,&total_removed,dt);
		apply_draw_bombs(badguy,bomb,&number_badguy,&number_bomb,&number_removed,&total_removed,dt);	

		// Apply path to the monsters, SUqBTRACT LIVES FROM PLAYER IF THEY MAKE IT
		apply_path(badguy,&number_badguy,&number_removed,&lives,dt);

		// Draw interface
		// void interface(int money,int lives,int count(destroyed),int wave(level));
		interface(money,lives,total_removed,level);

		// Flush graphics to screen
		gfx_flush();
		
		// Make new monsters
		// Every 2 seconds, make new monster
		clock+=dt;
		if(clock>=1 && (number_badguy+number_removed)<(2*level)){
			number_badguy++;
			// a new badguy is 'created' in badguy[number_badguy-1]
			// type gonna be random yall
			badguy[number_badguy-1].type=(rand()%3)+1;
			if(badguy[number_badguy-1].type==1){
				badguy[number_badguy-1].max_velocity=50;
				badguy[number_badguy-1].max_health=50;
			}
			if(badguy[number_badguy-1].type==2){
				badguy[number_badguy-1].max_velocity=100;
				badguy[number_badguy-1].max_health=25;
			}
			if(badguy[number_badguy-1].type==3){
				badguy[number_badguy-1].max_velocity=25;
				badguy[number_badguy-1].max_health=100;
			}
			badguy[number_badguy-1].x_pos=140;
			badguy[number_badguy-1].y_pos=0;
			badguy[number_badguy-1].health=badguy[number_badguy-1].max_health;
			badguy[number_badguy-1].velocity=badguy[number_badguy-1].max_velocity;
			clock=0;
		}
		if(number_removed>=(2*level)) level_over=1;
		if(lives<1) return 0;

		usleep(100000); // dt=0.1,sleeptime=1000000*dt
	}
}
return 0;
}
