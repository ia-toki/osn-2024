#include <bits/stdc++.h>

using namespace std;

const int MXN = 1e5;

int W[MXN + 69], D[MXN + 69];
vector<int> adj[MXN + 69];
long long dp[MXN + 69][2];

void dfs(int u)
{
	dp[u][0] = 0;
	dp[u][1] = W[u];
	
	vector<long long> diffs[2];
	for(int i = 0; i < adj[u].size(); i++)
	{
		int v = adj[u][i];
		dfs(v);
		
		for(int ii = 0; ii < 2; ii++)
		{
			dp[u][ii] += dp[v][ii];
			diffs[ii].push_back(dp[v][!ii] - dp[v][ii]);
		}
	}
	
	for(int ii = 0; ii < 2; ii++)
	{
		sort(diffs[ii].begin(), diffs[ii].end());
		for(int i = 0; i < D[u]; i++)
		{
			dp[u][ii] += diffs[ii][i];
		}
	}
}

int main()
{
	int N;
	scanf("%d", &N);
	
	int P[N + 69];
	for(int i = 2; i <= N; i++)
	{
		scanf("%d", P + i);
		adj[P[i]].push_back(i);
	}
	
	long long tot = 0;
	for(int i = 1; i <= N; i++)
	{
		scanf("%d", W + i);
		tot += W[i];
	}
	
	for(int i = 1; i <= N; i++)
	{
		scanf("%d", D + i);
	}
	
	dfs(1);
	
	long long mn, ans;
	mn = min(dp[1][0], dp[1][1]);
	ans = tot - mn * 2;
	printf("%lld\n", ans);
}
