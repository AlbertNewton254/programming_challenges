/**
 * @file pg_01_01_collatz.c
 * @author Miguel
 * @brief Computes the maximum Collatz sequence length within a range of natural numbers.
 *
 * This program calculates the Collatz sequence length for each number in a given range
 * and returns the maximum length found. It demonstrates basic control flow, input validation,
 * and algorithmic thinking.
 */

#include <stdio.h>

#define MAX_NUMBER 1000000  ///< Upper bound for valid input values
#define MIN_NUMBER 1        ///< Lower bound for valid input values

/**
 * @brief Computes the length of the Collatz sequence for a given number.
 *
 * The Collatz sequence is defined as:
 * - If n is even, n becomes n / 2
 * - If n is odd,  n becomes 3 * n + 1
 * The sequence ends when n becomes 1.
 *
 * @param n A natural number in the range [MIN_NUMBER, MAX_NUMBER].
 * @return The length of the Collatz sequence, or -1 if input is out of bounds.
 */
int collatz_length(int n) {
    if (n < MIN_NUMBER || n > MAX_NUMBER) {
        return -1;
    }

    int length = 1;

    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        length++;
    }

    return length;
}

/**
 * @brief Finds the maximum Collatz sequence length within a range [a, b].
 *
 * The function handles unordered inputs and validates bounds.
 *
 * @param a One endpoint of the range.
 * @param b The other endpoint of the range.
 * @return The maximum Collatz sequence length in the range, or -1 if inputs are invalid.
 */
int max_collatz_length(int a, int b) {
    int min = (a < b) ? a : b;
    int max = (a > b) ? a : b;

    if (min < MIN_NUMBER || max > MAX_NUMBER) {
        return -1;
    }

    int max_length = 0;

    for (int i = min; i <= max; i++) {
        int length = collatz_length(i);
        if (length > max_length) {
            max_length = length;
        }
    }

    return max_length;
}

/**
 * @brief Entry point of the program.
 *
 * Demonstrates the use of max_collatz_length with sample ranges.
 *
 * @return Exit status code.
 */
int main(void) {
    printf("%d\n", max_collatz_length(1, 3));
    printf("%d\n", max_collatz_length(4, 9));
    printf("%d\n", max_collatz_length(10, 16));
    printf("%d\n", max_collatz_length(17, 25));
    printf("%d\n", max_collatz_length(1, 25));

    return 0;
}