/*
 * nqueens.cpp
 *
 *  Created on: Feb, 2012
 *      Author: Ahmed Fakhry
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;

bool isPositionValid(int rowCount, int columnCount, vector<int>& state)
{
	//check rows conflict
	//I'm sure that there isn't any column conflict because I'm filling column by column,
	//and rightnow, my column is empty
	for (int i = 0; i < columnCount; i++)
	{
		if (state[i] == rowCount)
			return false;
	}
	//Now I need to check for diagonal conflict
	int colDiff = 0;
	int rowDiff = 0;
	for (int i = 0; i < columnCount; i++)
	{
		colDiff = abs(columnCount - i);
		rowDiff = abs(rowCount - state[i]);
		if (colDiff == rowDiff)
			return false;
	}

	//if it passed the above tests, then return true
	return true;
}

int main(int argc, char * argv[])
{
	int n;
	if (argc != 2)
	{
		cout << "Usage: nqueens n, where n is the size of the n x n chess board." << endl;
		cout << "n must be an integer greater than 3." << endl;
		exit(0);
	}
	else
	{
		if ((n = atoi(argv[1])) <= 3)
		{
			cout << "n must be an integer greater than 3." << endl;
			exit(0);
		}
	}

	vector<int> state;
	state.resize(n);
	int columnCount = 0;
	int rowCount = 0;

	bool backtracking = false;

	while (columnCount < n)
	{
		while (rowCount < n)
		{
			if (backtracking)
			{
				rowCount = state[columnCount] + 1;
				//if it's the last row, then we have to back track more
				if (rowCount == n)
				{
					columnCount--; //backtrack more
					backtracking = true;
					rowCount = 0;
					break;
				}
				backtracking = false;
			}
			if (isPositionValid(rowCount, columnCount, state))
			{
				state[columnCount] = rowCount;
				rowCount = 0;
				columnCount++; //advancing
				backtracking = false;
				break;
			}
			else
			{
				if (rowCount == (n - 1))
				{
					columnCount--; //backtracking
					backtracking = true;
					rowCount = 0;
				}
				else
				{
					rowCount++;
				}
			}
		}
	}

	//output the state array
	cout << endl << endl << "Solution is : [ ";
	for (int i = 0; i < n; i++)
	{
		cout << state[i] << " ";
	}
	cout << "]" << endl << endl << endl;

	return 0;
}
