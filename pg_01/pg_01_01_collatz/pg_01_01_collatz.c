/**
 * @file pg_01_01_collatz.c
 * @author miguel
 * @brief Computes the maximum Collatz sequence length within a range of natural numbers.
 *
 * This program calculates the Collatz sequence length for each number in a given range
 * and returns the maximum length found.
 */

#include <stdio.h>

#define MAX_NUMBER 1000000 // Upper bound for extreme points 

/**
 * @brief Returns the Collatz sequence length for a given natural number.
 * @param n A natural number in [1, MAX_NUMBER].
 * @return Length of sequence, or -1 if out of bounds.
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
 * @brief Returns the maximum Collatz sequence length within a range with extremes a and b.
 *
 * Inputs can be in any order. Returns -1 if either endpoint is out of bounds.
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

int main()
{
	printf("%d\n", max_collatz_length(1, 3));
	printf("%d\n", max_collatz_length(4, 9));
	printf("%d\n", max_collatz_length(10, 16));
	printf("%d\n", max_collatz_length(17, 25));
	printf("%d\n", max_collatz_length(1, 25));

	return 0;
}
