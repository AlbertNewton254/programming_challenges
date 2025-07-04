/**
 * @file pg_03_the_trip.c
 * @author miguel
 * @brief For each of m sets of n floats, calculates how much must be exchanged 
 * between individuals so that everyone has the same amount (equal to the average).
 * 
 * The program supports multiple sets of values and computes the total exchange needed
 * to equalize values for each group. Exchange is calculated as the total amount that 
 * must be given by those who have more than the average.
 */

#include <stdio.h>
#include <math.h>
#define MAX_STUDENTS 1000
#define MAX_MONEY 10000.00

/**
 * @brief Calculates the average of an array of n floats.
 * 
 * @param numbers Array of floats.
 * @param n Length of the array.
 * @return The average of the n values, or -1 if n is invalid.
 */
float average(float numbers[MAX_STUDENTS], int n)
{
	/* validate n */
	if (n < 0 || n > MAX_STUDENTS)
	{
		return -1;
	}

	/* initialize average */
	float avg = 0;

	/* add n terms */
	for (int i = 0 ; i < n ; i++)
	{
		avg += numbers[i];
	}

	/* then divide */
	avg = avg / n;

	return avg;
}

/**
 * @brief Calculates the total amount that needs to be exchanged to equalize all values to the average.
 * 
 * Each person who has more than the average will need to give the excess away.
 * This function sums all such excesses.
 * 
 * @param numbers Array of floats.
 * @param n Length of the array.
 * @return Total amount to be exchanged to reach the average, or -1 if input is invalid.
 */
float totalExchange(float numbers[MAX_STUDENTS], int n)
{
	/* initialize total exchange*/
	float exchange = 0;

	float avg = average(numbers, n);

	/* validate */
	if (avg == -1)
	{
		return -1;
	}

	/* for each term, how far above average? */
	for (int i = 0 ; i < n ; i++)
	{
		float error = numbers[i] - avg;
		if (error > 0)
		{
			exchange += error;
		}
	}

	/* round to 2 decimal places */
	exchange = floor(exchange * 100 + 0.5) / 100;

	/* return total exchange */
	return exchange;
}

