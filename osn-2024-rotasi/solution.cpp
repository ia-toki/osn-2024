#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
int n, k, a[MX];
bool vis[MX];

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		a[n + i] = a[i];
	}

	deque<pair<int, int> > mx, mn;
	mx.push_back({a[1], 1});
	mn.push_back({a[1], 1});
	vis[a[1]] = 1;

	int ans = 2 * n;
	for (int l = 1, r = 1; l <= 2 * n && r <= 2 * n;) {
		ans = min(ans, k - (r - l + 1));
		if (l == 2 * n && r == 2 * n) break;

		// try add r+1
		if (r + 1 > 2 * n || vis[a[r + 1]] || max(mx.front().first, a[r + 1]) - min(mn.front().first, a[r + 1]) >= k) {
			// move to [l+1, r]
			vis[a[l]] = 0;
			if (mx.front().second == l) mx.pop_front();
			if (mn.front().second == l) mn.pop_front();
			l++;
			if (l > r) {
				vis[a[r+1]] = 1;
				while (mx.size() && mx.back().first < a[r+1]) mx.pop_back();
				mx.push_back({a[r + 1], r + 1});
				while (mn.size() && mn.back().first > a[r+1]) mn.pop_back();
				mn.push_back({a[r + 1], r + 1});
				r++;
			} 
		} else {
			// move to [l, r+1]
			vis[a[r+1]] = 1;
			while (mx.size() && mx.back().first < a[r+1]) mx.pop_back();
			mx.push_back({a[r + 1], r + 1});
			while (mn.size() && mn.back().first > a[r+1]) mn.pop_back();
			mn.push_back({a[r + 1], r + 1});
			r++;
		}
	}

	printf("%d\n", ans);
}
