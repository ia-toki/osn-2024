/*
 * Subtask 3
 * Time complexity: O(N^2M)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define f1 first
#define s2 second

using ii = pair<int, int>;

const int inf = 1e9 + 69;

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	int N; cin >> N;
	vector<ii> ivl(N);
	for (auto &[l, r] : ivl)
		cin >> l >> r;

	int M; cin >> M;
	vector<vector<int>> dp(M+1, vector<int>(N, inf));
	fill(dp[0].begin(), dp[0].end(), 0);

	for (int i = 0, a; i < M; ++i)
	{
		cin >> a;
		for (int nxt = 0; nxt < N; ++nxt) if (ivl[nxt].f1 <= a && a <= ivl[nxt].s2)
			for (int prv = 0; prv < N; ++prv)
				dp[i+1][nxt] = min(dp[i+1][nxt], dp[i][prv] + (prv != nxt));
	}

	int Z = inf;
	for (int i = 0; i < N; ++i) 
		Z = min(Z, dp[M][i]);
	
	cout << (Z == inf ? -1 : Z) << '\n';
	return 0;
}