/**
 * @file pg_01_03_the_trip.c
 * @author Miguel
 * @brief Computes how much money needs to be exchanged so that all individuals in a group
 * end up with the same amount (equal to the average).
 *
 * Input: multiple groups of float values. Output: exchange amount per group.
 */

#include <stdio.h>
#include <math.h>

#define MAX_STUDENTS 1000   ///< Maximum number of students per group
#define MAX_MONEY 10000.0   ///< Maximum money per student

/**
 * @brief Calculates the average of an array of n floats.
 *
 * @param numbers Array of floats representing expenses.
 * @param n Number of elements in the array.
 * @return The average of the values, or -1 if n is invalid.
 */
float average(float numbers[MAX_STUDENTS], int n) {
    if (n < 0 || n > MAX_STUDENTS) {
        return -1;
    }

    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += numbers[i];
    }

    return sum / n;
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
float total_exchange(float numbers[MAX_STUDENTS], int n) {
    float avg = average(numbers, n);
    if (avg == -1) {
        return -1;
    }

    float exchange = 0;
    for (int i = 0; i < n; i++) {
        float diff = numbers[i] - avg;
        if (diff > 0) {
            exchange += diff;
        }
    }

    /* Round to two decimal places */
    exchange = floor(exchange * 100 + 0.5) / 100;
    return exchange;
}

/**
 * @brief Entry point of the program.
 *
 * Reads multiple groups of student expenses and prints the amount of money
 * that needs to be exchanged for each group to equalize expenses.
 *
 * @return Exit status code.
 */
int main(void) {
    int n;
    float expenses[MAX_STUDENTS];

    while (1) {
        scanf("%d", &n);

        if (n < 0) {
            return -1; // Invalid group size
        } else if (n == 0) {
            break; // End of input
        }

        int invalid = 0;
        for (int i = 0; i < n; i++) {
            scanf("%f", &expenses[i]);
            if (expenses[i] < 0 || expenses[i] > MAX_MONEY) {
                invalid = 1;
            }
        }

        if (invalid) {
            continue;
        }

        float exchange = total_exchange(expenses, n);
        printf("$%.2f\n", exchange);
    }

    return 0;
}