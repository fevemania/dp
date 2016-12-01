// uva568_Just_the_Facts
// for this problem, we could not directly calculate all of the n!, (n maybe 10000)
// We know that, 1! = 1, 2! = 1*2 … 5! = 120, 5! = 120 * 6
// so we can observe that “ the last non-zero digit of N! comes from the last non-zero digit of (N-1)! * N


// all we need is track the last non-zero of each n! number (using dp table)


// N!   the last non-zero 
// 0    1
// 1    1
// 2    2
// 3    6
// 4   24 -> 4
// 5   20 -> 2
// 6   12 -> 2

// second revised: We cannot just keep track of the last_non_zero, it also depend on the front digits
// ex. when n = 14, the last few digit is 1200, and so that n = 15, the last few digit is 8000, 8 is decided by 12 * 15 = 180.
// Because of n's upperbound is 10000, I decide the keep the last_five_digit in every DP_table
#include <cstdio>
const int table_size = 10005;
const int digit_size = 10000;
const int upperbound = 100000;

struct DP_table {
	int last_digit;
	int last_five_digit;
};
DP_table dp[table_size];
void print_last_non_zero(int n) {
	printf("%5d", n);
	printf(" -> %d", dp[n].last_digit);
	printf("\n");
}


int main() {
	dp[0].last_digit = 1;
	dp[0].last_five_digit = 1;
	dp[1].last_digit = 1;
	dp[1].last_five_digit = 1;
	for (int i = 2; i <= 10000; ++i) {
		int temp = dp[i-1].last_five_digit * i;
		while(!(temp%10)) {
			temp /= 10;
		}
		dp[i].last_five_digit = temp%upperbound;
		dp[i].last_digit = temp%10;
	}
	int n;
	while(scanf("%d", &n) != EOF) {
		print_last_non_zero(n);
	}
}

