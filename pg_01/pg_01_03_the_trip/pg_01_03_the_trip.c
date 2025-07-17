#include <stdio.h>
#include <math.h>

#define MAX_STUDENTS 1000
#define MAX_MONEY 10000.0

// Check if group size is valid
int is_valid_group_size(int n) {
	return n > 0 && n <= MAX_STUDENTS;
}

// Check if a single expense is valid
int is_valid_expense(float expense) {
	return expense >= 0 && expense <= MAX_MONEY;
}

// Calculate the average of expenses
float average(float expenses[], int n) {
	float sum = 0;
	for (int i = 0; i < n; i++) {
		sum += expenses[i];
	}
	return sum / n;
}

// Calculate total amount to exchange so everyone has the average
float total_exchange(float expenses[], int n) {
	float avg = average(expenses, n);
	float exchange = 0;
	for (int i = 0; i < n; i++) {
		float diff = expenses[i] - avg;
		if (diff > 0)
			exchange += diff;
	}
	// Round to 2 decimal places
	return floor(exchange * 100 + 0.5) / 100;
}

// Read expenses from input; returns 1 if valid, 0 otherwise
int read_expenses(float expenses[], int n) {
	for (int i = 0; i < n; i++) {
		if (scanf("%f", &expenses[i]) != 1)
			return 0; // input failure
		if (!is_valid_expense(expenses[i]))
			return 0; // invalid expense
	}
	return 1;
}

// Process groups until input ends or zero group size is read
void process_groups() {
	int n;
	float expenses[MAX_STUDENTS];

	while (1) {
		if (scanf("%d", &n) != 1)
			break; // EOF or error

		if (n == 0)
			break; // end of input

		if (!is_valid_group_size(n))
			continue; // skip invalid group sizes

		if (!read_expenses(expenses, n))
			continue; // skip invalid expenses

		float exchange = total_exchange(expenses, n);
		printf("$%.2f\n", exchange);
	}
}

int main(void) {
	process_groups();
	return 0;
}

