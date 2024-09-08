#include <bits/stdc++.h>
using namespace std;

const long long INF = 1000000000000000000LL;

typedef pair<long long, long long> PII;

int n, m, k, t, p, q, a, b, c, d;
long long dist[200007];
bool active[200007];
vector<PII> edge[200007], starting[100007], ending[100007];
priority_queue<PII> pq;

int main() {
	scanf("%d%d%d%d%d%d",&n,&m,&k,&t,&p,&q);
	
	// There will be 2N nodes:
	// Node   1 -  N: Bu Dengklek is at station i OUTSIDE the train
	// Node N+1 - 2N: Bu Dengklek is at station i INSIDE the train
	
	// First set of edges is the ANGKOT
	for (int i = 1; i <= n; i++) {
		if (i + 1 <= n) edge[i].push_back(PII(i + 1, k));
		if (i - 1 >= 1) edge[i].push_back(PII(i - 1, k));
	}
	
	// Next is going inside and outside a train
	for (int i = 1; i <= n; i++) {
		edge[i].push_back(PII(n + i, t));
		edge[n + i].push_back(PII(i, 0));
	}
	
	// Lastly, the express, and precomputation of the commuters
	for (int i = 0; i < m; i++){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		edge[n + a].push_back(PII(n + b, d));
		edge[n + b].push_back(PII(n + a, d));
		
		starting[a].push_back(PII(-c,i));
		ending[b].push_back(PII(-c,i));
	}
	
	// And here are the commuters
	for (int i = 1; i <= n; i++) {
		// Lazy deletion
		while (!pq.empty() && !active[pq.top().second]) {
			pq.pop();
		}
		
		if (!pq.empty()) {
			edge[n + i - 1].push_back(PII(n + i, -pq.top().first));
			edge[n + i].push_back(PII(n + i - 1, -pq.top().first));
		}
		
		for (int j = 0; j < ending[i].size(); j++) {
			active[ending[i][j].second] = false;
		}
		
		for (int j = 0; j < starting[i].size(); j++) {
			pq.push(starting[i][j]);
			active[starting[i][j].second] = true;
		}
	}
	while (!pq.empty()) pq.pop();
	
	// Now we just run the Dijkstra's Algorithm
	for (int i = 1; i <= 2*n; i++) dist[i] = INF;
	dist[p] = 0;
	pq.push(PII(0, p));
	
	while (!pq.empty()) {
		int pos = pq.top().second;
		long long run = -pq.top().first;
		pq.pop();
		
		if (dist[pos] == run) {
			for (int i = 0; i < edge[pos].size(); i++) {
				if (run + edge[pos][i].second < dist[edge[pos][i].first]) {
					dist[edge[pos][i].first] = run + edge[pos][i].second;
					pq.push(PII(-dist[edge[pos][i].first], edge[pos][i].first));
				}
			}
		}
	}
	
	printf("%lld\n",dist[q]);
}