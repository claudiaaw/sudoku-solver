// sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Board.h"

using namespace std;

int main()
{
	Board sudokuBoard("sudoku.txt");
	sudokuBoard.printSudoku();
	sudokuBoard.solveSudoku();
}

