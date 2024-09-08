#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
const ll NN = 6e5 + 5;
ll n, k;
ll a[NN];
ll b[NN];
ll cek(ll X) {
	memset(b, 0, sizeof(b));
	set<pll> s;
	ll dob = 0;
	for(ll i = 1; i <= X; i++) {
		b[a[i]]++;
		if(b[a[i]] == 2) {
			dob++;
		}
		s.insert({a[i], b[a[i]]});
	}
	for(ll i = X; i <= n; i++) {
		if(i > X) {
			b[a[i]]++;
			if(b[a[i]] == 2) {
				dob++;
			}
			s.insert({a[i], b[a[i]]});

			s.erase({a[i - X], b[a[i - X]]});
			if(b[a[i - X]] == 2) {
				dob--;
			}
			b[a[i - X]]--;
		}
		auto it = s.begin();
		ll LO = (*it).fi;
		it = s.end();
		it--;
		ll HI = (*it).fi;
		if(dob == 0 && HI - LO + 1 <= k) {
			return 1;
		}
	}
	return 0;
}
int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> k;
	for(ll i = 1; i <= n; i++) {
		cin >> a[i];
		a[i + n] = a[i];
	}
	n *= 2;
	ll L = 1, R = k, has;
	while(L <= R) {
		ll C = (L + R) / 2;
		if(cek(C)) {
			has = k - C;
			L = C + 1;
		}
		else {
			R = C - 1;
		}
	}
	cout << has << "\n";
}
