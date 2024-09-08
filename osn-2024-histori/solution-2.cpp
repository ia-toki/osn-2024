#include <bits/stdc++.h>
using namespace std;

int n;
int a[100007];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	
	for (int i = 1; i <= n; i++) {
		printf("%d %d %d\n", i, i, i);
	}
}