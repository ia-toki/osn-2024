#include <bits/stdc++.h>
using namespace std;

int n, m, res;
int row, col;
int rightT[30], downT[30];
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
	
	for (int i = 1; i <= 1000; i++) {
		if (i % n == 0) rightT[i % m] = i;
		if (i % m == 0) downT[i % n] = i;
	}
	
	for (int i = 1; i < n; i *= 2) {
		cout << "AKSELERASI " << downT[i] << endl;
		for (int i = 0; i < n; i++) cin >> s[i];
		
		for (int k = 0; k < 2 * i; k++) {
			if (s[(row + k) % n][col] == '1') {
				cout << "EKSPERIMEN " << (row + k) % n + 1 << " " << col + 1 << endl;
				cin >> res;
				s[(row + k) % n][col] = 0;
			}
		}
		
		bool allEmpty = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s[i][j] == '1') allEmpty = false;
			}
		}
		if (allEmpty) return 0;
	}
	
	for (int i = 0; i < n; i++) {
		if (s[i][col] == '1') {
			cout << "EKSPERIMEN " << i + 1 << " " << col + 1 << endl;
			cin >> res;
			s[i][col] = 0;
		}
		
		bool allEmpty = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s[i][j] == '1') allEmpty = false;
			}
		}
		if (allEmpty) return 0;
	}
	
	for (int j = 1; j < m; j *= 2) {
		cout << "AKSELERASI " << rightT[j] << endl;
		for (int i = 0; i < n; i++) cin >> s[i];
		
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < 2 * j; k++) {
				if (s[i][(col + k) % m] == '1') {
					cout << "EKSPERIMEN " << i + 1 << " " << (col + k) % m + 1 << endl;
					cin >> res;
					s[i][(col + k) % m] = 0;
				}
			}
		}
		
		bool allEmpty = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s[i][j] == '1') allEmpty = false;
			}
		}
		if (allEmpty) return 0;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '1') {
				cout << "EKSPERIMEN " << i + 1 << " " << j + 1 << endl;
				cin >> res;
			}
		}
	}
}