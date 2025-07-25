#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define BOARD_SIZE 8
#define LINE_BUFFER 10 // 8 chars + newline + null terminator

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE + 1]; // +1 for null terminator
    int black_king_x, black_king_y;
    int white_king_x, white_king_y;
} ChessBoard;

static bool is_inside(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

static bool check_rook_queen(const ChessBoard *cb, int x, int y, 
                            char enemy_rook, char enemy_queen) {
    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + directions[dir][0];
        int ny = y + directions[dir][1];
        
        while (is_inside(nx, ny)) {
            char piece = cb->board[nx][ny];
            if (piece != '.') {
                if (piece == enemy_rook || piece == enemy_queen) {
                    return true;
                }
                break;
            }
            nx += directions[dir][0];
            ny += directions[dir][1];
        }
    }
    return false;
}

static bool check_bishop_queen(const ChessBoard *cb, int x, int y, 
                              char enemy_bishop, char enemy_queen) {
    const int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    
    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + directions[dir][0];
        int ny = y + directions[dir][1];
        
        while (is_inside(nx, ny)) {
            char piece = cb->board[nx][ny];
            if (piece != '.') {
                if (piece == enemy_bishop || piece == enemy_queen) {
                    return true;
                }
                break;
            }
            nx += directions[dir][0];
            ny += directions[dir][1];
        }
    }
    return false;
}

static bool check_knight(const ChessBoard *cb, int x, int y, char enemy_knight) {
    const int moves[8][2] = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2},
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };
    
    for (int i = 0; i < 8; ++i) {
        int nx = x + moves[i][0];
        int ny = y + moves[i][1];
        
        if (is_inside(nx, ny) && cb->board[nx][ny] == enemy_knight) {
            return true;
        }
    }
    return false;
}

static bool check_pawn(const ChessBoard *cb, int x, int y, bool is_white) {
    int attack_dir = is_white ? -1 : 1;
    char enemy_pawn = is_white ? 'p' : 'P';
    
    for (int dy = -1; dy <= 1; dy += 2) {
        int nx = x + attack_dir;
        int ny = y + dy;
        
        if (is_inside(nx, ny) && cb->board[nx][ny] == enemy_pawn) {
            return true;
        }
    }
    return false;
}

static bool is_king_in_check(const ChessBoard *cb, bool check_white_king) {
    int x = check_white_king ? cb->white_king_x : cb->black_king_x;
    int y = check_white_king ? cb->white_king_y : cb->black_king_y;
    
    if (check_white_king) {
        return check_rook_queen(cb, x, y, 'r', 'q') ||
               check_bishop_queen(cb, x, y, 'b', 'q') ||
               check_knight(cb, x, y, 'n') ||
               check_pawn(cb, x, y, true);
    } else {
        return check_rook_queen(cb, x, y, 'R', 'Q') ||
               check_bishop_queen(cb, x, y, 'B', 'Q') ||
               check_knight(cb, x, y, 'N') ||
               check_pawn(cb, x, y, false);
    }
}

static bool read_board(ChessBoard *cb) {
    bool is_empty = true;
    
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (fgets(cb->board[i], LINE_BUFFER, stdin) == NULL) {
            return false;
        }
        getchar(); // Consume newline
        
        for (int j = 0; j < BOARD_SIZE; ++j) {
            char piece = cb->board[i][j];
            if (piece != '.') {
                is_empty = false;
                if (piece == 'K') {
                    cb->white_king_x = i;
                    cb->white_king_y = j;
                } else if (piece == 'k') {
                    cb->black_king_x = i;
                    cb->black_king_y = j;
                }
            }
        }
    }
    return !is_empty;
}

int main(void) {
    ChessBoard cb;
    int game_number = 1;
    
    while (read_board(&cb)) {
        bool white_check = is_king_in_check(&cb, true);
        bool black_check = is_king_in_check(&cb, false);
        
        printf("Game #%d: ", game_number++);
        
        if (white_check) {
            puts("white king is in check.");
        } else if (black_check) {
            puts("black king is in check.");
        } else {
            puts("no king is in check.");
        }
    }
    
    return 0;
}
