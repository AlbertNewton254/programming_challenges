/*
 * name		:	pg_02_minesweeper.c
 * author	:	miguel
 * description	:	given a minesweeper grid, calculates adjacent mines number for each cell and maps as a new grid
 * */

#include <stdio.h>

#define MAX_COLUMN 100	// max number of columns we will work with

/*
 * countAdjacentMines	:	function to print number of adjacent mines for a given cell in a Minesweeper grid
 * @param grid		:	2D array representing the minesweeper grid
 * @param rows		:	number of rows in the grid
 * @param cols		:	number of columns in the grid
 * @param row		:	the row index of the cell
 * @param col		:	the column index of the cell
 * @return		:	number of adjacent mines or minesweeper cell
 * */

int countAdjacentMines(char grid[][MAX_COLUMN], int rows, int cols, int row, int column)
{
	/* start count at 0 */
	int count = 0;

	/* we need to set all possible directions to be examinated */
	int directions[8][2] =
	{ {-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 1},
	{1, -1}, {1, 0}, {1, 1}
	};

	/* now we start checking for each direction */
	for (int i = 0 ; i < 8 ; i++)
	{
		int newRow = row + directions[i][0];
		int newCol = row + directions[i][1];

		/* validade whether we are within bounds */
		if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols)
		{
			/* if the cell contains a mine, add 1 to count */
			if (grid[newRow][newCol] == '*')
			{
				count++;
			}
		}
	};

	/* return count */
	return count;
}

/*
 * printMinesweeperGrid		:	function to print the minesweeper grid with adjacent mines counter
 * @param grid			:	2D array representing the minesweeper grid
 * @param rows			:	number of rows in the grid
 * @param cols			:	number of columns in the grid
 * @return			:	minesweeper grid w/ adjacent mines counter
 * */

int printMinesweeperGrid(int grid[][MAX_COLUMN], int rows, int cols)
{
	/* we will exhaust all grid cells through index numbers */
	for (int i = 0 ; i < rows ; i++)
	{
		for (int j = 0 ; j < cols ; j ++)
		{
			/* if the cell is a mine, print '*' */
			if (grid[i][j] == '*')
			{
				printf('*');
			}
			
			/* otherwise show adjacent mines counter */
			else
			{
				int count = countAdjacentMines(grid, rows, cols, i, j);
				printf("%d", count);
			}
		}
	}
}
