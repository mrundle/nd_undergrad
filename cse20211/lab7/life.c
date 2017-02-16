//**************************************//
//					//
// 	life.c				//
// 	Game of Life			//
// 	Created by Matt Rundle		//
// 	for cse20211.01			//
// 	Fall 2012			//
//					//
//**************************************//	

#include <stdio.h>
#include <unistd.h>
#define SIZE 40

// Populate board with spaces (for initial use)
void space_array(char array[][SIZE])
{
	int i,j;
	for(i=0;i<SIZE;i++){
	        for(j=0;j<SIZE;j++){
	                array[i][j]=' ';
	        }
	}
}

// Displays board 
void print_array(char array[][SIZE])
{
	int i,j;
	printf("\n ");
	for(i=0;i<SIZE;i++){
	        printf("%d\n",i);	
	        for(j=0;j<SIZE;j++){
	                printf(" %c",array[i][j]);
	        }
	}
	printf("\n\n");
}

// Collect input from user, output their choice
char collect_input(void)
{
	int choice;	
	// Ask user for input
        printf("\n\nEnter 'a' to add a new cell, 'r' to remove a cell,");
        printf(" 'n' to advance the simulation, 'p' to advance indefinitely,");
        printf(" or 'q' to quit: ");
        scanf("%d",&choice);
	return choice;
}

// Ask for coordinates where to add a new live cell, and add it
void choice_a(char array[][SIZE])
{
	int i,j;

	// Ask user for input
	printf("Enter coordinates for new live cell: ");
	scanf("%d %d",&i,&j);
	
	// Apply to board (make space occupied/alive)
	array[i][j]='X';
}

// Ask for coordinates where to remove a cell
void choice_r(char array[][SIZE])
{
	int i,j;
	
	// Ask user for input
	printf("Enter coordinates to remove cell: ");
	scanf("%d %d",&i,&j);

	// Apply to board (make space empty/dead)
	array[i][j]=' ';
}

// Copy one array to the other
void copy_array(char game_array[][SIZE],char array[][SIZE])
{
	int i,j;	
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			array[i][j]=game_array[i][j];
		}
	}
}

void life_rules(char array[][SIZE],char game_array[][SIZE], int i, int j)
{
	// Determine how many live cells surround the current cell
	int alive=0;  
	if((i-1)>=0 && (j-1)>=0 && array[i-1][j-1]=='X') alive++;
	if((i-1)>=0 && array[i-1][j]=='X') alive++;
	if((i-1)>=0 && (j+1)<=SIZE && array[i-1][j+1]=='X') alive++;
	if((j-1)>=0 && array[i][j-1]=='X') alive++;
	if((j+1)<=SIZE && array[i][j+1]=='X') alive++;
	if((i+1)<=SIZE && array[i+1][j-1]=='X') alive++;
	if((i+1)<=SIZE && array[i+1][j]=='X') alive++;
	if((i+1)<=SIZE && (j+1)<=SIZE && array[i+1][j+1]=='X') alive++;

	// Apply life rules based on number of adjacent live cells
	// Then assign "new" value to the separate array (game_array)	
	if(array[i][j]=='X'){	
		if(alive<2) game_array[i][j]=' ';
		if(alive==2 || alive==3) game_array[i][j]='X';
		if(alive>3) game_array[i][j]=' ';	
	}
	if(array[i][j]==' '){
		if(alive==3) game_array[i][j]='X';
	}
}

// Advance simulation one tick
void choice_n(char array[][SIZE],char game_array[][SIZE])
{
	int i,j;
	
	// Apply the rules of life to each piece on the board	
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			life_rules(array,game_array,i,j);
		}
	}

	// Copy the contents of game_array into array
	copy_array(game_array,array);
}

// Advance indefinitely
void choice_p(char array[][SIZE],char game_array[][SIZE])
{
	while(1){	// go forever
		choice_n(array,game_array);  	// advance one tick
		printf("\033[2J\033[H"); 	// clear screen
		print_array(array);		// print array
		usleep(500000);   		// pause between each tick
	}
}

// Apply action based on user input
int apply_action(char array[][SIZE],char game_array[][SIZE],char choice)
{

	switch(choice){
        	        case 'a':	//ask for coordinates for new live cell
				choice_a(array);
				break;
			case 'c':
				copy_array(array,array);
				break;
        	        case 'r':	//ask for coordinates to remove cell
				choice_r(array);
				break;
        	        case 'n':	//advance the simulation one tick
				choice_n(array,game_array);
				break;
        	        case 'p':	//advance indefinitely
				choice_p(array,game_array);
				break;
        	        case 'q':	//quit the program
				printf("\n");
				return 1;
	}
	return 0;
}


//******************************//
//				//
//	  Main Function		//
//				//
//******************************//

int main (void)
{

// Initialize arrays
char array[SIZE][SIZE];	      // this will be the main array, printed to screen
char game_array[SIZE][SIZE];  // this will be used to apply game rules

// Populate arrays with ' ' initially
space_array(array);
space_array(game_array);

// Print the blank array
print_array(array);

int gameover=0;  // this will determine whether or not the game is over
char choice;

while(gameover==0){
	// Prompt user for input and collect the input
	choice=collect_input();

	// Apply the action
	gameover=apply_action(array,game_array,choice);

	// Print the board	
	print_array(array);
}

return 0;
}













