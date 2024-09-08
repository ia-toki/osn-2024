#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main()
{
	int N, D;
	scanf("%d%d", &N, &D);
	
	int A[N * 2 + 69];
	for(int i = 1; i <= N; i++)
	{
		scanf("%d", A + i);
	}
	for(int i = N + 1; i <= N * 2; i++)
	{
		A[i] = A[i - N];
	}
	
	int last[N + 69];
	for(int i = 1; i <= N; i++)
	{
		last[i] = 0;
	}
	
	int ans, p;
	ans = INF;
	p = 1;
	multiset<int> ms;
	for(int i = 1; i <= N * 2; i++)
	{
		ms.insert(A[i]);
		while(true)
		{
			int mn, mx;
			mn = *ms.begin();
			mx = *prev(ms.end());
			if(mx - mn + 1 <= D)
			{
				break;
			}
			
			ms.erase(ms.find(A[p]));
			p++;
		}
		
		while(p <= last[A[i]])
		{
			ms.erase(ms.find(A[p]));
			p++;
		}
		last[A[i]] = i;
		
		ans = min(ans, D - (i - p + 1));
	}
	
	printf("%d\n", ans);
}
