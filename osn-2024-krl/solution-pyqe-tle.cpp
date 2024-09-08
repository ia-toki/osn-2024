#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long INF = 1e18;

int main()
{
	int N, M, K, T, P, Q;
	scanf("%d%d%d%d%d%d", &N, &M, &K, &T, &P, &Q);
	
	vector<pair<int, int>> adj[N * 2 + 69];
	for(int i = 1; i <= N - 1; i++)
	{
		adj[i].push_back({i + 1, K});
		adj[i + 1].push_back({i, K});
	}
	
	for(int i = 1; i <= N; i++)
	{
		adj[i].push_back({N + i, T});
		adj[N + i].push_back({i, 0});
	}
	
	int A[M + 69], B[M + 69], C[M + 69], D[M + 69];
	vector<pair<int, int>> upds[N + 69];
	for(int i = 1; i <= M; i++)
	{
		scanf("%d%d%d%d", A + i, B + i, C + i, D + i);
		
		adj[N + A[i]].push_back({N + B[i], D[i]});
		adj[N + B[i]].push_back({N + A[i], D[i]});
		
		upds[A[i]].push_back({0, C[i]});
		upds[B[i]].push_back({1, C[i]});
	}
	
	multiset<int> vals;
	for(int i = 1; i <= N - 1; i++)
	{
		for(int j = 0; j < upds[i].size(); j++)
		{
			int op, w;
			op = upds[i][j].fr;
			w = upds[i][j].sc;
			if(op == 0)
			{
				vals.insert(w);
			}
			else
			{
				vals.erase(vals.find(w));
			}
		}
		
		if(!vals.empty())
		{
			int mn = *vals.begin();
			adj[N + i].push_back({N + i + 1, mn});
			adj[N + i + 1].push_back({N + i, mn});
		}
	}
	
	long long dis[N * 2 + 69];
	for(int i = 1; i <= N * 2; i++)
	{
		dis[i] = INF;
	}
	
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	pq.push({0, P});
	dis[P] = 0;
	while(!pq.empty())
	{
		long long curDis = pq.top().fr;
		int u = pq.top().sc;
		pq.pop();
		
		if(u == Q)
		{
			break;
		}
		
		for(int i = 0; i < adj[u].size(); i++)
		{
			int v, w;
			v = adj[u][i].fr;
			w = adj[u][i].sc;
			
			if(curDis + w < dis[v])
			{
				pq.push({curDis + w, v});
				dis[v] = curDis + w;
			}
		}
	}
	
	printf("%lld\n", dis[Q]);
}
