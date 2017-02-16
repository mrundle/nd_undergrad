/*
	Puzzle.cpp
*/
     
#include "Puzzle.h"

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
     
	// Initialize possibleValues
	vector<int> temp1D;
	vector< vector<int> > temp2D;
    for(int i=0;i<PUZZLE_SIZE;i++){
    	temp2D.push_back(temp1D);
	}
  	for(int i=0;i<PUZZLE_SIZE;i++){
    	possibleValues.push_back(temp2D);
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

int Puzzle::findPossible(int Y, int X){

	vector<int> impossible;
	
	// Check Horizontally
	for(int i=0;i<PUZZLE_SIZE;i++){
		if(Board[Y][i] > 0){
			impossible.push_back(Board[Y][i]);
		}
	}
	
	// Check Vertically
	for(int i=0;i<PUZZLE_SIZE;i++){
		if(Board[i][X] > 0){
			impossible.push_back(Board[i][X]);
		}
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
	
	if(Board[centerY][centerX] > 0) impossible.push_back(Board[Y][X]);
	if(Board[centerY][centerX-1] > 0) impossible.push_back(Board[Y][X]);
	if(Board[centerY][centerX+1] > 0) impossible.push_back(Board[Y][X]);
	if(Board[centerY+1][centerX] > 0) impossible.push_back(Board[Y][X]);
	if(Board[centerY+1][centerX-1] > 0) impossible.push_back(Board[Y][X]);
	if(Board[centerY+1][centerX+1] > 0) impossible.push_back(Board[Y][X]);	
	if(Board[centerY-1][centerX] > 0) impossible.push_back(Board[Y][X]);
	if(Board[centerY-1][centerX-1] > 0) impossible.push_back(Board[Y][X]);
	if(Board[centerY-1][centerX+1] > 0) impossible.push_back(Board[Y][X]);
	
	int Value;
	int counter = 0;
	// Remove impossible values from possible values
	bool possible;
	for(int i=1;i<=9;i++){
		possible = true;
		for(int j=0;j<impossible.size();j++){
			if(impossible[i] == i){
				possible = false;
			}
		}
		if(possible = true){
			Value = i;
			counter++;
		}
	}

	if(counter == 1){
		return Value;
	}else{
		return 0;
	}
}

void Puzzle::solve(){
	vector< vector<int> > mirrorBoard;
	int tries = 0;
	while(isComplete() == false){
	//while( !(Board == mirrorBoard) ){
		mirrorBoard = Board;
		for(int Y=0;Y<PUZZLE_SIZE;Y++){
			for(int X=0;X<PUZZLE_SIZE;X++){
				if(Board[Y][X] == 0){
					Board[Y][X] = findPossible(Y,X);
				}
			}
		}
	print();
	tries++;
	cout << tries << endl;
	}
}

void Puzzle::print(){

	for(int Y=0;Y<PUZZLE_SIZE;Y++){
		for(int X=0;X<PUZZLE_SIZE;X++){
			cout << Board[Y][X] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

}
