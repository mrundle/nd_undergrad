//******************************//
//				//
//	crossword.c		//
//	Matthew Rundle		//
//	cse20211.01		//
//				//
//******************************//


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define SIZE 15


// Populate a board with "empty" spaces of the period character
void populate_empty(char board[][SIZE])
{
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			board[i][j]='.';
		}
	}
}


// Displays board 
void print_array(char array[][SIZE])
{
	int i,j;
	printf("\n ");
	for(i=0;i<SIZE;i++){
	        printf("\n       ",i);	
	        for(j=0;j<SIZE;j++){
	                printf(" %c",array[i][j]);
	        }
	}
	printf("\n\n");
}


// Prints the crossword
void print_crossword(char array[][SIZE])
{
int i,j;
	printf("\n ");
	for(i=0;i<SIZE;i++){
	        printf("\n       ",i);	
	        for(j=0;j<SIZE;j++){
			if (array[i][j]=='.') printf(" #");
			if (array[i][j]!='.') printf("  ");
	        }
	}
	printf("\n\n");
}


// Copy one array to the other
void copy_array(char from[][SIZE],char to[][SIZE])
{
	int i,j;	
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			to[i][j]=from[i][j];
		}
	}
}


// Prompt the user for a list of words up to 20 words, 15 characters long 
int user_wordlist(char words[20][15])
{
	printf("\n\nAnagram Crossword Puzzle Generator\n");
	printf("----------------------------------");
	printf("\n\nEnter a list of words:\n\n");
	int i;
	int word_number=0;
	for(i=0;i<20;i++){
		scanf("%s",words[i]);
		if(*words[i] == '.'){
			break;
		}
		word_number++;
	}
	return word_number;
	// HOW TO PRINT printf("\n\n%s\n\n",&list[0]);
}


void place_longest(char * list[20],char board[][SIZE],int coordinates[][3])
{
	// longest word should be first in list
	// place in the 7th row
	int i=(SIZE/2)-(strlen(list[0])/2);
	int max=i+strlen(list[0]);
	int j=0;
	// Set coordinates for first element
	coordinates[0][0]=SIZE/2;
	coordinates[0][1]=i;
	coordinates[0][2]=1; // 1 means RIGHT
	for(i;i<max;i++){
		board[SIZE/2][i]=*(list[0]+(j++));
	}
}


// Check empties down and right ** TWO FUNCTIONS ** (see if there is a space between other words on board)
int check_empties_down(char board[][SIZE],char check_board[][SIZE],char * word, int i,int j)
{
	int c;
	int valid=0;
	// Keep it from attaching to another word
	if(board[i-1][j]!='.') return 0;
	if(board[i+strlen(word)][j]!='.') return 0;
	// Now check the empties to see if valid
	for(c=0;c<strlen(word);c++){
		int empty=0;		
		if(board[i+c][j-1]=='.') empty++;
		if(board[i+c][j+1]=='.') empty++;
 		if(empty==2) valid++; 
	}
	// word is valid if it contains all valid letters except for 1 (intersecting word)	
	if(valid==(strlen(word)-1)) return 1;
	// else the word is not valid
	return 0;
}
int check_empties_right(char board[][SIZE],char check_board[][SIZE],char * word, int i,int j)
{
	int c;
	int valid=0;
	// Keep it from attaching to the end of a word
	if(board[i][j-1]!='.') return 0;
	if(board[i][j+strlen(word)]!='.') return 0;
	// Now check the empties to see if valid
	for(c=0;c<strlen(word);c++){
		int empty=0;				
		if(board[i-1][j+c]=='.') empty++;
		if(board[i+1][j+c]=='.') empty++;
 		if(empty==2) valid++; 
	}
	// word is valid if it contains all valid letters except for 1 (intersecting word)
	if(valid==(strlen(word)-1)) return 1;
	// else the word is not valid
	return 0;
}


// Check to see if boards match in exactly one place
int check_boards(char board[][SIZE],char check_board[][SIZE])
{
	int i,j;
	int match=0;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(board[i][j]==check_board[i][j] && check_board[i][j]!='.') match++;
			if(board[i][j]!='.' && check_board[i][j]!='.' && board[i][j]!=check_board[i][j]) return 0;		
		}
	}
	if(match!=1) return 0;
	if(match==1){
		return 1;
	}
}


// Brute force the board to find a fit
int place_board(char * word,char board[][SIZE],int coordinates[][3],int element_num)
{
	int i,j,c;
	int match,valid;
	// create a test board and empty it out
	char check_board[SIZE][SIZE];

	// Matches reading right
	for(i=0;i<SIZE;i++){
		for(j=0;j<=(SIZE-strlen(word));j++){
			// empty test board
			populate_empty(check_board);
			// add word to test board			
			for(c=0;c<strlen(word);c++){
				check_board[i][j+c]=*(word+c);
			}
			// check to see if there is exactly one match and that it has a space between other words
			match=check_boards(board,check_board); 
			valid=check_empties_right(board,check_board,word,i,j);		
			if(match==1){
				if(valid==1){
					// store coordinates of first element
					coordinates[element_num][0]=i;
					coordinates[element_num][1]=j;
					coordinates[element_num][2]=1; // 1 means RIGHT
					// add string onto board
					for(c=0;c<strlen(word);c++){
						board[i][j+c]=*(word+c);
					}
					return 1;			
				}
			}		
		}
	}
	// Matches reading down
	for(j=0;j<SIZE;j++){
		for(i=0;i<=(SIZE-strlen(word));i++){
			// empty test board
			populate_empty(check_board);
			// add word to test board			
			for(c=0;c<strlen(word);c++){
				check_board[i+c][j]=*(word+c);
			}
			// check to see if there is exactly one match and that it is has a space between other words			
			match=check_boards(board,check_board);
			valid=check_empties_down(board,check_board,word,i,j); 
			if(match==1){
				if(valid==1){
					// store coordinates of first element
					coordinates[element_num][0]=i;
					coordinates[element_num][1]=j;
					coordinates[element_num][2]=0; // 0 means down
					// add string onto board
					for(c=0;c<strlen(word);c++){
						board[i+c][j]=*(word+c);
					}
					return 1;			
				}			
			}
		}
	}
	return 0;

}


// Place rest of the words (2nd through last)
int place_words(char * list[20],char board[][SIZE],int word_number,int coordinates[][3])
{
	int c,i,j;
	int placed=1; // the first word has already been placed
	for(i=1;i<word_number;i++){
		placed+=place_board(list[i],board,coordinates,i);
	}
	return placed; 
}


// Change all to capital letters
void change_caps(char words[20][15],int word_number)
{
	int i,j;
	for(i=0;i<word_number;i++){
		for(j=0;j<strlen(words[i]);j++){
			words[i][j]=toupper(words[i][j]);
		}
	}
}


// Sort the words in order of descending length
void sort_words(char * list[20], int word_number)
{
	int i,j;
	char * temp;
	for(j=0;j<word_number;j++){
		for(i=0;i<(word_number-1);i++){
			if(strlen(list[i]) < strlen(list[i+1])){			
				temp=list[i+1];
				list[i+1]=list[i];
				list[i]=temp;
			}
		}
	}
}

// Print the clues
void print_clues(char * list[20],int coordinates[][3],int placed)
{
	int c;
	for(c=0;c<placed;c++){
		printf("%2d,%2d",coordinates[c][1],coordinates[c][0]);
		if(coordinates[c][2]==0) printf(" Down  :");
		if(coordinates[c][2]==1) printf(" Across:");
		strfry(list[c]);
		printf(" %s\n",list[c]);
	}
}




//**************************************//
//					//
//	MAIN FUNCTION			//
//					//
//**************************************//

int main(void)
{

int i,j;
// Populate list of words (up to 20 words, 15 characters long)
// and a pointer to those words
char words[20][15];

// Prompt user for input, return number of words
int word_number;
word_number=user_wordlist(words);

// Convert to upper case
change_caps(words,word_number);

// Create array of pointers to our words
char * list[20];
	for(i=0;i<word_number;i++){
		list[i]=words[i];
	}

// Put words in descending order of length
sort_words(list,word_number);

// create 15x15 board, populate with spaces
char board[SIZE][SIZE];
populate_empty(board);

// create an array for coordinates of sorted word list
int coordinates[word_number][3];

// Place longest word in middle of board, then place the rest
// If not all words are able to be matched, tell user
place_longest(list,board,coordinates);
int placed;
placed=place_words(list,board,word_number,coordinates);
if(placed<word_number) printf("\nNot able to fit all words. Approximate puzzle will be printed.\n");

// Print solution
printf("\nSolution:");
print_array(board);

// Print crossword puzzle
printf("Crossword Puzzle:");
print_crossword(board);

// Print clues
printf("Hints:\n\n");
print_clues(list,coordinates,placed);
printf("\n");

return 0;
}
