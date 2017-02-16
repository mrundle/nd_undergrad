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
#include <unistd.h>
#include "gfx.h"
#include "typewriter.h"
#include "interface.h"
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
	double cooldown;
};

struct bombs{
	double x_pos,y_pos;
	double x_start,y_start;
	double x_final,y_final;
	double velocity;
	double theta;
	int range;
};

// Global Parameters
// Used to  modify game parameters
const int tower_range=95;
const int start_money=1500;
const int start_lives=10;
const int LazerCost=250;
const int SlowCost=500;
const int BombCost=750;
const int bounty=25;
const double SpawnDelay=.25;
const double SpawnBase=1.5;
const double SlowConstant=.50;
const int LazerDamage=6;
const int BombDamage=20;
const int BombCooldown=3;

// Drawing the big F for the intro
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

// Draw bad guy, type 1 (asterisk)
void draw_bad_one(int x, int y, int size)
{
	double toTheta=0.0174533;	// multiply degrees by this to get theta
	double theta;
	for(theta=0;theta<=(toTheta*360);theta+=(toTheta*45)){
		gfx_line(x,y,x+size*cos(theta),y+size*sin(theta));
	}
}

// Draw bad guy, type 2 (upside down triangle)
void draw_bad_two(int x, int y, int size)
{
	gfx_line(x-size,y-size,x+size,y-size);
	gfx_line(x-size,y-size,x,y+size);
	gfx_line(x+size,y-size,x,y+size);
}		

// Draw bad guy, type 3 (square)
void draw_bad_three(int x, int y, int size)
{
	gfx_line(x-size,y-size,x+size,y-size);
	gfx_line(x+size,y-size,x+size,y+size);
	gfx_line(x+size,y+size,x-size,y+size);
	gfx_line(x-size,y+size,x-size,y-size);
}

// Draw health bar
void draw_health_bar(double health, double max_health,int x,int y,int size)
{
	if(health>=(.7*max_health)) gfx_color(0,100,0);
	if(health<(.7*max_health) && health>=(.4*max_health)) gfx_color(218,165,32);
	if(health<.4*max_health) gfx_color(178,34,34);
	gfx_line(x-size,y-(size+2),x-(size)+2*size*(health/max_health),y-(size+2));
	gfx_line(x-(size),y-(size+3),x-(size)+2*size*(health/max_health),y-(size+3));
}

// Draw bad guy 
void draw_badguy(struct bad_guy *badguy,int number_badguy,double size)
{
	int i;
	double toTheta=0.0174533;	// multiply degrees by this to get theta
	double theta;	
	//loop through each badguy
	if(number_badguy>0){
	for(i=0;i<number_badguy;i++){
		gfx_color(178,34,34);
		if(badguy[i].type==1) draw_bad_one(badguy[i].x_pos,badguy[i].y_pos,size);
		if(badguy[i].type==2) draw_bad_two(badguy[i].x_pos,badguy[i].y_pos,size);
		if(badguy[i].type==3) draw_bad_three(badguy[i].x_pos,badguy[i].y_pos,size);
		//draw health bar
		draw_health_bar(badguy[i].health,badguy[i].max_health,badguy[i].x_pos,badguy[i].y_pos,size);
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

// Remove a bomb
void delete_bomb(struct bombs *bomb,int x,int *number_bomb){
	int i;
	for(i=x;i<*number_bomb;i++){
		bomb[i]=bomb[i+1];
	}
	*number_bomb=*number_bomb-1;
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
	if(*money<LazerCost && type==1) return 0;
	if(*money<SlowCost && type==2) return 0;
	if(*money<BombCost && type==3) return 0;

	tower[number_tower].type=type;
	tower[number_tower].x_pos=x_pos;
	tower[number_tower].y_pos=y_pos;
	tower[number_tower].range=tower_range;
	if(tower[number_tower].type==1){
		tower[number_tower].damage=LazerDamage; //per second
		*money-=LazerCost;
	}
	if(tower[number_tower].type==2){
		*money-=SlowCost;
	}
	if(tower[number_tower].type==3){
		tower[number_tower].cooldown=0; //seconds
		*money-=BombCost;
	}
	return 1;
}

// Draw slow tower
void draw_slow_tower(int x, int y, int size,int range){
	gfx_color(0,100,0);
	gfx_line(x,y-size,x-size,y+size);
	gfx_line(x,y-size,x+size,y+size);
	gfx_line(x-size,y+size,x+15,y+15);
	gfx_color(255,69,0);
	double toTheta=0.0174533;	// multiply degrees by this to get theta
	double theta;	
	for(theta=0;theta<(360*toTheta);theta+=.1){
		gfx_line(x+(range)*cos(theta),y+(range)*sin(theta),x+(range)*cos(theta+.1),y+(range)*sin(theta+.1));
	}	
}

// Draw laser tower
void draw_laser_tower(int x, int y, int r){
	gfx_color(0,0,128);
	double toTheta=0.0174533;	// multiply degrees by this to get theta
	double theta;
	for(theta=0;theta<=(toTheta*360);theta+=((360/8)*toTheta)){
		gfx_line(x+r*cos(theta),y+r*sin(theta),x+r*cos(theta+(360/8)*toTheta),y+r*sin(theta+(360/8)*toTheta));
	}
}

// Draw bomb tower
void draw_bomb_tower(int x, int y, int r){
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
}

// Draw tower
void draw_tower(struct Tower *tower,int number_tower){
	int i;
	int r=15; //radius of tower
	double toTheta=0.0174533;	// multiply degrees by this to get theta
	double theta;	
	//loop through each tower
	if(number_tower>0){
	for(i=0;i<number_tower;i++){
		if(tower[i].type==1) draw_laser_tower(tower[i].x_pos,tower[i].y_pos,r);
		if(tower[i].type==2) draw_slow_tower(tower[i].x_pos,tower[i].y_pos,r,tower[i].range);
		if(tower[i].type==3) draw_bomb_tower(tower[i].x_pos,tower[i].y_pos,r);
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
void apply_draw_shots(struct bad_guy *badguy,struct Tower *tower,int *number_badguy,int number_tower,int *number_removed,int *total_removed,double dt, int *money){
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
				// Draw and apply beam for Lazer Towers
				if(tower[i].type==1){
					gfx_color(255,20,147);
					gfx_line(tower[i].x_pos,tower[i].y_pos,badguy[j].x_pos,badguy[j].y_pos);
					// Apply the damage to the badguy
					badguy[j].health-=(tower[i].damage*dt);
				}
				// Slow the badguy down
				if(tower[i].type==2){
					gfx_color(0,100,0);
					badguy[j].velocity=(SlowConstant*badguy[j].velocity);
					if(badguy[j].velocity<5) badguy[j].velocity=5;
				}
				// Check for zombies
				if(badguy[j].health<=0){
					delete_badguy(badguy,j,number_badguy);
					*number_removed=*number_removed+1;
					*total_removed=*total_removed+1;
					*money+=bounty;
				}
				if(tower[i].type==1) j=*number_badguy+1;
			}
		}
		}
	}
	}
}

void apply_draw_bombs(struct bad_guy *badguy,struct Tower *tower,struct bombs *bomb,int *number_badguy,int *number_tower, 
		      int *number_bomb,int *number_removed,int *total_removed,double dt, int *money){
	int i,j;
	for(i=0;i<*number_tower;i++){
		// Reduce cooldown for all tower 3 types
		if(tower[i].type==3){
			if(tower[i].cooldown>0) tower[i].cooldown-=dt;
			if(tower[i].cooldown<0) tower[i].cooldown=0;
		}
		// Spawn bomb if cooldown <=0 and a badguy within range
		if(tower[i].type==3 && tower[i].cooldown<=0){
			if(*number_badguy>0){	
			for(j=0;j<*number_badguy;j++){
				double distance=sqrt(pow(tower[i].x_pos-badguy[j].x_pos,2)+pow(tower[i].y_pos-badguy[j].y_pos,2));
				if(distance<=tower[i].range){
					*number_bomb+=*number_bomb+1;
					bomb[*number_bomb-1].x_pos=bomb[*number_bomb-1].x_start=tower[i].x_pos;
					bomb[*number_bomb-1].y_pos=bomb[*number_bomb-1].y_start=tower[i].y_pos;
					bomb[*number_bomb-1].x_final=badguy[j].x_pos;
					bomb[*number_bomb-1].y_final=badguy[j].y_pos;
					j=*number_badguy+1;  // Have found the badguy to track, want to exit now
					// Give projectile explosion radius (you can play around with this)
					bomb[*number_bomb-1].range=30;
					//CALCULATE THETA AND VELOCITY FOR PROJECTILE
					bomb[*number_bomb-1].theta=atan2(bomb[*number_bomb-1].y_pos-bomb[*number_bomb-1].y_final,
									bomb[*number_bomb-1].x_pos-bomb[*number_bomb-1].x_final);
					double toTheta=0.0174533;	// multiply degrees by this to get theta
					bomb[*number_bomb-1].theta+=(180*toTheta);
					bomb[*number_bomb-1].velocity=50;
					//Re-start the 2 second cooldown for the spawning tower
					tower[i].cooldown=BombCooldown;
				}
			}
			}
		}	
	}
	// Draw bombs
	// loop through each bomb
	gfx_color(0,0,0);
	if(*number_bomb>0){
	for(i=0;i<*number_bomb;i++){
		int side=3;
		// calculate new position based on dt and velocity
		bomb[i].x_pos+=bomb[i].velocity*cos(bomb[i].theta)*dt;
		bomb[i].y_pos+=bomb[i].velocity*sin(bomb[i].theta)*dt;
		// draw bomb new position based on dt
		int c;
		for(c=-2;c<(2*side);c++){
		gfx_line(bomb[i].x_pos-side,bomb[i].y_pos+c,bomb[i].x_pos+side,bomb[i].y_pos+c);
		}
		// then loop through bad guys and apply damage if bomb has reached target
		if(*number_badguy>0 && sqrt(pow(bomb[i].x_pos-bomb[i].x_start,2)+pow(bomb[i].y_pos-bomb[i].y_start,2))>=sqrt(pow(bomb[i].x_start-bomb[i].x_final,2)+pow(bomb[i].y_start-bomb[i].y_final,2))){
			for(j=0;j<*number_badguy;j++){
				double distance=sqrt(pow(bomb[i].x_pos-badguy[j].x_pos,2)+pow(bomb[i].y_pos-badguy[j].y_pos,2));
				if(distance<=bomb[i].range){
					badguy[j].health-=BombDamage;
					if(badguy[j].health<=0){
						delete_badguy(badguy,j,number_badguy);
						*number_removed=*number_removed+1;
						*total_removed=*total_removed+1;
						*money+=bounty;
					}
				}
			}
			// DELETE THE BOMB
			delete_bomb(bomb,i,number_bomb);
		}
	}}
}

int display_intro(){
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
	int intro_over=0;
	double dt=0.1;
	double theta=0;
	double x_pos,y_pos;
	int radius=280;
	double clock=0;
	char choice;
	while(intro_over==0){
		//let user get out of intro
		while(gfx_event_waiting()){
			choice=gfx_wait();
			if(choice=='p') intro_over=1;
			if(choice=='q') return 0;
		}
		gfx_clear();
		// draw laser tower
		draw_laser_tower(370,300,30);
		gfx_color(178,34,34);
		// decrement theta
		theta-=dt;
		// determine positions at a certain radius away
		x_pos=370+radius*cos(theta);
		y_pos=300+radius*sin(theta);
		// draw badguy
		draw_bad_two(x_pos,y_pos,5);
		// increment clock
		clock+=dt;
		// draw laser from tower to badguy
		if(clock>1 && clock<=2){
			gfx_color(255,20,147);
			gfx_line(370,300,x_pos,y_pos);
		}
		if(clock>2) clock=0;
		// Display "GEOMETRY \n DEFENSE"
		gfx_color(0,0,0);
		draw_string(150,150,100,"GEOMETRY");
		draw_string(170,350,100,"DEFENSE");
		draw_string(650,580,15,"PRESS P TO PLAY");
		// flush graphics and sleep
		gfx_flush();
		usleep(100000); // dt=0.1,sleeptime=1000000*dt
	}
	return 1;
}

void instructions(){
	char ch;
	gfx_clear();
	gfx_color(0,0,0);
	draw_string(200,50,50,"INSTRUCTIONS");
	gfx_line(200,105,570,105);
	draw_string(25,150,30,"TO PLACE A TOWER, PRESS EITHER 1, 2, OR 3.");
	draw_string(25,200,30,"THE TOWER WILL APPEAR AT THE LOCATION");
	draw_string(25,250,30,"OF YOUR MOUSE, PROVIDED THAT");
	draw_string(25,300,30,"YOU HAVE ENOUGH MONEY TO BUY IT.");
	draw_string(580,580,15,"PRESS ANY KEY TO RETURN");
	ch=gfx_wait();		
}

void display_game_over(){
	gfx_clear_color(0,0,0);
	gfx_clear();
	gfx_color(255,255,255);
	draw_string(210,100,150,"GAME");
	draw_string(210,350,150,"OVER");
	gfx_flush();
	usleep(2000000);
}

int main()
{
// Open window
int size_x=SIZE+200; //200 for sidebar to the right
int size_y=SIZE;
gfx_open(size_x,size_y,"Geometry Defense");

while(1){
// Display intro Fisher Hall Productions, Matt Rundle and Matt Mahan. Green and White
int intro=1;
intro=display_intro();
if(intro==0) return 0;

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
int money=start_money;
double clock=0;
int lives=start_lives;	// INTIAL AMOUNT OF USER LIVES
while(game_over==0){
	// increment the level
	level++;
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
					break;
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
		apply_draw_shots(badguy,tower,&number_badguy,number_tower,&number_removed,&total_removed,dt,&money);
		apply_draw_bombs(badguy,tower,bomb,&number_badguy,&number_tower,&number_bomb,&number_removed,&total_removed,dt,&money);	

		// Apply path to the monsters, SUBTRACT LIVES FROM PLAYER IF THEY MAKE IT
		apply_path(badguy,&number_badguy,&number_removed,&lives,dt);

		// Draw interface
		interface(money,lives,total_removed,level);

		// Flush graphics to screen
		gfx_flush();
		
		// Make new monsters
		// Every 2 seconds, make new monster
		clock+=dt;
		if(clock>=SpawnDelay && (number_badguy+number_removed)<(pow(SpawnBase,level))){
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
		if(number_removed>=(pow(SpawnBase,level))) level_over=1;
		if(lives<1){
			display_game_over();
			level_over=1;
			game_over=1;
		}
		usleep(100000); // dt=0.1,sleeptime=1000000*dt
	}
}
}
return 0;
}
