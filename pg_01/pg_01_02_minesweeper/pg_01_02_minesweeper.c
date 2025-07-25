#include <stdio.h>

#define MAX_COLUMN 100
#define MINE '*'
#define EMPTY '.'

static const int DIRECTIONS[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
};

static int count_adjacent_mines(const char grid[][MAX_COLUMN], 
                               int rows, int cols, 
                               int row, int col) {
    int count = 0;

    for (int i = 0; i < 8; i++) {
        const int r = row + DIRECTIONS[i][0];
        const int c = col + DIRECTIONS[i][1];

        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            count += (grid[r][c] == MINE);
        }
    }

    return count;
}

static void solve_minesweeper(const char input[][MAX_COLUMN], 
                             char output[][MAX_COLUMN], 
                             int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            output[r][c] = (input[r][c] == MINE) 
                ? MINE 
                : '0' + count_adjacent_mines(input, rows, cols, r, c);
        }
    }
}

static void print_grid(const char grid[][MAX_COLUMN], int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            putchar(grid[r][c]);
        }
        putchar('\n');
    }
}

int main(void) {
    const char input[3][MAX_COLUMN] = {
        {MINE, EMPTY, EMPTY},
        {EMPTY, MINE, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };
    
    char solved[3][MAX_COLUMN];

    solve_minesweeper(input, solved, 3, 3);
    print_grid(solved, 3, 3);

    return 0;
}
