#include <bits/stdc++.h>
using namespace std;

int n, m, res;
int bestT, bestExp;
string s[30];

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> s[i];
	
	for (int t = 1; t <= n * m; t++) {
		cout << "AKSELERASI 1" << endl;
		for (int i = 0; i < n; i++) cin >> s[i];
		
		int exp = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s[i][j] == '1') exp++;
			}
		}
		
		if (exp > bestExp) {
			bestExp = exp;
			bestT = t;
		}
	}
	
	cout << "AKSELERASI " << bestT << endl;
	for (int i = 0; i < n; i++) cin >> s[i];
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '1') {
				cout << "EKSPERIMEN " << i + 1 << " " << j + 1 << endl;
				cin >> res;
			}
		}
	}
}