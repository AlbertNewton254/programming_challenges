/**
 * @file pg_01_collatz.c
 * @author miguel
 * @brief Computes the maximum Collatz sequence length within a range of natural numbers.
 *
 * This program calculates the Collatz sequence length for each number in a given range
 * and returns the maximum length found.
 */

#include <stdio.h>

#define MAX_NUMBER 1000000  ///< Upper limit for valid input values

/**
 * @brief Computes the length of the Collatz sequence for a given number.
 *
 * Applies the 3n+1 rule recursively until reaching 1.
 * 
 * @param n The starting number (must be 1 <= n <= MAX_NUMBER).
 * @return Length of the sequence, or -1 if input is invalid.
 */
int collatz_length(int n)
{
	if (n < 1 || n > MAX_NUMBER)
	{
		return -1;
	}

	int length = 1;

	while (n != 1)
	{
		if (n % 2 == 0)
		{
			n /= 2;
		}
		else
		{
			n = 3 * n + 1;
		}
		length++;
	}

	return length;
}

/**
 * @brief Computes the maximum Collatz sequence length in a given inclusive range.
 * 
 * @param a One endpoint of the range.
 * @param b The other endpoint of the range.
 * @return Maximum sequence length in the range [min(a, b), max(a, b)], or -1 if invalid input.
 */
int max_collatz_length(int a, int b)
{
	int min = (a < b) ? a : b;
	int max = (a > b) ? a : b;

	if (min < 1 || max > MAX_NUMBER)
	{
		return -1;
	}

	int max_length = 0;

	for (int i = min; i <= max; i++)
	{
		int length = collatz_length(i);
		if (length > max_length)
		{
			max_length = length;
		}
	}

	return max_length;
}

/**
 * @brief Test driver for the Collatz sequence functions.
 *
 * Uncomment the examples below to test specific ranges.
 */
int main()
{
	/*
	printf("%d\n", max_collatz_length(1, 3));
	printf("%d\n", max_collatz_length(4, 9));
	printf("%d\n", max_collatz_length(10, 16));
	printf("%d\n", max_collatz_length(17, 25));
	*/

	return 0;
}

