/*
 * Subtask 6
 * Time complexity: O(N lg N + M)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back
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
	sort(ivl.begin(), ivl.end());

	{
		vector<ii> sk;
		for (auto &[l, r] : ivl)
		{
			if (!sk.empty() && sk.back().s2 == l) sk.back().s2 = max(sk.back().s2, r);
			else if (sk.empty() || r > sk.back().s2) sk.pb({l, r});
		}
		ivl = sk; N = (int)ivl.size();
	}

	int M, Z = -1; cin >> M;
	for (int i = 0, j = -1, a; i < M; ++i)
	{
		cin >> a;

		// need to switch brake
		if (j == -1 || !(ivl[j].f1 <= a && a <= ivl[j].s2))
		{
			while (j+1 < N && a >= ivl[j+1].f1) ++j;
			if (j == -1 || !(ivl[j].f1 <= a && a <= ivl[j].s2)) { Z = -1; break; }
			Z++;
		}
	}

	cout << Z << '\n';
	return 0;
}