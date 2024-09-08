#include <bits/stdc++.h>
using namespace std;

const int NUM_RANDOM = 8; // Adjustable

int n, m, res;
int bestT, bestExp, sumAccel, finalT;
string s[30];

int main() {
	srand(1412); // Adjustable
	
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> s[i];
	
	bestT = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '1') bestExp++;
		}
	}
	
	sumAccel = 0;
	for (int k = 0; k < NUM_RANDOM; k++) {
		int t = rand() % 1000 + 1;
		sumAccel = (sumAccel + t) % (n * m);

		cout << "AKSELERASI " << t << endl;
		for (int i = 0; i < n; i++) cin >> s[i];
		
		int exp = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s[i][j] == '1') exp++;
			}
		}
		
		if (exp > bestExp) {
			bestExp = exp;
			bestT = sumAccel;
		}
	}
	
	for (int i = 1; i <= 1000; i++) {
		if ((sumAccel + i) % (n * m) == bestT) finalT = i;
	}
	
	cout << "AKSELERASI " << finalT << endl;
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