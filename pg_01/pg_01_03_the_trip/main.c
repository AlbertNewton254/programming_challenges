/**
 * @file pg_03_the_trip.c
 * @author miguel
 * @brief For each set of n floats, calculates how much must be exchanged 
 * between individuals so that everyone has the same amount (equal to the average).
 * 
 * The program supports multiple sets of values and computes the total exchange needed
 * to equalize values for each group. Exchange is calculated as the total amount that 
 * must be given by those who have more than the average.
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
float totalExchange(float numbers[MAX_STUDENTS], int n)
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

/**
 * @brief Main function that reads multiple sets of expenses and prints the total exchange needed.
 * 
 * The input consists of multiple groups. Each group starts with an integer n (number of students),
 * followed by n float values representing individual expenses. Input ends when n is zero.
 */
int main()
{
	int n;
	float expenses[MAX_STUDENTS];

	while (1)
	{
		scanf("%d", &n);
		/* validates n */
		if (n < 0)
		{
			return -1;
		}
		
		/* finishes when n equals 0 */
		else if (n == 0)
		{
			break;
		}

		else
		{
			for (int i = 0; i < n; i++)
			{
				scanf("%f", &expenses[i]);

				/* validates money per student */
				if (expenses[i] < 0 || expenses[i] > MAX_MONEY)
				{
					break;
				}
			}
		}
		float exchange = totalExchange(expenses, n);
		printf("$%.2f\n", exchange);
	}

	return 0;
}
