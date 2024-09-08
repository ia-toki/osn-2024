#include <bits/stdc++.h>
using namespace std;

int n, m, res;
int row, col, rightT, downT;
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
		if (i % n == 0 && i % m == 1) rightT = i;
		if (i % n == 1 && i % m == 0) downT = i;
	}
	
	for (int i = 0; i < n; i++) {
		cout << "AKSELERASI " << downT << endl;
		for (int i = 0; i < n; i++) cin >> s[i];
		
		if (s[row][col] == '1') {
			cout << "EKSPERIMEN " << row + 1 << " " << col + 1 << endl;
			cin >> res;
			s[row][col] = 0;
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
	
	for (int j = 0; j < m; j++) {
		cout << "AKSELERASI " << rightT << endl;
		for (int i = 0; i < n; i++) cin >> s[i];
		
		for (int i = 0; i < n; i++) {
			if (s[i][col] == '1') {
				cout << "EKSPERIMEN " << i + 1 << " " << col + 1 << endl;
				cin >> res;
				s[i][col] = 0;
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