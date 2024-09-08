/*
 * Subtask 4
 * Time complexity: O(NM)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ii = pair<int, int>;

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	int N; cin >> N;
	vector<ii> ivl(N);
	for (auto &[l, r] : ivl)
		cin >> l >> r;

	int M, Z = 0; cin >> M;
	for (int i = 0, a, p = 1e9, q = 0; i < M; ++i)
	{
		cin >> a;
		p = min(p, a); q = max(q, a);

		bool ok = false, impos = true;
		for (auto &[l, r] : ivl) 
		{
			if (l <= a && a <= r) impos = false;
			if (l <= p && q <= r) { ok = true; break; }
		}

		if (impos) { Z = -1; break; }
		if (!ok) Z++, p = q = a;
	}

	cout << Z << '\n';
	return 0;
}