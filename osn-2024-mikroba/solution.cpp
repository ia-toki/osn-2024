#include <bits/stdc++.h>
using namespace std;

int n, m, res;
int row, col;
string s[30];

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> s[i];
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '0') {
				row = i;
				col = j;
			}
		}
	}
	
	for (int t = 1; t < n * m; t *= 2) {
		cout << "AKSELERASI " << t << endl;
		for (int i = 0; i < n; i++) cin >> s[i];
		
		int x = row;
		int y = (col + 2 * t - 1) % m;
		for (int k = 0; k < 2 * t; k++) {
			if (s[x][y] == '1') {
				cout << "EKSPERIMEN " << x + 1 << " " << y + 1 << endl;
				cin >> res;
				s[x][y] = 0;
			}
			
			x = (x + 1) % n;
			y = (y - 1 + m) % m;
		}
		
		bool allEmpty = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s[i][j] == '1') allEmpty = false;
			}
		}
		if (allEmpty) return 0;
	}
}