/**
 * @file pg_01_03_the_trip.c
 * @author miguel
 * @brief Computes how much money needs to be exchanged so that all individuals in a group
 * end up with the same amount (equal to the average).
 *
 * Input: multiple groups of float values. Output: exchange amount per group.
 */

#include <stdio.h>
#include <math.h>

#define MAX_STUDENTS 1000 // Maximum amount of students
#define MAX_MONEY 10000.0 // Maximum money per student

/**
 * @brief Calculates the average of an array of n floats.
 * 
 * @param numbers Array of floats representing expenses.
 * @param n Number of elements in the array.
 * @return The average of the values, or -1 if n is invalid.
 */
float average(float numbers[MAX_STUDENTS], int n)
{
	if (n < 0 || n > MAX_STUDENTS)
	{
		return -1;
	}

	float avg = 0;
	for (int i = 0; i < n; i++)
	{
		avg += numbers[i];
	}
	return avg / n;
}

/**
 * @brief Calculates the total amount that needs to be exchanged to equalize all values to the average.
 * 
 * Each person who has more than the average will need to give the excess away.
 * This function sums all such excesses.
 * 
 * @param numbers Array of floats representing expenses.
 * @param n Number of elements in the array.
 * @return Total amount to be exchanged to reach the average, rounded to two decimal places.
 */
float total_exchange(float numbers[MAX_STUDENTS], int n)
{
	float exchange = 0;
	float avg = average(numbers, n);

	if (avg == -1)
	{
		return -1;
	}

	for (int i = 0; i < n; i++)
	{
		float error = numbers[i] - avg;
		if (error > 0)
		{
			exchange += error;
		}
	}

	// Round to two decimal places
	exchange = floor(exchange * 100 + 0.5) / 100;
	return exchange;
}

int main()
{
	int n;
	float expenses[MAX_STUDENTS];

	while (1)
	{
		scanf("%d", &n);

		if (n < 0)
		{
			// Invalid group size
			return -1;
		}
		else if (n == 0)
		{
			// End of input
			break;
		}

		int invalid = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%f", &expenses[i]);
			if (expenses[i] < 0 || expenses[i] > MAX_MONEY)
			{
				invalid = 1;
			}
		}

		if (invalid)
			continue;

		float exchange = total_exchange(expenses, n);
		printf("$%.2f\n", exchange);
	}

	return 0;
}
