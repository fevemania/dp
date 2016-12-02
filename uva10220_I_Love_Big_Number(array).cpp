// for this problem, I would like split every digit and store each of them into the array
// 
// So I would have the data structure called “DP_table” which have the following member
// 1. the array to store each digit. and cause the upperbound is 1000!l, that’s 25XX digits, so I would set the array_size as 3000
// 3. the size (the number of digits) of the the correspond n!
// 2. the sum of the correspond n!
// 
// Create by fevemania on 12/2/16.

#include <cstdio>
#include <memory.h>

const int digit_size = 3000;
const int table_size = 1005;
const int limit = 10;


struct DP_table {
	int arr[digit_size];
	int size;
	int sum;
	DP_table();
};

DP_table::DP_table() {
	memset(arr, 0, sizeof(arr));
	size = 1;
	sum = 1;
}

DP_table dp[table_size];
// do the multiplication operation of Big number and save the sum into DP_table
DP_table multi(int n, const DP_table& dp, int x) 
{
	DP_table temp;
	temp.sum = 0;
	for (temp.size = 0; temp.size < dp.size; ++temp.size) {
		temp.arr[temp.size] = dp.arr[temp.size] * n;
	}

	int cnt = temp.size;
	for (int i = 0; i < cnt; ++i) {
		if(temp.arr[i] >= limit) {
			temp.arr[i+1] += (temp.arr[i] / limit);
			temp.arr[i] %= limit;

		}
		temp.sum += temp.arr[i];
	}

	while (temp.arr[temp.size]) {
		if(temp.arr[temp.size] / limit) {
			temp.arr[temp.size+1] = temp.arr[temp.size] / limit;
			temp.arr[temp.size] %= limit;
		}
		temp.sum += temp.arr[temp.size];
		++temp.size;
	}

	// printf("i = %d\n", x);
	// printf("temp.size = %d\n", temp.size);
	// for(int i = temp.size-1; i >= 0; --i)
	// 	printf("%d", temp.arr[i]);
	// printf("\n");
	// printf("temp.sum = %d\n", temp.sum);
	return temp;
}


// print_sum
void print_sum(const DP_table& dp) {
	printf("%d", dp.sum);
}


int main() {
	
	dp[0].arr[0] = 1;
	dp[1].arr[0] = 1;

	for (int i = 2; i <= 1000; ++i)
		dp[i] = multi(i, dp[i-1], i);

	int n;
	while (scanf("%d", &n) != EOF) {
		print_sum(dp[n]);
		printf("\n");
	}
}

// Time Complexity: O(n^2)
// Space Complexity: O(digit_size * table_size)
