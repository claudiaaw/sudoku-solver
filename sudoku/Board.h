#pragma once
#include "Box.h"
#include <iostream>

class Board
{
public:
	Board(std::string filePath); // constructor
	~Board(); // deconstructor
	void printSudoku(void); // function to print the sudoku
	void solveSudoku(void);
private:
	Box m_grid[9][9];
	
	bool forward(int &row, int &col);
	void backward(int &row, int &col);
	bool inRow(int row, int column, int value);
	bool inCol(int row, int column, int value);
	bool inBox(int row, int column, int value);
	int checkSafe(int row, int column, int value);
	int isCompleted(void);
	//void fillIn(int row, int col);

};

