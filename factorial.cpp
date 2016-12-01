// UVA 623: 500!
// 本題動態規劃的思維參考自：UVa：623－500! – 翼世界夢想領域(部落格文章)
//
// This is the problm of calculating big number
//
// method: 1 variable not enough, so we can use multiple variable to store.
// here I use array
// Let every element can contain 0~9999 , that is 4 digits.

/* sample

the very long number:	1234 5678 9999 9999 4321
we store it like:       A[4] A[3] A[2] A[1] A[0]

*/

// In the factorial problem, we didn't have to consider the negative number.
// Define the multiplication operation for big number.(Array)
#include <cstdio>
#include <memory.h>
using namespace std;

const int table_size = 1005;	// the table numbers to store from 0! to 1000!
const int digit_size = 1000;    // the upper bound of the numbers of segment
const int segment_size = 10000; // A[0], A[1] ... each is the segment containing number from 0 ~ 9999

struct DP_table {
	int A[digit_size];
	int size;	// keep the size of the every DP_table
	DP_table();
};

DP_table::DP_table() {
	memset(A, 0, sizeof(A));
	size = 1;
}

DP_table dp[table_size];

//   1234 1234
// x        10 (b)
// -------------
// 12340 12340 -> Step1: multiply every segment with the variable b
// 1 2341 2340 -> Step2: Update every segment so that every segment maintains 4 digits
//			   -> Step3: Check if the upper is changed
DP_table multiple(int x, const DP_table& dp) {
	DP_table temp;
	for(temp.size = 0; temp.size < dp.size; ++temp.size) {
		temp.A[temp.size] = x * dp.A[temp.size];
	}
	for(int j = 0; j < temp.size; ++j) {
		if(temp.A[j] >= segment_size) {
			temp.A[j+1] += (temp.A[j] / segment_size);
			temp.A[j] %= segment_size;
		}
	}
	if(temp.A[temp.size])
		temp.size += 1;

	return temp;
}

void printBigNumber(const DP_table& dp) {

	int digit = dp.size - 1;

	printf("%d", dp.A[digit]);
	--digit;

	while(digit != -1) {
		printf("%04d", dp.A[digit]);
		--digit;
	}
}

int main() {
	int n;

	// DP table
	dp[0].A[0] = 1;
  	dp[1].A[0] = 1;

  	for(int i = 2; i <= 1000; ++i) {
  		dp[i] = multiple(i, dp[i-1]);
  	}

	while(scanf("%d", &n) != EOF) {
		printf("%d!\n", n);
		printBigNumber(dp[n]);
		printf("\n");
	}
}

// Time Complexity : O(n^2)
// Space Complexity: O(1)
