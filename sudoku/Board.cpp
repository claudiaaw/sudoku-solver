#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Board.h"
#include <vector>

using namespace std;

Board::Board(std::string filePath)
{
	// open the file for reading
	ifstream fileObject(filePath);
	// if could not open the input file stream for reading
	if (!fileObject) {
		cerr << "File could not be opened" << endl;
		return;
	}

	int grid[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fileObject >> m_grid[i][j].number; // read from file and store in grid
			if (m_grid[i][j].number != 0) {
				m_grid[i][j].fixed = true;
			}
		}
	}
}

Board::~Board()
{
}

void Board::printSudoku() {
	printf("-------------------------------\n");
	for (int i = 0; i < 9; i++) {
		printf("|");
		for (int j = 0; j < 9; j++) {
			printf(" %d ", m_grid[i][j].number);
			if (((j + 1) % 3) == 0) {
				printf("|");
			}
		}
		printf("\n");
		if (((i + 1) % 3) == 0) {
			printf("-------------------------------\n");
		}
	}
}

void Board::solveSudoku(void) {
	// check if all the 0s have been placed with a number
	//if (isCompleted()) {
	//	return 1;
	//}
	int row = 0, col = 0;
	bool completed = false;
	while (!completed) {
		completed = forward(row, col);
		if (!completed) {
			backward(row, col); //puzzle failure handled in backwards
		}
	}
	// fill in the confirm is this solution de
	/*std::cout << "not completed" << std::endl;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			fillIn(row, col);
		}
	}*/
	printSudoku();
}

// change name
/*
void Board::fillIn(int row, int col) {
	std::cout << row << col << std::endl;
	int numbers[9] = { 0 };
	
	for (int val = 1; val <=9; val++) {
		if (inRow(row, col, val) || inCol(row, col, val) || inBox(row, col, val)) {
			numbers[val - 1] = 1;
		}
	}
	for (int i = 0; i < 9; i++) {
		std::cout << numbers[i];
	}
	std::cout << std::endl;
	
	int countPossiblities = 0, index = 0;
	for (int i = 0; i < 9; i++) {
		if (numbers[i] == 0) {
			countPossiblities++;
			index = i;
		}
	}
	if (countPossiblities == 1) {
		m_grid[row][col] = (index + 1);
		std::cout << "fill in " << (index + 1) << " at row " << row << " and col " << col << std::endl;
	}
}
*/
/* check if value is already in the row */
bool Board::inRow(int row, int column, int value) {
	for (int i = 0; i < 9; i++) { // loop through all columns
		if (m_grid[row][i].number == value) { // row stays constant
			return 1;
		}
	}
	return 0;
}

/* check if value is already in the column */
bool Board::inCol(int row, int column, int value) {
	for (int i = 0; i < 9; i++) { // loop throw all rows
		if (m_grid[i][column].number == value) { // column stays constant
			return 1;
		}
	}
	return 0;
}

/* check if value is already in the box */
// might shift to a class
bool Board::inBox(int row, int column, int value) {
	// if (5,5), startRow = 3, startCol = 3, 
	int startRow = row - row % 3;
	int startCol = column - column % 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (m_grid[i + startRow][j + startCol].number == value) {
				return 1;
			}
		}
	}
	return 0;
}

/* check if value is safe (not in row, column, box) */
int Board::checkSafe(int row, int column, int value) {
	if (!inRow(row, column, value) && !inCol(row, column, value) && !inBox(row, column, value)) {
		return 1;
	}
	return 0;
}

int Board::isCompleted() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (m_grid[i][j].number == 0) { // if any value still == 0
				return 0; // return not true
			}
		}
	}
	return 1;
}

bool Board::forward(int &row, int &col) {
//Function fills in blank boxes
//Function will move left to right, top to bottom
	//Keeps going as long as blank boxes are solvable
	//If blank box found to be unsolvable, exit this fn and call backwards()
	while (row != 9) {
		if (m_grid[row][col].number == 0){
			for (int i = 1; i <= 9; i++) {
				//loop to solve from 1 to 9
				bool clash = false;
				clash = inRow(row, col, i);
				if (clash){
					continue;
				}

				clash = false;
				clash = inCol(row, col, i);
				if (clash){
					continue;
				}

				clash = false;
				clash = inBox(row, col, i);

				if (!clash){
					m_grid[row][col].number = i;
					break; //breal checking 1 to 9
				}// end of 1 to 9 loop
			}
			//outside of 1 to 9 loop
			if (m_grid[row][col].number == 0) { //can use zero since fixed squares !=0 and answer squares == 0 if and only if for loop could not find ans
				return false; //impossible to fill square, break big while loop and go to backtrack
			}
			
		}//end of box is empty

		if (col == 8){
			col = 0;
			row++;
		}
		else {
			col++;
		}
	}	//end of while row != 9
	return true;
}

void Board::backward(int &row, int &col) {
	//decrement to avoid double checking
	if (col == 0) {
		col = 8;
		row--;
	}
	else {
		col--;
	}

	while (row != -1) {
		if (!m_grid[row][col].fixed) {
			int temp = m_grid[row][col].number;
			m_grid[row][col].number = 0; // set to zero
			for (int i = ++temp; i <= 9; i++) { // ++temp = 1+temp
				//loop to solve from next number (i+temp) to 9
				bool clash = false;
				clash = inRow(row, col, i);
				if (clash) {
					continue;
				}

				clash = false;
				clash = inCol(row, col, i);
				if (clash) {
					continue;
				}

				clash = false;
				clash = inBox(row, col, i);

				if (!clash) {
					m_grid[row][col].number = i;
					return; //continue going forward
				}// end of 1 to 9 loop
			}


		}//end of not fixed

		if (col == 0) {
			col = 8;
			row--;
		}
		else {
			col--;
		}
	}	//end of while row != -1, sudoku cannot be solved
	std::cout << "sudoku not solvable" << std::endl;
	exit(EXIT_FAILURE);
	//system exit failure
}