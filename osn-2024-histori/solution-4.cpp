#include <bits/stdc++.h>
using namespace std;

int n;
int minn, maxx;
long long summ;
int a[100007];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) a[j]++;
		scanf("%d", &a[i]);
		
		minn = a[1];
		maxx = a[1];
		summ = a[1];
		for (int j = 2; j <= i; j++) {
			minn = min(minn, a[j]);
			maxx = max(maxx, a[j]);
			summ += a[j];
		}
		
		printf("%d %d %.6lf\n", minn, maxx, (double) summ / i);
	}
}