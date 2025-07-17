#include <stdio.h>

#define MAX_NUMBER 1000000
#define MIN_NUMBER 1

// Checks if the number is within valid limits.
int is_valid_input(int n) {
	return n >= MIN_NUMBER && n <= MAX_NUMBER;
}

// Counts how many steps the Collatz sequence takes to reach 1.
// Returns -1 if the input is invalid.
int collatz_length(int n) {
	if (!is_valid_input(n))
		return -1;

	int length = 1;

	while (n != 1) {
		if (n % 2 == 0)
			n = n / 2;
		else
			n = 3 * n + 1;
		length++;
	}

	return length;
}

// Finds the max Collatz sequence length between a and b.
// Accepts unordered inputs, returns -1 if inputs are invalid.
int max_collatz_length(int a, int b) {
	if (!is_valid_input(a) || !is_valid_input(b))
		return -1;

	int min = (a < b) ? a : b;
	int max = (a > b) ? a : b;

	int max_length = 0;

	for (int i = min; i <= max; i++) {
		int length = collatz_length(i);
		if (length > max_length)
			max_length = length;
	}

	return max_length;
}

// Runs a test and prints if it passed or failed.
void test_range(int a, int b, int expected) {
	int result = max_collatz_length(a, b);

	if (result == expected)
		printf("PASS: max_collatz_length(%d, %d) == %d\n", a, b, result);
	else
		printf("FAIL: max_collatz_length(%d, %d) == %d (expected %d)\n",
			a, b, result, expected);
}

// Main entry point. Runs several tests to check correctness.
int main(void) {
	test_range(1, 3, 8);
	test_range(4, 9, 20);
	test_range(10, 16, 20);
	test_range(17, 25, 24);
	test_range(1, 25, 24);

	test_range(0, 3, -1);                  // invalid input
	test_range(1, MAX_NUMBER + 1, -1);    // invalid input
	test_range(42, 42, collatz_length(42)); // single number case

	return 0;
}

