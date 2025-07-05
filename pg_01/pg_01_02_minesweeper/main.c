/**
 * @file pg_02_minesweeper.c
 * @author miguel
 * @brief Given a minesweeper grid, calculates the number of adjacent mines for each cell
 * and maps it into a new grid representation.
 */

#include <stdio.h>

#define MAX_COLUMN 100	///< Max number of columns allowed

/**
 * @brief Counts the number of adjacent mines around a specific cell in the grid.
 *
 * @param grid 2D array representing the minesweeper grid.
 *             Cells with mines are marked with '*'.
 * @param rows Number of rows in the grid.
 * @param cols Number of columns in the grid.
 * @param row The row index of the cell to check.
 * @param col The column index of the cell to check.
 * @return Number of adjacent mines around the specified cell.
 */
int countAdjacentMines(char grid[][MAX_COLUMN], int rows, int cols, int row, int col)
{
	int count = 0;

	int directions[8][2] =
	{
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1},           {0, 1},
		{1, -1},  {1, 0},  {1, 1}
	};

	for (int i = 0; i < 8; i++)
	{
		int newRow = row + directions[i][0];
		int newCol = col + directions[i][1]; // Corrigido: aqui era 'row + ...', virou 'col + ...'

		if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols)
		{
			if (grid[newRow][newCol] == '*')
			{
				count++;
			}
		}
	}

	return count;
}

/**
 * @brief Prints the minesweeper grid with counts of adjacent mines for non-mine cells.
 *
 * @param grid 2D array representing the minesweeper grid.
 * @param rows Number of rows in the grid.
 * @param cols Number of columns in the grid.
 */
void printMinesweeperGrid(char grid[][MAX_COLUMN], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[i][j] == '*')
			{
				printf("*");
			}
			else
			{
				int count = countAdjacentMines(grid, rows, cols, i, j);
				printf("%d", count);
			}
		}
		printf("\n"); // Para quebrar a linha depois de cada linha da grade
	}
}

