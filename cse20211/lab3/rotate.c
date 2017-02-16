/* rotate.c
   Created by Matthew Rundle 
   for cse20211.01, September 2012
   This program incorporates multiple shapes and colors,
   circular motion of some kind, and lets the user control
   the display in some way. The user gets to determine
   the velocity and gravity for 'Evil Knievel'l, who goes
   around a loopdeloop and jumps a pit of flames.
   Press 'q' to quit in game. Prior to the game, instructions
   need to be followed. */

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "gfx.h"

int main()
{

//						//
// 	INFORMATION 				//
//  	USER HAS TO PRESS 1 TO CONTINUE		//
//						//


printf("-------------------------------\n");
printf("-----     EVIL KNIEVEL   ------\n");
printf("-------------------------------\n");
printf("\n");
printf("Evil Knievel is attempting to do a\n");
printf("Hot-wheels style loop-de-loop and jump\n");
printf("a pit of flames.\n");
printf("\n");
printf("You are Evil Knievel.\n");
printf("Choose your velocity, and the gravity\n");
printf("that you wish to perform under - You\n");
printf("have that kind of power. You should\n");
printf("do this by clicking inside one square\n");
printf("of each catagory.\n");
printf("\n");
printf("During the game, press 'q' to quit.\n");
printf("\n");
printf("Press 1, and then Enter, when you are ready for glory.\n");

// Checks to see if the user has entered 1. If so, continue. If not, wait.
int testcont=0;
while(testcont==0){
	int cuser;
	scanf("%d",&cuser);
	if (cuser==1){
		testcont=1;
	}
}


//               	//
//   OPEN GAME WINDOW  	//
//              	//

int xsize=1300;
int ysize=500;
gfx_open(xsize,ysize,"Evel Knievel");

//						//
//   START MAIN LOOP OF GAME			//
//						//
//   Declare variables here so that each	//
//   time the game ends, variables will		//
//   be redeclared and the user can keep	//
//   playing.					//
//						//
	
while(1){

//			//
// ESTABLISH VARIABLES	//
//			//

float torad=0.01745329; 	// 1 degree = this many radians (multiplying degrees * torad gets you radians) 
float pi=3.14159265359;  	// pi
float i; 			// counter for the loop
float thetaL,thetaR;		// theta, used to draw circular motion
float r=150;			// radius of loop-de-loop and ramp
float centerLx,centerLy;	// center of circle to draw loop-de-loop (L)
float centerRx,centerRy;	// center of circle to draw ramp (R)
float oldxL,oldyL,newxL,newyL;  // declaring variables for drawing loop-de-loop
float oldxR,oldyR,newxR,newyR;	// declaring variables for drawing ramp
int xmouse,ymouse;		// testing for click position, ***DELETE AFTER FINAL COPY***
float dt=.01667;		// dt (control motion of car)
float x=0;			// initial position of car, x
float y=100;			// initial position of car, y
float vtot=0;			// initial velocity in the x direction
float vx,vy;			// for after the jump
float vtheta;			// velocity of theta on the loopdeloop based on vx, radians per second
float ctheta=130*torad;		// theta for car around loopdeloop
float cthetar=90*torad;		// theta for car up ramp
float gravity=0;		// initializing gravity
int cont=0;			// useful later (managing going through loopdeloop twice)
int conttwo=0;			// ^^^
int contthree=0;		// ^^^
int contfour=0;			// ^^^
int contfive=0;			// ^^^
int c=0;			// initialize a counter
char input;			// ininialize a character for user input
int fx,fy;			// fire positions
float ft=0;			// used later for fire (keeps track of time for fire - "F"ire "T"ime)
int fs=-1;			// fire switch (initializing a variable for the actual mechanism of switching colors of flames)
int bugfix=0;			// bugfix and bugfix_two are used later to fix two small errors 
int bugfix_two=0;


//			//
//  MAKE BACKGROUND	//
//			//

gfx_clear_color(67,81,104);     // Dark blue 
gfx_clear();			// Clears screen to dark blue

//		//
//  DRAW TRACK 	//
//		//

gfx_color(224,73,87);           // "Holidy Red" track color
centerLx=280+(r*cos(45*torad)); // establish center of loopdeloop for drawing ref, x position
centerLy=430-(r*sin(45*torad)); // establish center of loopdeloop for drawing ref, y position
centerRx=600;                   // establish center of ramp for drawing ref, x position
centerRy=324;                   // establish center of ramp for drawing ref, y position

// Draws track leading TOloop-de-loop
gfx_line(0,100,280,430);

// Draws track leading away from loop-de-loop
gfx_line(400,473,600,473);

// Draws track after jump
gfx_line(1100,473,xsize,473);

// Draws supporting structures
gfx_line(2,102,2,ysize);//
gfx_line(50,160,50,ysize);//
gfx_line(100,218,100,ysize);//
gfx_line(150,278,150,ysize);//
gfx_line(200,335,200,ysize);//
gfx_line(250,395,250,ysize);//
gfx_line(300,447,300,ysize);//
gfx_line(350,470,350,ysize);//
gfx_line(400,473,400,ysize);//
gfx_line(450,473,450,ysize);//
gfx_line(500,473,500,ysize);//
gfx_line(550,473,550,ysize);//
gfx_line(600,473,600,ysize);//
gfx_line(650,465,650,ysize);
gfx_line(700,436,700,ysize);
gfx_line(729,400,729,ysize);
gfx_line(1100,473,1100,ysize);
gfx_line(1150,473,1150,ysize);
gfx_line(1200,473,1200,ysize);
gfx_line(1250,473,1250,ysize);
gfx_line(1300,473,1300,ysize);

// Draws loop-de-loop using radius
oldxL=centerLx+r;	// for first drawn line in loop
oldyL=centerLy;         // ^^^
for (thetaL=0.01;thetaL<=(2*pi);thetaL=thetaL+.01){
        newxL=(centerLx+r*cos(thetaL));         // new position x
        newyL=(centerLy+r*sin(thetaL));         // new position y
        gfx_line(oldxL,oldyL,newxL,newyL);	// draw lines between new and old positions
        oldxL=newxL;                            // re-assign old x-position with new position
        oldyL=newyL;                            // re-assign old y-position with new position
}

// Draws ramp
oldxR=(centerRx)+(r*cos(30*torad));     // for first drawn line in ramp circle
oldyR=(centerRy)+(r*sin(30*torad));     // ^^^
for (thetaR=(35*torad);thetaR<=(90*torad);thetaR=thetaR+.01){   // between 30 deg and 90 deg
        newxR=(centerRx+r*cos(thetaR));         // new position x
        newyR=((centerRy)+r*sin(thetaR));               // new position y
        gfx_line(oldxR,oldyR,newxR,newyR);	// draw lines between new and old positions
        oldxR=newxR;                            // re-assign old x-position with new
        oldyR=newyR;                            // re-assign old y-position with new
}


//   				           	//
//   DRAW CHOICES 				//
//   This draws the letters "V" and "G"		//
//   standing for velocity and gravity,		//
//   and then five boxes for each of them.	//
//						//

// Choose color (white) and draw lines
gfx_color(255,255,255);
gfx_line(800,50,810,70);	// "V"
gfx_line(810,70,820,50);
gfx_line(828,55,838,55);   	 // "="
gfx_line(828,65,838,65);
int bxs;			// number of boxes
float bxsr;			// boxes 'radius', aka half of one side of the square
float bxs_xpos,bxs_ypos; 	// x-position of center, y-position of center
for (bxs=40;bxs<=200;bxs=bxs+40){
	bxs_xpos=830+bxs;
	bxs_ypos=60;
	gfx_line(bxs_xpos-10,bxs_ypos-10,bxs_xpos-10,bxs_ypos+10);
	gfx_line(bxs_xpos-10,bxs_ypos-10,bxs_xpos+10,bxs_ypos-10);
	gfx_line(bxs_xpos+10,bxs_ypos+10,bxs_xpos-10,bxs_ypos+10);
	gfx_line(bxs_xpos+10,bxs_ypos+10,bxs_xpos+10,bxs_ypos-10);
}
gfx_line(800,90,820,90);	// "G"
gfx_line(800,90,800,110);
gfx_line(800,110,820,110);
gfx_line(820,110,820,103);
gfx_line(820,103,810,103);
gfx_line(828,105,838,105);	// "="
gfx_line(828,95,838,95);
for (bxs=40;bxs<=200;bxs=bxs+40){
        bxs_xpos=830+bxs;
        bxs_ypos=100;
        gfx_line(bxs_xpos-10,bxs_ypos-10,bxs_xpos-10,bxs_ypos+10);
        gfx_line(bxs_xpos-10,bxs_ypos-10,bxs_xpos+10,bxs_ypos-10);
        gfx_line(bxs_xpos+10,bxs_ypos+10,bxs_xpos-10,bxs_ypos+10);
        gfx_line(bxs_xpos+10,bxs_ypos+10,bxs_xpos+10,bxs_ypos-10);
}


//					//
//	CHOOSE BETWEEN CHOICES 		//
//	FOR VELOCITY AND GRAVITY	//
//					//

int choice=0;
int xpos,ypos=0;
char m;
while((vtot==0) || (gravity==0)){		// While two options have not been chosen
	if (gfx_event_waiting()){		// Wait for user input
		m=gfx_wait();			// Collect user input
		switch(m){			// Switch based on user input
			case 1:			// On click, collect x and y positions of mouse and store them
				xpos=gfx_xpos();
				ypos=gfx_ypos();
				printf("%d  %d\n",xpos,ypos);
				break;
			case 'q':		// Allows user to press 'q' to quit
				return 0;
		}				
	}
	// Choose vtot				// If user chooses one of the velocity squares, a corresponding velocity is given.
	for (bxs=40;bxs<=200;bxs=bxs+40){
        	bxs_xpos=830+bxs;
	        bxs_ypos=60;
                // Draw X in box to show user that input has been recieved
		if ( (xpos > (bxs_xpos-10)) && (xpos < (bxs_xpos+10)) && (ypos > (bxs_ypos-10)) && (ypos < (bxs_ypos+10)) ){	
		       	gfx_line(bxs_xpos-10,bxs_ypos-10,bxs_xpos+10,bxs_ypos+10);
        		gfx_line(bxs_xpos-10,bxs_ypos+10,bxs_xpos+10,bxs_ypos-10);
			switch(bxs){
                                        case 40:
                                                vtot=100;
						break;  
	                                case 80:
                                                vtot=125;
						break;
                                        case 120:
                                                vtot=150;
						break;
                                        case 160:
                                                vtot=175;
						break;
                                        case 200:
                                                vtot=225;
						break;
                        }
			vx=vtot*cos(30*torad);    // for after the jump
			vy=-1*(vtot*sin(30*torad));	// for after the jump
			vtheta=(2*pi)/((2*pi*r)/vtot);    // velocity of theta on the loopdeloop based on vx, radians per second
			ctheta=130*torad;                 // theta for car around loopdeloop
			cthetar=90*torad;                 // theta for car up ramp
		}
	}	
	// Choose gravity			// If user chooses one of the gravity squares, a corresponding gravity is given.
	for (bxs=40;bxs<=200;bxs=bxs+40){
	                bxs_xpos=830+bxs;
	                bxs_ypos=100;
	                // Draw X in box to show user that input has been recieved
			if ( (xpos > (bxs_xpos-10)) && (xpos < (bxs_xpos+10)) && (ypos > (bxs_ypos-10)) && (ypos < (bxs_ypos+10)) ){
	                        gfx_line(bxs_xpos-10,bxs_ypos-10,bxs_xpos+10,bxs_ypos+10);
	                        gfx_line(bxs_xpos-10,bxs_ypos+10,bxs_xpos+10,bxs_ypos-10);
	                        switch(bxs){
					case 40:
						gravity=50;
						break;
					case 80:
						gravity=100;
						break;
					case 120:
						gravity=150;
						break;
					case 160:
						gravity=200;
						break;
					case 200:
						gravity=250;
						break;
				}
	               	}
       	}
}

// Flush drawing to screen 
gfx_flush();


//			//
//       RUN GAME 	//
//			//

// Game will run as long as gameover=0. When the rider has either crashed or made it over the flames,
// gameover will be set to 1 and the loop will break.

int gameover=0;
while(gameover==0){

// Allow user to quit.
while(gfx_event_waiting()){
        char userquit=gfx_wait();
	switch (userquit){
        	case 'q':
                        return 0;
                        break;
        }
}


// Draw moving fire
// Time is kept in variable ft. At every half second, the flames will flip colors. 
ft=ft+dt;		// Time is kept here
if (ft>0.5){		// Every half second, fs changes sign and ft resets
	fs=fs*-1;	
	ft=0;
}

fy=ysize-2;		// Draw triangles, with color dependent on sign of fs
if (fs==1){
	gfx_color(184,69,67);
}else{
	gfx_color(255,122,66);
}
for (fx=760;fx<1100;fx=fx+30){
	gfx_line(fx-10,fy,fx+10,fy);
	gfx_line(fx-10,fy,fx,fy-20);
	gfx_line(fx+10,fy,fx,fy-20);
}

fy=ysize-6;
if (fs==1){		// Draw another set of triangles, color dependent on fs as well
	gfx_color(217,142,77);
}else{
	gfx_color(224,73,87);
}
for (fx=740;fx<1100;fx=fx+30){
	gfx_line(fx-10,fy,fx+10,fy);
	gfx_line(fx-10,fy,fx,fy-20);
	gfx_line(fx+10,fy,fx,fy-20);
}
			
//						//
//	 ANIMATE CAR MOVING ALONG TRACK		//
//						//

// First portion of track is the "DOWNHILL" goes from (0,100) to (280,430)
// Equation for this line is y=1.178571+100
//
// Next portion of track is the "LOOPDELOOP", which initiates the first time x passes 280 and 
// stops the second time it passes it. Vx is converted into vtheta, which is applied to 
// ctheta (which determines position of object on the loop).
// 
// Third portion of loop is the "STRAIGHT" before the ramp. Vx is used again.
// 
// Fourth portion of track is the "RAMP".
//

// Drawing color for object is determined 
gfx_color(0,0,0);


// DOWNHILL
//
// Moves the car based on "x", "vx", "dt", and position relative to beginning of loopdeloop, x=284.
// The equation of the line has been determined in y=mx+b form, and m and b have been calculated 
// and will be used in the equation.
//

float m=1.178571;		// Slope of first downhill segment
float b=100;			// Y-intercept of this line
if (x < 284 && cont==0){	// Once rider makes it past a certain 'x', exit loop and move to next segment	
	x=x+vtot*dt;		// Increment x each time via dt and vtot
	y=m*x+b-1;		// Determine postion of y via equation for line
	gfx_color(255,255,255); // Pick color for rider (white)
	gfx_line(x,y,x+20*cos(-.7939),y+20*sin(-.7939)); // Draw line representing rider, perpendicular to line
	gfx_color(67,81,104);	// Change color to background (erase previous line)
	gfx_line(x-vtot*dt,m*(x-vtot*dt)+b-1,(x-vtot*dt)+20*cos(-.7939),(m*(x-vtot*dt)+b-1)+20*sin(-.7939)); // Draw over previous position to erase it
}else{
	cont=1;
}

// Because there will be one 'unerased' position, a circle is drawn over it (one time, controlled
// by variable bugfix) to erase it.
if (cont==1 && bugfix==0){
	gfx_color(67,81,104);
       	float bugradius,bugx,bugy,theta;
       	for (bugradius=.05;bugradius<=15;bugradius=bugradius+.05){
       	        for (theta=0;theta<=(2*pi);theta+=.01){
                       	bugx=297+bugradius*cos(theta);
                       	bugy=425+bugradius*sin(theta);
                       	gfx_line(297,425,bugx,bugy);
         	}
	}
}

// Draws the loop-de-loop

float oldx,oldy;
if (cont==1 && conttwo==0){		
	bugfix=1;
	gfx_color(67,81,104);     // Background color
	gfx_line(x,y,(centerLx+(r-20)*cos(ctheta)),(centerLy+(r-20)*sin(ctheta)));     // 'Erases' old position of rider by coloring it with background color
	ctheta=ctheta-vtheta*dt;	// angle ctheta changes based on vtheta (angular velocity proportional to vtot) and dt
	x=centerLx+r*cos(ctheta);	// x position found
	y=centerLy+r*sin(ctheta);	// y position found
	gfx_color(255,255,255);	  // Drawing color of rider, white
	// Draw line representing rider, from current position to one 20 px into center
	gfx_line(x,y,(centerLx+(r-20)*cos(ctheta)),(centerLy+(r-20)*sin(ctheta))); 
	if (ctheta<(-4) && x>=400){   // if the loopdeloop has been completed, move on
		conttwo=1;
	}
	// Draws loop-de-loop using radius
	gfx_color(224,73,87);           // "Holidy Red"
	oldxL=centerLx+r;	// for first drawn line in loop
	oldyL=centerLy;         // ^^^
	for (thetaL=0.01;thetaL<=(2*pi);thetaL=thetaL+.01){
        	newxL=(centerLx+r*cos(thetaL));         // new position x
        	newyL=(centerLy+r*sin(thetaL));         // new position y
        	gfx_line(oldxL,oldyL,newxL,newyL);	// draw lines between new and old positions
        	oldxL=newxL;                            // re-assign old x-position with new position
        	oldyL=newyL;                            // re-assign old y-position with new position
	}

}

// Again there will be one 'unerased' position, a circle is drawn over it (one time, controlled
// by variable bugfix_two) to erase	it.
if (conttwo==1 && bugfix_two==0){
        gfx_color(67,81,104);
        float bugradius,bugx,bugy,theta;
        for (bugradius=.05;bugradius<=15;bugradius=bugradius+.05){
                for (theta=0;theta<=(2*pi);theta+=.01){
                        bugx=401+bugradius*cos(theta);
                        bugy=462+bugradius*sin(theta);
                        gfx_line(401,462,bugx,bugy);
                }
        }
}


//			//
//  DRAWS STRAIGHTAWAY	//
//			//

if (conttwo==1 && contthree==0){
	bugfix_two=1;
        gfx_color(67,81,104);     // Background color
        gfx_line(x,y,x,y-20);
	x=x+vtot*dt;			// x position determined by old x, vtot*dt
	y=472;				// because line is flat, y position static
	gfx_color(255,255,255);		// color of rider is white
	gfx_line(x,y,x,y-20);		// draw line 20 px high
	if (x >= 600){			// Changes segments of track once the rider has completed the straightaway
		contthree=1;
	}
}
	// Loop de loop may suffer some 'visible damage' due to erasing of rider, so we'll redraw it during this period
	// Draws loop-de-loop using radius
	gfx_color(224,73,87);           // "Holidy Red"
	oldxL=centerLx+r;	// for first drawn line in loop
	oldyL=centerLy;         // ^^^
	for (thetaL=0.01;thetaL<=(2*pi);thetaL=thetaL+.01){
	   	newxL=(centerLx+r*cos(thetaL));         // new position x
	        newyL=(centerLy+r*sin(thetaL));         // new position y
	        gfx_line(oldxL,oldyL,newxL,newyL);	// draw lines between new and old positions
	        oldxL=newxL;                            // re-assign old x-position with new position
	        oldyL=newyL;                            // re-assign old y-position with new position
}


//		//
//  DRAWS RAMP	//
//		//

if (contthree==1 && contfour==0){
	cthetar=cthetar-vtheta*dt;
	gfx_color(67,81,104);     // Background color
        gfx_line(x,y,x,y-20);	
	x=centerRx+r*cos(cthetar);	
	y=centerRy+r*sin(cthetar)-1;
	gfx_color(255,255,255);
	gfx_line(x,y,x,y-20);
	if (cthetar<(30*torad)){
		contfour=1;
	}
}

//			//
//   AFTER RAMP FREE	//
//   STYLE IN AIR	//
//			//

if (contfour==1 && contfive==0){
	vy=vy+(gravity*dt);
        gfx_color(67,81,104);     // Background color
        gfx_line(x,y,x,y-20);	
	x=x+vx*dt;
	y=y+vy*dt;
	gfx_color(255,255,255);	
	gfx_line(x,y,x,y-20);
}

//					//
//  To End The Game			//
//					//
//   Ramp ends at x=729 and the 	//
//   landing strip starts at x=1100	//
//   At landing strip, y=473		//
//					//

if (x<1100 && y>480){
	gameover=1;
}
if (x>1100 && y>=473 && gameover==0){
        contfive==1;
	gfx_color(67,81,104);     // Background color
        gfx_line(x,y,x,y-20);
	x=x+vtot*dt;
	y=471;
	gfx_color(255,255,255);
	gfx_line(x,y,x,y-20);
	if (x>=1250){		// Ends game based on x
		gameover=1;
	}
}

gfx_flush();


usleep(dt*1000000);  // dt * 1000000 because usleep uses microseconds (1 us is 1e-6 s)

}  // close while loop of GAME, go back to where the user picks the V and G


} // close overarching while loop

return 0;
}  // close main function

