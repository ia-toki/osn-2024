#include <bits/stdc++.h>
using namespace std;

int n, m, res;
string s[30];

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> s[i];
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (s[i][j] == '1') {
			cout << "EKSPERIMEN " << i + 1 << " " << j + 1 << endl;
			fflush(stdout);
			cin >> res;
		}
	}
}