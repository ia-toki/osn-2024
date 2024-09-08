#include <bits/stdc++.h>
using namespace std;

int n,p;
int w[100007],d[100007];
vector<int> edge[100007];
long long mem[100007][2];

// minimize the sum of nodes with color 0 considering
// only the subtree rooted at "pos" with color "col"
long long DP(int pos, int col) {
	if (mem[pos][col] != -1) return mem[pos][col];
	
	// assume all children have the same color as the root
	long long sum = (col == 0 ? w[pos] : 0);
	for (int i = 0; i < edge[pos].size(); i++) {
		sum += DP(edge[pos][i],col);
	}
	
	// calculate "what if they are colored differently"
	vector<long long> changes;
	for (int i = 0; i < edge[pos].size(); i++) {
		changes.push_back(DP(edge[pos][i],1-col) - DP(edge[pos][i],col));
	}
	
	// greedily, change those who minimize the sum
	sort(changes.begin(), changes.end());
	for (int i = 0; i < d[pos]; i++) sum += changes[i];
	
	return mem[pos][col] = sum;
}

int main() {
	scanf("%d",&n);
	for (int i = 2; i <= n; i++) {
		scanf("%d",&p);
		edge[p].push_back(i);
	}
	for (int i = 1; i <= n; i++) scanf("%d",&w[i]);
	for (int i = 1; i <= n; i++) scanf("%d",&d[i]);
	
	long long sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += w[i];
		mem[i][0] = -1;
		mem[i][1] = -1;
	}
	printf("%lld\n",sum - 2 * min(DP(1,1),DP(1,0)));
}