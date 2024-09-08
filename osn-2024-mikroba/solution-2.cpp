#include <bits/stdc++.h>
using namespace std;

int n, m, res;
int row, col;
string s[30];

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> s[i];
	
	row = -1;
	col = -1;
	
	for (int i = 0; i < n; i++) {
		bool allEmpty = true;
		for (int j = 0; j < m; j++) if (s[i][j] == '1') allEmpty = false;
		if (allEmpty) row = i;
	}
	
	for (int j = 0; j < m; j++) {
		bool allEmpty = true;
		for (int i = 0; i < n; i++) if (s[i][j] == '1') allEmpty = false;
		if (allEmpty) col = j;
	}
	
	// This is to earn some points on bigger subtasks
	if (row == -1 || col == -1) {
		int fewestRemove = n * m;
		
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				int toRemove = 0;
				
				for (int i = 0; i < n; i++) {
					if (s[i][y] == '1') toRemove++;
				}
				for (int j = 0; j < m; j++) {
					if (s[x][j] == '1') toRemove++;
				}
				if (s[x][y] == '1') toRemove--;
				
				if (toRemove < fewestRemove) {
					fewestRemove = toRemove;
					row = x;
					col = y;
				}
			}
		}
		
		for (int i = 0; i < n; i++) {
			if (s[i][col] == '1') {
				cout << "EKSPERIMEN " << i + 1 << " " << col + 1 << endl;
				cin >> res;
				s[i][col] = 0;
			}
		}
		
		for (int j = 0; j < m; j++) {
			if (s[row][j] == '1') {
				cout << "EKSPERIMEN " << row + 1 << " " << j + 1 << endl;
				cin >> res;
				s[row][j] = 0;
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
	
	while (true) {
		cout << "AKSELERASI 1" << endl;
		for (int i = 0; i < n; i++) cin >> s[i];
		
		for (int i = 0; i < n; i++) {
			if (s[i][col] == '1') {
				cout << "EKSPERIMEN " << i + 1 << " " << col + 1 << endl;
				cin >> res;
				s[i][col] = 0;
			}
		}
		
		for (int j = 0; j < m; j++) {
			if (s[row][j] == '1') {
				cout << "EKSPERIMEN " << row + 1 << " " << j + 1 << endl;
				cin >> res;
				s[row][j] = 0;
			}
		}
		
		bool allEmpty = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s[i][j] == '1') allEmpty = false;
			}
		}
		if (allEmpty) break;
	}
}