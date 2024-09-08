/*
 * Subtask 2
 * Time complexity: O((N + M) lg N)
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
	sort(ivl.begin(), ivl.end());

	int M, prv = -1, Z = -1; cin >> M;
	for (int i = 0, a; i < M; ++i)
	{
		cin >> a;

		int id = (int)(lower_bound(ivl.begin(), ivl.end(), make_pair(a, inf)) - ivl.begin()) - 1;
		if (0 <= id && id < N && ivl[id].f1 <= a && a <= ivl[id].s2) Z += prv != id, prv = id;
		else { Z = -1; break; }
	}

	cout << Z << '\n';
	return 0;
}