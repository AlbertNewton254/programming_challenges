/**
 * @file pg_01_04_lcd_display.c
 * @author miguel
 * @brief Prints numbers in LCD format in a given scale.
 */

#include <stdio.h>
#include <string.h>

const char segments[10][7] =
{
	{1, 1, 1, 0, 1, 1, 1}, // 0
	{0, 0, 1, 0, 0, 1, 0}, // 1
	{1, 0, 1, 1, 1, 0, 1}, // 2
	{1, 0, 1, 1, 0, 1, 1}, // 3
	{0, 1, 1, 1, 0, 1, 0}, // 4
	{1, 1, 0, 1, 0, 1, 1}, // 5
	{1, 1, 0, 1, 1, 1, 1}, // 6
	{1, 0, 1, 0, 0, 1, 0}, // 7
	{1, 1, 1, 1, 1, 1, 1}, // 8
	{1, 1, 1, 1, 0, 1, 1}  // 9
};

/**
 * @brief Prints horizontal line 
 */

void print_horizontal


