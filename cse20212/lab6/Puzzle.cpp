/*
	Puzzle.cpp
*/
     
#include "Puzzle.h"

Puzzle::Puzzle(){}

Puzzle::Puzzle(char* filename){

	std::ifstream inData;
    int num;
     
    inData.open(filename);
		if(!inData){
        	std::cerr << "Error loading file." << std::endl;
            exit(1);
		}
     
	int row = 0;
   	for(int Y=0;Y<PUZZLE_SIZE;Y++) {
    	std::vector<int> row; // create an empty row
        for(int X=0;X<PUZZLE_SIZE;X++) {
        	inData >> num;
            row.push_back(num);
        }
        Board.push_back(row);
	}
    inData.close();
     
	// Initialize empty possibleValues
	vector<int> temp1D;
	vector< vector<int> > temp2D;
    for(int i=0;i<PUZZLE_SIZE;i++){
    	temp2D.push_back(temp1D);
	}
  	for(int i=0;i<PUZZLE_SIZE;i++){
    	possibleValues.push_back(temp2D);
	}
	// Fill possible values 1-9
	for(int Y=0;Y<PUZZLE_SIZE;Y++){
		for(int X=0;X<PUZZLE_SIZE;X++){
			for(int i=1;i<=9;i++){
				possibleValues[Y][X].push_back(i);
			}
		}
	}
}

bool Puzzle::isComplete(){
	for(int Y=0;Y<PUZZLE_SIZE;Y++){
		for(int X=0;X<PUZZLE_SIZE;X++){
			if(Board[Y][X] == 0) return false;
		}
	}
	return true;
}

bool Puzzle::isPossible(int Y, int X, int z){
	
	// Check Horizontally
	for(int i=0;i<PUZZLE_SIZE;i++){
		if(Board[Y][i] == z) return false;
	}
	
	// Check Vertically
	for(int i=0;i<PUZZLE_SIZE;i++){
		if(Board[i][X] == z) return false;
	}
	
	// Check 3x3 tile from middle
	int centerX;
	if( (X >= 0) && (X <= 2) ) centerX=1;
	if( (X >= 3) && (X <= 5) ) centerX=4;
	if( (X >= 6) && (X <= 8) ) centerX=7;
	int centerY;
	if( (Y >= 0) && (Y <= 2) ) centerY=1;
	if( (Y >= 3) && (Y <= 5) ) centerY=4;
	if( (Y >= 6) && (Y <= 8) ) centerY=7;
	if(Board[centerY][centerX] == z) return false;
	if(Board[centerY][centerX-1] == z) return false;
	if(Board[centerY][centerX+1] == z) return false;
	if(Board[centerY+1][centerX] == z) return false;
	if(Board[centerY+1][centerX-1] == z) return false;
	if(Board[centerY+1][centerX+1] == z) return false;	
	if(Board[centerY-1][centerX] == z) return false;
	if(Board[centerY-1][centerX-1] == z) return false;
	if(Board[centerY-1][centerX+1] == z) return false;
	
	// Return true if not false lolz
	return true;
}

/*
	loop through this->board find 0
*/
void Puzzle::findGuess(int & guessY,int & guessX){
	for(guessY=0;guessY<PUZZLE_SIZE;guessY++){
		for(guessX=0;guessX<PUZZLE_SIZE;guessX++){
			if(this->Board[guessY][guessX] == 0) return;
		}
	}
}

/*
	loop through board and find if any 0's have no possibilities
*/
int Puzzle::badGuess(){
	for(int Y=0;Y<PUZZLE_SIZE;Y++){
		for(int X=0;X<PUZZLE_SIZE;X++){
			if(this->Board[Y][X] == 0){
				if(this->possibleValues[Y][X].size() == 0) return 0;
			}
		}
	}
	return 1;
}


/*
	Solves the sudoku puzzle
*/
int Puzzle::solve(){

	while(this->isComplete() == false){

		// Fill in as many singletons as possible
		vector< vector<int> > mirrorBoard;
		while( !(this->Board == mirrorBoard) ){
			mirrorBoard = this->Board;
			for(int Y=0;Y<PUZZLE_SIZE;Y++){
				for(int X=0;X<PUZZLE_SIZE;X++){
					if(this->Board[Y][X] == 0){
						vector<int>::iterator i;
						for(i=this->possibleValues[Y][X].begin();i!=this->possibleValues[Y][X].end();i++){
							if(this->isPossible(Y,X,*i) == false){
								this->possibleValues[Y][X].erase(i);
								i--;
							}
						}
						if(this->possibleValues[Y][X].size() == 1){
							this->Board[Y][X]=possibleValues[Y][X][0];
							this->possibleValues[Y][X].pop_back();
						}
					}
				}
			}
		}

		// If solved, print and return
		if(this->isComplete()){
			cout << "Solved:\n" << endl;
			print();
			return 1;
		}

		// Guess and recursively solve the board
		int possibleCount = 0;
		while(1){
			//check Board to make sure there are no 0's with no possible values
			if(this->badGuess() == 0) return 0;

			// instantiate a "Guess" board
			Puzzle Guess;
			Guess.Board = this->Board;
			Guess.possibleValues = this->possibleValues;

			//Loop through Guess board and find the first 0
			int guessY,guessX;
			Guess.findGuess(guessY,guessX);

			//Guess the first from possible values at that coordinate
			Guess.Board[guessY][guessX] = Guess.possibleValues[guessY][guessX][possibleCount];

			// call solve recursively
			if(Guess.solve() == 1){
				this->Board = Guess.Board;
				return 1;
				cout << "1" << endl;
			}else{
				possibleCount++; // try the next possible value
				cout << "2" << endl;
				if(possibleCount >= 8) return 0;
			}
		}

	} // ends the big while loop

	return 1;
}


/*
	Prints a sudoku puzzle
*/
void Puzzle::print(){

	for(int Y=0;Y<PUZZLE_SIZE;Y++){
		if((Y==3) || (Y==6)){
			cout << "- - - | - - - | - - -" << endl;
		}
		for(int X=0;X<PUZZLE_SIZE;X++){
			if((X==2) || (X==5)){
				cout << Board[Y][X] << " | ";
			}else{
				cout << Board[Y][X] << " ";
			}
		}
		cout << "\n";
	}
	cout << "\n";
}
