#include <bits/stdc++.h>
using namespace std;

int n;
int minn, maxx;
long long summ;
int a[100007];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	
	minn = a[1];
	maxx = a[1];
	summ = a[1];
	printf("%d %d %.6lf\n", minn, maxx, (double) summ);
	
	for (int i = 2; i <= n; i++) {
		minn = min(minn + 1, a[i]);
		maxx = max(maxx + 1, a[i]);
		summ = summ + i - 1 + a[i];
		printf("%d %d %.6lf\n", minn, maxx, (double) summ / i);
	}
}