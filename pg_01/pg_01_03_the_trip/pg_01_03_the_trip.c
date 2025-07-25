#include <stdio.h>
#include <math.h>

#define MAX_STUDENTS 1000
#define MAX_MONEY 10000.0f
#define MAX_DECIMALS 2

static int is_valid_group_size(int n) {
    return n > 0 && n <= MAX_STUDENTS;
}

static int is_valid_expense(float expense) {
    return expense >= 0.0f && expense <= MAX_MONEY;
}

static float calculate_average(const float expenses[], int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += expenses[i];
    }
    return sum / n;
}

static float calculate_exchange(const float expenses[], int n) {
    const float avg = calculate_average(expenses, n);
    float exchange = 0.0f;
    
    for (int i = 0; i < n; i++) {
        const float diff = expenses[i] - avg;
        if (diff > 0.0f) {
            exchange += diff;
        }
    }
    
    // Round to 2 decimal places
    const float scale = powf(10.0f, MAX_DECIMALS);
    return floorf(exchange * scale + 0.5f) / scale;
}

static int read_expenses(float expenses[], int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%f", &expenses[i]) != 1) {
            return 0;
        }
        if (!is_valid_expense(expenses[i])) {
            return 0;
        }
    }
    return 1;
}

static void process_groups(void) {
    int n;
    float expenses[MAX_STUDENTS];

    while (scanf("%d", &n) == 1) {
        if (n == 0) {
            break;
        }

        if (!is_valid_group_size(n)) {
            fprintf(stderr, "Error: Invalid group size %d\n", n);
            continue;
        }

        if (!read_expenses(expenses, n)) {
            fprintf(stderr, "Error: Invalid expenses for group size %d\n", n);
            continue;
        }

        printf("$%.2f\n", calculate_exchange(expenses, n));
    }
}

int main(void) {
    process_groups();
    return 0;
}
