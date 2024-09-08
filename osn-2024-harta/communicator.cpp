#include <bits/stdc++.h>
using namespace std;

ifstream tc_in;

const int N = 256;
const int MAX_COINS = 512;
const string ASK = "TANYA";
const string ANSWER = "JAWAB";

int ANS;
int numCoins;
int a[N + 7];

// ======================================
// ===== RETURN & SCORING FUNCTIONS =====
// ======================================

int AC() {
	cerr << "AC" << endl;
	return 0;
}

int OK(double percentage, int coins) {
	cerr << "OK" << endl;
	cerr << fixed << setprecision(2) << percentage << "% " << coins << " Kwakkoin" << endl;
	return 0;
}

int WA() {
	cerr << "WA" << endl;
	return 0;
}

int getFinalVerdict(int numCoins) {	
	if (numCoins <= 6) {
		return AC();
	} else {
		double percentage = 100.0 - 5 * log2(numCoins - 5);
		return OK(percentage, numCoins);
	}
}

// ============================
// ===== HELPER FUNCTIONS =====
// ============================

// none

// ==========================
// ===== MAIN FUNCTIONS =====
// ==========================

void readInput(char* argv) {
	ifstream tc_in(argv);
	tc_in >> ANS;
}

void initInteraction() {
	// none
}

int doInteraction() {
	while (numCoins <= MAX_COINS) {
		char op[101];
		if (!(scanf("%99s", op))) return WA();
		
		if (op == ASK) {
			int k;
			if (!(scanf("%d", &k))) return WA();
			if (k < 1 || k > N) return WA();
			
			numCoins += ceil((double) N / k);
			if (numCoins > MAX_COINS) return WA();
			
			for (int i = 0; i < k; i++) {
				if (!(scanf("%d", &a[i]))) return WA();
				if (a[i] < 1 || a[i] > N) return WA();
				if (i > 0 && a[i] <= a[i-1]) return WA();
			}
			
			int d = N;
			for (int i = 0; i < k; i++) {
				d = min(d, abs(ANS - a[i]));
				d = min(d, N - abs(ANS - a[i]));
			}
			printf("%d\n", d);
			fflush(stdout);
			
		} else if (op == ANSWER) {
			int h;
			if (!(scanf("%d", &h))) return WA();
			if (h < 1 || h > N) return WA();
			
			if (h == ANS) {
				return getFinalVerdict(numCoins);
			} else {
				return WA();
			}
			
		} else {
			return WA();
		}
	}
}

int main(int argc, char* argv[]) {
	readInput(argv[1]);
	initInteraction();
	return doInteraction();
}