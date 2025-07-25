#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    SEG_BOTTOM,
    NUM_SEGMENTS
} Segment;

static const int SEGMENT_PATTERNS[10][NUM_SEGMENTS] = {
    [0] = {1,1,1,0,1,1,1}, // 0
    [1] = {0,0,1,0,0,1,0}, // 1
    [2] = {1,0,1,1,1,0,1}, // 2
    [3] = {1,0,1,1,0,1,1}, // 3
    [4] = {0,1,1,1,0,1,0}, // 4
    [5] = {1,1,0,1,0,1,1}, // 5
    [6] = {1,1,0,1,1,1,1}, // 6
    [7] = {1,0,1,0,0,1,0}, // 7
    [8] = {1,1,1,1,1,1,1}, // 8
    [9] = {1,1,1,1,0,1,1}  // 9
};

static int is_valid_scale(int scale) {
    return scale >= MIN_SCALE && scale <= MAX_SCALE;
}

static int is_valid_number(const char *num) {
    const size_t len = strlen(num);
    if (len == 0 || len > MAX_DIGITS) return 0;
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit(num[i])) return 0;
    }
    return 1;
}

static void print_horizontal(int digit, int scale, Segment seg) {
    putchar(' ');
    for (int i = 0; i < scale; i++) {
        putchar(SEGMENT_PATTERNS[digit][seg] ? '-' : ' ');
    }
    putchar(' ');
}

static void print_vertical(int digit, int scale, Segment left, Segment right) {
    putchar(SEGMENT_PATTERNS[digit][left] ? '|' : ' ');
    for (int i = 0; i < scale; i++) {
        putchar(' ');
    }
    putchar(SEGMENT_PATTERNS[digit][right] ? '|' : ' ');
}

static void print_lcd_display(const char *number, int scale) {
    const size_t len = strlen(number);

    // Top segment
    for (size_t i = 0; i < len; i++) {
        print_horizontal(number[i] - '0', scale, SEG_TOP);
        putchar(' ');
    }
    putchar('\n');

    // Upper vertical segments
    for (int row = 0; row < scale; row++) {
        for (size_t i = 0; i < len; i++) {
            print_vertical(number[i] - '0', scale, SEG_TOP_LEFT, SEG_TOP_RIGHT);
            putchar(' ');
        }
        putchar('\n');
    }

    // Middle segment
    for (size_t i = 0; i < len; i++) {
        print_horizontal(number[i] - '0', scale, SEG_MIDDLE);
        putchar(' ');
    }
    putchar('\n');

    // Lower vertical segments
    for (int row = 0; row < scale; row++) {
        for (size_t i = 0; i < len; i++) {
            print_vertical(number[i] - '0', scale, SEG_BOTTOM_LEFT, SEG_BOTTOM_RIGHT);
            putchar(' ');
        }
        putchar('\n');
    }

    // Bottom segment
    for (size_t i = 0; i < len; i++) {
        print_horizontal(number[i] - '0', scale, SEG_BOTTOM);
        putchar(' ');
    }
    putchar('\n');
}

int main(void) {
    int scale;
    char number[MAX_DIGITS + 1] = {0};

    printf("Enter scale (1-10): ");
    if (scanf("%d", &scale) != 1 || !is_valid_scale(scale)) {
        fputs("Error: Invalid scale\n", stderr);
        return 1;
    }

    printf("Enter number (up to 8 digits): ");
    if (scanf("%8s", number) != 1 || !is_valid_number(number)) {
        fputs("Error: Invalid number\n", stderr);
        return 1;
    }

    print_lcd_display(number, scale);
    return 0;
}
