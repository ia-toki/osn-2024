/*
 * Full Solution
 * Time complexity: O((N+M) lg (N+M))
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back

using ii = pair<int, int>;

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	int N; cin >> N;
	vector<int> zip;
	vector<ii> ivl(N);
	for (auto &[l, r] : ivl)
		cin >> l >> r, zip.pb(l), zip.pb(r);

	int M; cin >> M;
	vector<int> A(M);
	for (int &a : A)
		cin >> a, zip.pb(a);

	sort(zip.begin(), zip.end());
	zip.resize(unique(zip.begin(), zip.end()) - zip.begin());
	for (auto &[l, r] : ivl)
	{
		l = (int)(lower_bound(zip.begin(), zip.end(), l) - zip.begin());
		r = (int)(lower_bound(zip.begin(), zip.end(), r) - zip.begin());
	}
	for (int &a : A)
		a = (int)(lower_bound(zip.begin(), zip.end(), a) - zip.begin());

	vector<int> pfx(zip.size(), -1);
	for (auto &[l, r] : ivl)
		pfx[l] = max(pfx[l], r);
	for (int i = 1; i < (int)zip.size(); ++i)
		pfx[i] = max(pfx[i], pfx[i-1]);

	int Z = 0, p = A[0], q = A[0];
	for (int a : A)
	{
		p = min(p, a); q = max(q, a);
		if (pfx[p] < q)
			Z++, p = q = a;
		if (pfx[p] < q)
		{
			Z = -1; break;
		}
	}

	cout << Z << '\n';
	return 0;
}