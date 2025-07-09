/**
 * @file pg_01_02_minesweeper.c
 * @author Miguel
 * @brief Displays a Minesweeper grid where non-mine cells show the count of adjacent mines.
 *
 * This program processes a Minesweeper grid represented as a 2D character array.
 * Mines are marked with '*', and empty cells are marked with '.'. The output replaces
 * each empty cell with the number of adjacent mines.
 */

#include <stdio.h>

#define MAX_COLUMN 100  ///< Maximum number of columns in the grid
#define MINE '*'
#define EMPTY '.'

/**
 * @brief Counts the number of adjacent mines around a specific cell.
 *
 * Checks all 8 neighboring cells (diagonals included) and counts how many contain mines.
 *
 * @param grid 2D array representing the Minesweeper grid.
 * @param rows Total number of rows in the grid.
 * @param cols Total number of columns in the grid.
 * @param row Row index of the target cell.
 * @param col Column index of the target cell.
 * @return Number of adjacent mines.
 */
int count_adjacent_mines(char grid[][MAX_COLUMN], int rows, int cols, int row, int col) {
    int count = 0;

    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int new_row = row + directions[i][0];
        int new_col = col + directions[i][1];

        if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols) {
            if (grid[new_row][new_col] == MINE) {
                count++;
            }
        }
    }

    return count;
}

/**
 * @brief Prints the Minesweeper grid with adjacent mine counts.
 *
 * Replaces empty cells with the number of adjacent mines. Mines remain unchanged.
 *
 * @param grid 2D array representing the Minesweeper grid.
 * @param rows Number of rows in the grid.
 * @param cols Number of columns in the grid.
 */
void print_minesweeper_grid(char grid[][MAX_COLUMN], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == MINE) {
                printf("%c", MINE);
            } else {
                int count = count_adjacent_mines(grid, rows, cols, i, j);
                printf("%d", count);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Entry point of the program.
 *
 * Demonstrates the Minesweeper grid transformation with a sample 3x3 grid.
 *
 * @return Exit status code.
 */
int main(void) {
    char grid[3][MAX_COLUMN] = {
        {MINE, EMPTY, EMPTY},
        {EMPTY, MINE, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    print_minesweeper_grid(grid, 3, 3);

    return 0;
}