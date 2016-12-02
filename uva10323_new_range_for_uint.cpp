// Actually, this was a bad problem that negative factorial is definitely not defined, but uva would test for the negative factorial


// DP_table:
// 1. the array represent our factorial number ( split 4 digits in one element )
// 2. the size to keep of the total number of elements of the array


// we can first calculate the upperbound number of factoral and lowerbound number of factoral.


// that is the Lowerbound = 10000 , which is between 7! and 8!, which mean if the input number is less than or less to 7, then we directly print “Underflow!”


// and for the Upperbound, we also need to find the n! which just larger than to 62|2702|0800
// -> n = 14
// -> and that all we need to keep in our DP_table



#define LOCAL
#include <memory.h>
#include <cstdio>
#include <cstdlib>

const int array_size = 1000;
const int table_size = 15;
const int segment_size = 10000;

struct DP_table {
	int arr[array_size];
	int size;
	DP_table();
};

DP_table::DP_table() {
	memset(arr, 0, sizeof(arr));
	size = 1;
}

DP_table dp[table_size];

// first, define multiplication operation with n!
DP_table multi(int n, const DP_table& dp) 
{
	DP_table temp;
	for (temp.size = 0; temp.size < dp.size; ++temp.size) {
		temp.arr[temp.size] = n * dp.arr[temp.size];
	}
	for (int j = 0; j < temp.size; ++j) {
		if (temp.arr[j] >= segment_size) {
			temp.arr[j+1] += (temp.arr[j] / segment_size);
			temp.arr[j] %= segment_size;
		}
	}
	if (temp.arr[temp.size])
		++temp.size;

	return temp;
}
// 		4 7900 1600
// * 			 13
// 52  102700 20800
//->  62 2702 0800
// print_function -> to check if the array is between the upperbound and lowerbound. if it is, then normal print, otherwise, print underflow or overflow

void print_fact(int n) {
	if(n < 0) {
		if(abs(n) % 2) // odd number -> ex. (-3)! = (-1)(-2)(-3) -> total multiple will be negative.
			printf("Overflow!\n");
		else {
			printf("Underflow!\n");
		}
	}
	else if(n < 8)
		printf("Underflow!\n");
	else if(n > 13)
		printf("Overflow!\n");
	else {
		int digit = dp[n].size - 1;

		printf("%d", dp[n].arr[digit]);
		--digit;

		while(digit != -1) {
			printf("%04d", dp[n].arr[digit]);
			--digit;
		}
		printf("\n");
	}
}


int main() {
// #ifdef LOCAL
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
// #endif
	dp[0].arr[0] = 1;
	dp[1].arr[0] = 1;

	for(int i = 2; i < table_size; ++i)
		dp[i] = multi(i, dp[i-1]);

	int n;
	while(scanf("%d", &n) == 1) {
		print_fact(n);
	}
}