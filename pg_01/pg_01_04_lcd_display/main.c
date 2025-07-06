/**
 * @file pg_01_04_lcd_display.c
 * @author miguel
 * @brief Scalable LCD-style digit display using 7-segment representation.
 */

#include <stdio.h>
#include <string.h>

/* We have seven segments, so here we name them */
typedef enum {
    SEG_TOP = 0,
    SEG_TOP_LEFT,
    SEG_TOP_RIGHT,
    SEG_MIDDLE,
    SEG_BOTTOM_LEFT,
    SEG_BOTTOM_RIGHT,
    SEG_BOTTOM
} Segment;

/* Segment activation map for digits 0–9 */
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

/**
 * @brief Prints little horizontal slice for a given digit
 * @param digit The digit we want to print
 * @param s The scale
 * @param seg The segment type
 */
void print_horizontal_slice(int digit, int s, Segment seg) {
    printf(" ");
    for (int i = 0; i < s; i++)
        printf(segments7[digit][seg] ? "-" : " ");
    printf(" ");
}

/**
 * @brief Prints little vertical slice for a given digit
 * @param digit The digit we want to print
 * @param s The scale
 * @param left_seg The left-segment type
 * @param right_seg The right-segment slice
 */
void print_vertical_slice(int digit, int s, Segment left_seg, Segment right_seg) {
    printf(segments7[digit][left_seg] ? "|" : " ");
    for (int i = 0; i < s; i++)
        printf(" ");
    printf(segments7[digit][right_seg] ? "|" : " ");
}

/**
 * @brief Prints a given number in LCD style
 * @param number The number string
 * @param s The scale
 */
void print_lcd_number(const char *number, int s) {
    int len = strlen(number);

    // Top segment
    for (int i = 0; i < len; i++)
    {
        print_horizontal_slice(number[i] - '0', s, SEG_TOP);
        printf(" ");
    }
    printf("\n");

    // Upper vertical segments
    for (int row = 0; row < s; row++) 
    {
        for (int i = 0; i < len; i++) 
	{
            print_vertical_slice(number[i] - '0', s, SEG_TOP_LEFT, SEG_TOP_RIGHT);
            printf(" ");
        }
        printf("\n");
    }

    // Middle segment
    for (int i = 0; i < len; i++) 
    {
        print_horizontal_slice(number[i] - '0', s, SEG_MIDDLE);
        printf(" ");
    }
    printf("\n");

    // Lower vertical segments
    for (int row = 0; row < s; row++) 
    {
        for (int i = 0; i < len; i++) 
	{
            print_vertical_slice(number[i] - '0', s, SEG_BOTTOM_LEFT, SEG_BOTTOM_RIGHT);
            printf(" ");
        }
        printf("\n");
    }

    // Bottom segment
    for (int i = 0; i < len; i++) 
    {
        print_horizontal_slice(number[i] - '0', s, SEG_BOTTOM);
        printf(" ");
    }
    printf("\n");
}

/**
 * @brief Main function
 */
int main()
{
	int s;
	char number[9];
	printf("Enter scale (1-10): ");
	scanf("%d", &s);
	if (s < 1 || s > 10)
	{
		printf("Invalid scale. Must be between 1 and 10.\n");
		return 1;
	}

	printf("Enter number: ");
	scanf("%s", number);
	if (strlen(number) > 8)
	{
		printf("Number too long. Max 8 digits.\n");
		return 1;
	}

	print_lcd_number(number, s);
	return 0;
}
