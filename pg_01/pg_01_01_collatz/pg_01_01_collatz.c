#include <stdio.h>
#include <limits.h>

#define MAX_NUMBER 1000000
#define MIN_NUMBER 1

static int is_valid_input(int n) {
    return n >= MIN_NUMBER && n <= MAX_NUMBER;
}

static int collatz_length(int n) {
    if (!is_valid_input(n)) {
        return -1;
    }

    int length = 1;

    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        
        // Check for potential overflow
        if (n < 1) {
            return -1;
        }
        
        length++;
    }

    return length;
}

static int max_collatz_length(int a, int b) {
    if (!is_valid_input(a) || !is_valid_input(b)) {
        return -1;
    }

    const int start = a < b ? a : b;
    const int end = a > b ? a : b;
    int max_length = 0;

    for (int i = start; i <= end; i++) {
        const int current_length = collatz_length(i);
        if (current_length == -1) {
            return -1;
        }
        if (current_length > max_length) {
            max_length = current_length;
        }
    }

    return max_length;
}

static void test_range(int a, int b, int expected) {
    const int result = max_collatz_length(a, b);
    const char* status = (result == expected) ? "PASS" : "FAIL";

    printf("%s: max_collatz_length(%d, %d) = %d", status, a, b, result);
    if (result != expected) {
        printf(" (expected %d)", expected);
    }
    putchar('\n');
}

int main(void) {
    // Valid ranges
    test_range(1, 3, 8);
    test_range(4, 9, 20);
    test_range(10, 16, 20);
    test_range(17, 25, 24);
    test_range(1, 25, 24);

    // Edge cases
    test_range(0, 3, -1);                   // Invalid input
    test_range(1, MAX_NUMBER + 1, -1);      // Invalid upper bound
    test_range(42, 42, collatz_length(42)); // Single number
    test_range(MAX_NUMBER, MAX_NUMBER, collatz_length(MAX_NUMBER));

    return 0;
}
