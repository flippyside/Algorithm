#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<stdio.h>
using namespace std;

/*
第i堆金币：总重量mi 总价值vi
容量：T
N堆金币
*/
const int MAX = 100000;
double N, T;
double ave[MAX], w[MAX], v[MAX];
int findMaxIndex(double arr[], int N) {
	int max_index = 0, max = arr[0], c = 0;
	for (c = 0; c < N; c++) {
		if (arr[c] > max) { 
			max_index = c; 
			max = arr[c];	
		}
	}
	return max_index;
}
/*
4 50
15 45
30 120
10 60
20 100
*/
int main() {
	cin >> N >> T;
	for (int i = 0; i < N; i++) {
		cin >> w[i] >> v[i];
		ave[i] = v[i] / w[i];
	}// w[i] weight  v[i] value
	double rest = T;

	int i = findMaxIndex(ave, N);
	double result = 0;
	while (rest > 0) {
		if (w[i] > rest) {
			result += rest * ave[i];
			break;
		}
		else {
			result += v[i];
			rest -= w[i];
		}
		ave[i] = -1;
		i = findMaxIndex(ave, N);
	}// 
	printf("%.2f", result);
}
