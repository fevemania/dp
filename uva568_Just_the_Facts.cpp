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

#include <cstdio>


const table_size = 10005;
const digit_size = 10000;


void print_last_non_zero(int n) {
	printf(“% 5d”, n);
	printf(“ -> %d, dp[n]);
	printf(“\n”);
}


int main() {
	int dp[table_size];
	dp[0] = 1;
	dp[1] = 1;
	for (int i = 2; i <= 10000; ++i) {
		int temp = dp[i-1] * i;
		while(!(temp%10)) {
			temp /= 10;
		}
		dp[i] = temp%10;
	}
	int n;
	while(scanf(“%d”, &n) != EOF) {
		print_last_non_zero(n);
	}
}

