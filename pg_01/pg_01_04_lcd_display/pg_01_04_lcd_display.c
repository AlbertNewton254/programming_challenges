#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 8
#define MAX_SCALE 10
#define MIN_SCALE 1

typedef enum {
	SEG_TOP = 0,
	SEG_TOP_LEFT,
	SEG_TOP_RIGHT,
	SEG_MIDDLE,
	SEG_BOTTOM_LEFT,
	SEG_BOTTOM_RIGHT,
	SEG_BOTTOM
} Segment;

const int segments7[10][7] = {
	{1,1,1,0,1,1,1}, // 0
	{0,0,1,0,0,1,0}, // 1
	{1,0,1,1,1,0,1}, // 2
	{1,0,1,1,0,1,1}, // 3
	{0,1,1,1,0,1,0}, // 4
	{1,1,0,1,0,1,1}, // 5
	{1,1,0,1,1,1,1}, // 6
	{1,0,1,0,0,1,0}, // 7
	{1,1,1,1,1,1,1}, // 8
	{1,1,1,1,0,1,1}  // 9
};

int is_valid_scale(int s) {
	return s >= MIN_SCALE && s <= MAX_SCALE;
}

int is_valid_number(const char *num) {
	int len = strlen(num);
	if (len == 0 || len > MAX_DIGITS) return 0;
	for (int i = 0; i < len; i++) {
		if (num[i] < '0' || num[i] > '9') return 0;
	}
	return 1;
}

void print_horizontal(int digit, int s, Segment seg) {
	printf(" ");
	for (int i = 0; i < s; i++)
		printf(segments7[digit][seg] ? "-" : " ");
	printf(" ");
}

void print_vertical(int digit, int s, Segment left, Segment right) {
	printf(segments7[digit][left] ? "|" : " ");
	for (int i = 0; i < s; i++)
		printf(" ");
	printf(segments7[digit][right] ? "|" : " ");
}

void print_lcd(const char *number, int s) {
	int len = strlen(number);

	for (int i = 0; i < len; i++) {
		print_horizontal(number[i] - '0', s, SEG_TOP);
		printf(" ");
	}
	printf("\n");

	for (int row = 0; row < s; row++) {
		for (int i = 0; i < len; i++) {
			print_vertical(number[i] - '0', s, SEG_TOP_LEFT, SEG_TOP_RIGHT);
			printf(" ");
		}
		printf("\n");
	}

	for (int i = 0; i < len; i++) {
		print_horizontal(number[i] - '0', s, SEG_MIDDLE);
		printf(" ");
	}
	printf("\n");

	for (int row = 0; row < s; row++) {
		for (int i = 0; i < len; i++) {
			print_vertical(number[i] - '0', s, SEG_BOTTOM_LEFT, SEG_BOTTOM_RIGHT);
			printf(" ");
		}
		printf("\n");
	}

	for (int i = 0; i < len; i++) {
		print_horizontal(number[i] - '0', s, SEG_BOTTOM);
		printf(" ");
	}
	printf("\n");
}

int main(void) {
	int scale;
	char number[MAX_DIGITS + 1];

	printf("Enter scale (1-10): ");
	if (scanf("%d", &scale) != 1 || !is_valid_scale(scale)) {
		printf("Invalid scale.\n");
		return 1;
	}

	printf("Enter number (up to 8 digits): ");
	if (scanf("%8s", number) != 1 || !is_valid_number(number)) {
		printf("Invalid number.\n");
		return 1;
	}

	print_lcd(number, scale);
	return 0;
}
