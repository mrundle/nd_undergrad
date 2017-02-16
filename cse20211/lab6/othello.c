//******************************//
//				//
//      othello.c		//
// 	Game created by 	//
// 	Matthew Rundle		//
// 	for cse20211.01		//
// 	Fall 2012		//
//				//
//******************************//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BOARD_SIZE 8

// Displays board (pass the board array in, print it)
void print_board(char board[][BOARD_SIZE])
{
int i,j;
printf("\n ");
for(i=0;i<BOARD_SIZE;i++){
	printf(" %d",i);
}
for(i=0;i<BOARD_SIZE;i++){
	printf("\n%d",i);
	for(j=0;j<BOARD_SIZE;j++){
		printf(" %c",board[i][j]);
	}
}
printf("\n\n");
}

// Check right and flip
void flip_right(char board[][BOARD_SIZE],int i,int j,char player)
{

	int flip,flipright,c;
	// Check to see if there is another piece of same type to the right
	for(c=j+1;c<=BOARD_SIZE;c++){
		if(board[i][c]==player){
			flipright=1;
		}
		if(board[i][c]=='.') break;
	}
	// If so, flip each token until you get to another similar one
	flip=j+1;
	while(flipright==1){
		if(board[i][flip]==player || board[i][flip]=='.'){
			flipright=0;
			continue;
		}
		board[i][flip]=player;
		flip++;
	}
	return;
}

// Check left and flip
void flip_left(char board[][BOARD_SIZE],int i,int j,char player)
{
	int flip,flipleft,c;
	for(c=j-1;c>=0;c--){
		if(board[i][c]==player){
			flipleft=1;
		}
		if(board[i][c]=='.') break;
	}
	flip=j-1;
	while(flipleft==1){
		if(board[i][flip]==player || board[i][flip]=='.'){
			flipleft=0;
			continue;
		}
		board[i][flip]=player;
		flip--;	
	}	
	return;
}

// Check up and flip 
void flip_up(char board[][BOARD_SIZE],int i,int j,char player)
{

	int flip,flipup,c;
	// Check to see if there is another piece of same type above
	for(c=i+1;c<=BOARD_SIZE;c++){
		if(board[c][j]==player){
			flipup=1;
		}
		if(board[c][j]=='.') break;
	}
	// If so, flip each token until you get to another similar one
	flip=i+1;
	while(flipup==1){
		if(board[flip][j]==player || board[flip][j]=='.'){
			flipup=0;
			continue;
		}
		board[flip][j]=player;
		flip++;
	}
	return;
}

// Check down and flip
void flip_down(char board[][BOARD_SIZE],int i,int j,char player)
{
	int flip,flipdown,c;
	// Check to see if there is another piece of same type above
	for(c=i-1;c>=0;c--){
		if(board[c][j]==player){
			flipdown=1;
		}
		if(board[c][j]=='.') break;
	}
	// If so, flip each token until you get to another similar one
	flip=i-1;
	while(flipdown==1){
		if(board[flip][j]==player || board[flip][j]=='.'){
			flipdown=0;
			continue;
		}
		board[flip][j]=player;
		flip--;
	}
	return;
}

// Check diagonals up and to the right
void flip_diag_up_right(char board[][BOARD_SIZE],int i,int j,char player)
{
	int flip,flipgo,c;
	// Check to see if there is another piece of same type diagonal
	for(c=1;c<BOARD_SIZE;c++){
		if(board[i-c][j+c]==player){
			flipgo=1;
			break;
		}
		if(board[i-c][j+c]=='.') break;
	}
	// If so, flip each token until you get to another similar one
	flip=1;
	while(flipgo==1){
		if(board[i-flip][j+flip]==player || board[i-flip][j+flip]=='.'){
			flipgo=0;
			continue;
		}
		board[i-flip][j+flip]=player;
		flip++;
	}
	return;
}

// Check diagonals down and to the left
void flip_diag_down_left(char board[][BOARD_SIZE],int i,int j,char player)
{
	int flip,flipgo,c;
	// Check to see if there is another piece of same type diagonal
	for(c=1;c<BOARD_SIZE;c++){
		if(board[i+c][j-c]==player){
			flipgo=1;
			break;
		}
		if(board[i+c][j-c]=='.') break;
	}	
	// If so, flip each token until you get to another similar one
	flip=1;
	while(flipgo==1){
		if(board[i+flip][j-flip]==player || board[i+flip][j-flip]=='.'){
			flipgo=0;
			continue;
		}
		board[i+flip][j-flip]=player;
		flip++;
	}
	return;
}

// Check diagonals up and to the left 
void flip_diag_up_left(char board[][BOARD_SIZE],int i,int j,char player)
{
	int flip,flipgo,c;
	// Check to see if there is another piece of same type diagonal
	for(c=1;c<BOARD_SIZE;c++){
		if(board[i-c][j-c]==player){
			flipgo=1;
			break;
		}
		if(board[i-c][j-c]=='.') break;
	}
	// If so, flip each token until you get to another similar one
	flip=1;
	while(flipgo==1){
		if(board[i-flip][j-flip]==player || board[i-flip][j-flip]=='.'){
			flipgo=0;
			continue;
		}
		board[i-flip][j-flip]=player;
		flip++;
	}
	return;
}

// Check diagonals down and to the right 
void flip_diag_down_right(char board[][BOARD_SIZE],int i,int j,char player)
{
	int flip,c;
	int flipgo=0;
	// Check to see if there is another piece of same type diagonal
	for(c=1;c<BOARD_SIZE;c++){
		if(board[i+c][j+c]==player){
			flipgo=1;
			break;
		}
		if(board[i+c][j+c]=='.') break;
	}
	// If so, flip each token until you get to another similar one
	flip=1;
	while(flipgo==1){
		if(board[i+flip][j+flip]==player || board[i+flip][j+flip]=='.'){
			flipgo=0;
			continue;
		}
		board[i+flip][j+flip]=player;
		flip++;
	}
	return;
}


// Check adjacency (DETERMINES VALID MOVE)
int adjacent(char board[][BOARD_SIZE],int i, int j){
	if(board[i-1][j-1]=='.' && board[i-1][j]=='.' && board[i-1][j+1]=='.' && 
	   board[i+1][j-1]=='.' && board[i+1][j]=='.' && board[i+1][j+1]=='.' &&
	   board[i][j-1]=='.' && board[i][j+1]=='.'){
		return 0;  // Piece is not adjacent to another on the board
	}else{
		return 1;  // Piece is indeed adjacent to another on the board 
	}
}

// Take input from player, apply changes to board
void take_input(char board[][BOARD_SIZE],char player)
{
	int i,j;
	int valid_move=0;
	
	// Take input and check for valid move
	while(valid_move==0){
		printf("Player %c moves: ",player);
		// This collects the input and checks for validity
		scanf("%d %d",&i,&j);
		if(board[i][j] != '.'){
			printf("\nNot a valid move.\n");
			continue;
		}
		if(i<0 || i>BOARD_SIZE){
			printf("\nNot a valid move.\n");
			continue;
		}
		if(j<0 || j>BOARD_SIZE){
			printf("\nNot a valid move.\n");
			continue;
		}
		int adj=adjacent(board,i,j);
		if(adj==0){
			printf("\nNot a valid move.\n");
			continue;
		}	
	valid_move=1;  // If valid, move out of loop
	}

	// Assign choice to board
	board[i][j]=player;

	// Flip pieces
        if(j>0) flip_left(board,i,j,player);
	if(j<BOARD_SIZE) flip_right(board,i,j,player);
	if(i>0) flip_down(board,i,j,player);
	if(i<BOARD_SIZE) flip_up(board,i,j,player);
	if(i>0 && j<BOARD_SIZE) flip_diag_up_right(board,i,j,player);
	if(i<BOARD_SIZE && j>0) flip_diag_down_left(board,i,j,player);
	if(i>0 && j>0) flip_diag_up_left(board,i,j,player);
	if(i<BOARD_SIZE && j<BOARD_SIZE) flip_diag_down_right(board,i,j,player);
}

// Check if game is over and tally score
int check_gameover(char board[][BOARD_SIZE])
{
	// Initialize loop variables
	int i,j;
	// Initialize scores
	int x_score=0;
	int o_score=0;

	for(i=0;i<BOARD_SIZE;i++){
		for(j=0;j<BOARD_SIZE;j++){
			switch(board[i][j]){
				case 'X':
					x_score++;
					break;
				case 'O':
					o_score++;
					break;
				case '.':
					return 0;
			}
		}
	}
	if(x_score==o_score){
		printf("\n\nThe game is a tie. Both players had %d points.\n\n",x_score); 
	}
	if(x_score>o_score){
		printf("\n\nPlayer X is the game winner, beating player O %d points to %d.\n\n",x_score,o_score);
	}
	if(o_score>x_score){
		printf("\n\nPlayer O is the game winner, beating player X %d points to %d.\n\n",o_score,x_score);
	}
	return 1;
}			



//***************************//
//       MAIN FUNCTION       //
//***************************//

int main(void)
{

    int i,j;
    char board[BOARD_SIZE][BOARD_SIZE];
printf("1\n"); // debug

    //Populate array with '.'
    for(i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            board[i][j]='.';
        }
    }

    //Set initial pieces
    board[3][3]='X';
    board[3][4]='O';
    board[4][3]='O';
    board[4][4]='X';

    // Initialize variables
    int gameover=0;
    char player='O';

    // Print initial board
    print_board(board);

    // Run the game
    while(gameover==0){
        // Each loop through, player switches
        if(player=='O'){
            player='X';
        }else{
            player='O';
        }

        // Take input from player, and apply changes to board
        take_input(board,player);			

        // Print the board
        print_board(board);

        gameover=check_gameover(board);
    }
    return 0;
}
