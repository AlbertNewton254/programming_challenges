#include <stdio.h>
#include <string.h>

typedef struct {
	char board[8][9]; // Last column for terminator '\0'
	int x_black_king, y_black_king;
	int x_white_king, y_white_king;
} Chess;

int is_inside(int x, int y) {
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}

 
// Rook and queen make both horizontal movements.
int check_rook_queen(Chess *c, int x, int y, char enemy_rook, char enemy_queen) {
	int dx[] = { 0, 0, 1, -1 };
	int dy[] = { 1, -1, 0, 0 };
	for (int dir = 0; dir < 4; ++dir) {
		int i = x + dx[dir], j = y + dy[dir];
		while (is_inside(i, j)) {
			char piece = c->board[i][j];
			if (piece != '.') {
				if (piece == enemy_rook || piece == enemy_queen)
					return 1;
				break;
			}
			i += dx[dir];
			j += dy[dir];
		}
	}
	return 0;
}

// As before, bishop and queen make both diagonal movements.
int check_bishop_queen(Chess *c, int x, int y, char enemy_bishop, char enemy_queen) {
	int dx[] = { 1, 1, -1, -1 };
	int dy[] = { 1, -1, 1, -1 };
	for (int dir = 0; dir < 4; ++dir) {
		int i = x + dx[dir], j = y + dy[dir];
		while (is_inside(i, j)) {
			char piece = c->board[i][j];
			if (piece != '.') {
				if (piece == enemy_bishop || piece == enemy_queen)
					return 1;
				break;
			}
			i += dx[dir];
			j += dy[dir];
		}
	}
	return 0;
}

int check_knight(Chess *c, int x, int y, char enemy_knight) {
	int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	for (int i = 0; i < 8; ++i) {
		int nx = x + dx[i], ny = y + dy[i];
		if (is_inside(nx, ny) && c->board[nx][ny] == enemy_knight)
			return 1;
	}
	return 0;
}

int check_pawn(Chess *c, int x, int y, int is_white) {
	int dir = is_white ? -1 : 1;
	char enemy_pawn = is_white ? 'p' : 'P';
	for (int dy = -1; dy <= 1; dy += 2) {
		int nx = x + dir, ny = y + dy;
		if (is_inside(nx, ny) && c->board[nx][ny] == enemy_pawn)
			return 1;
	}
	return 0;
}

int is_white_king_in_check(Chess *c) {
	int x = c->x_white_king, y = c->y_white_king;
	return check_rook_queen(c, x, y, 'r', 'q') ||
	       check_bishop_queen(c, x, y, 'b', 'q') ||
	       check_knight(c, x, y, 'n') ||
	       check_pawn(c, x, y, 1);
}

int is_black_king_in_check(Chess *c) {
	int x = c->x_black_king, y = c->y_black_king;
	return check_rook_queen(c, x, y, 'R', 'Q') ||
	       check_bishop_queen(c, x, y, 'B', 'Q') ||
	       check_knight(c, x, y, 'N') ||
	       check_pawn(c, x, y, 0);
}

int main() {
	Chess c;
	int game_number = 1;

	while (1) {
		int is_empty = 1;
		for (int i = 0; i < 8; ++i) {
			fgets(c.board[i], 9, stdin);
			getchar(); // reads '\n' in buffer
			for (int j = 0; j < 8; ++j) {
				char piece = c.board[i][j];
				if (piece != '.')
					is_empty = 0;
				if (piece == 'K') {
					c.x_white_king = i;
					c.y_white_king = j;
				} else if (piece == 'k') {
					c.x_black_king = i;
					c.y_black_king = j;
				}
			}
		}

		if (is_empty)
			break;

		int white_check = is_white_king_in_check(&c);
		int black_check = is_black_king_in_check(&c);

		printf("Game #%d: ", game_number++);
		
		// Both kings cannot be in check, theoretically speaking.
		if (white_check)
			printf("white king is in check.\n");
		else if (black_check)
			printf("black king is in check.\n");
		else
			printf("no king is in check.\n");
	}

	return 0;
}

