#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
int main()
{
	int N;
	scanf("%d", &N);
	
	int A[N + 69], mn = INF, mx = -INF;
	long long sum = 0;
	for(int i = 1; i <= N; i++)
	{
		scanf("%d", A + i);
		A[i] -= i;
		mn = min(mn, A[i]);
		mx = max(mx, A[i]);
		sum += A[i];
		printf("%d %d %.4lf\n", mn + i, mx + i, (double)sum / i + i);
	}
}
