#include <stdio.h>

#define MAX_COLUMN 100
#define MINE '*'
#define EMPTY '.'

// Directions around a cell — global const to avoid repeated creation
const int directions[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{ 0, -1},          { 0, 1},
	{ 1, -1}, { 1, 0}, { 1, 1}
};

// Counts mines around (row, col) in grid
int count_adjacent_mines(char grid[][MAX_COLUMN], int rows, int cols, int row, int col) {
	int count = 0;

	for (int i = 0; i < 8; i++) {
		int r = row + directions[i][0];
		int c = col + directions[i][1];

		if (r >= 0 && r < rows && c >= 0 && c < cols) {
			if (grid[r][c] == MINE) {
				count++;
			}
		}
	}

	return count;
}

// Creates a solved board in 'output' based on input 'grid'.
// Mines stay '*', empty cells become count chars ('0' to '8').
void solve_minesweeper(char input[][MAX_COLUMN], char output[][MAX_COLUMN], int rows, int cols) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (input[r][c] == MINE) {
				output[r][c] = MINE;
			} else {
				int count = count_adjacent_mines(input, rows, cols, r, c);
				output[r][c] = '0' + count; // convert number to char
			}
		}
	}
}

// Prints any grid of chars with given dimensions.
void print_grid(char grid[][MAX_COLUMN], int rows, int cols) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			printf("%c", grid[r][c]);
		}
		printf("\n");
	}
}

int main(void) {
	char input[3][MAX_COLUMN] = {
		{MINE, EMPTY, EMPTY},
		{EMPTY, MINE, EMPTY},
		{EMPTY, EMPTY, EMPTY}
	};
	
	char solved[3][MAX_COLUMN];

	solve_minesweeper(input, solved, 3, 3);
	print_grid(solved, 3, 3);

	return 0;
}

