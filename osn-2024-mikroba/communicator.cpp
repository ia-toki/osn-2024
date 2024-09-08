#include <bits/stdc++.h>
using namespace std;

ifstream tc_in;

const int MAX_T = 1000;
const int MAX_ACCELERATE = 1000;
const string ACCELERATE = "AKSELERASI";
const string EXPERIMENT = "EKSPERIMEN";

const int KK = (1 << 1); // KANAN/RIGHT-microbe
const int BB = (1 << 2); // BAWAH/DOWN-microbe

int N, M;
int numMicrobesInit, numMicrobes, numAccelerate, numSuccess;
vector<vector<int>> G;

// ======================================
// ===== RETURN & SCORING FUNCTIONS =====
// ======================================

int AC() {
	cerr << "AC" << endl;
	return 0;
}

int OK(double accuracy, double efficiency, double performance) {
	cerr << "OK" << endl;
	cerr << fixed << setprecision(2) << 100.0 * performance << "% ";
	cerr << "AKURASI: " << fixed << setprecision(2) << 100.0 * accuracy << "%, ";
	cerr << "EFISIENSI: " << fixed << setprecision(2) << 100.0 * efficiency << "%";
	cerr << endl;
	return 0;
}

int WA() {
	cerr << "WA" << endl;
	return 0;
}

int getFinalVerdict(int numSuccess, int numAccelerate) {	
	if (numSuccess == numMicrobesInit && numAccelerate <= 9) {
		return AC();
		
	} else {
		double accuracy = pow((double) numSuccess / numMicrobesInit, 3.0);
		double efficiency = (numAccelerate <= 9) ? 1.0 : 1.0 - 0.05 * log2(numAccelerate - 8);
		double performance = accuracy * efficiency;
		
		return OK(accuracy, efficiency, performance);
	}
}

// ============================
// ===== HELPER FUNCTIONS =====
// ============================

void printGrid() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d", (G[i][j] == 0) ? 0 : 1);
		}
		printf("\n");
	}
	fflush(stdout);
}

void accelerate(int T) {
	vector<int> TMP;
	vector<vector<int>> TMP2;
	for (int j = 0; j < M; j++) TMP.push_back(0);
	for (int i = 0; i < N; i++) TMP2.push_back(TMP);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (G[i][j] & KK) TMP2[i][(j + T) % M] |= KK;
			if (G[i][j] & BB) TMP2[(i + T) % N][j] |= BB;
		}
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			G[i][j] = TMP2[i][j];
		}
	}
}

// ==========================
// ===== MAIN FUNCTIONS =====
// ==========================

void readInput(char* argv) {
	ifstream tc_in(argv);
	tc_in >> N >> M;
	
	vector<int> TMP;
	for (int j = 0; j < M; j++) TMP.push_back(0);
	for (int i = 0; i < N; i++) G.push_back(TMP);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tc_in >> G[i][j];
		}
	}
}

void initInteraction() {
	numMicrobesInit = 0;
	numMicrobes = 0;
	numAccelerate = 0;
	numSuccess = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (G[i][j] & KK) numMicrobesInit++;
			if (G[i][j] & BB) numMicrobesInit++;
		}
	}
	
	numMicrobes = numMicrobesInit;
	printf("%d %d\n", N, M);
	printGrid();
}

int doInteraction() {
	while (numMicrobes > 0) {
		char op[101];
		if (scanf("%99s", op) != 1) return WA();
		
		if (op == ACCELERATE) {
			if (++numAccelerate > MAX_ACCELERATE) return WA();
			
			int t;
			if (scanf("%d", &t) != 1) return WA();
			if (t < 1 || t > MAX_T) return WA();
			
			accelerate(t);
			printGrid();
			
		} else if (op == EXPERIMENT) {
			int x, y;
			if (scanf("%d", &x) != 1) return WA();
			if (x < 1 || x > N) return WA();
			if (scanf("%d", &y) != 1) return WA();
			if (y < 1 || y > M) return WA();
			
			if (G[x-1][y-1] == 0) {
				return WA();
				
			} else if (G[x-1][y-1] == (KK | BB)) {
				G[x-1][y-1] = 0;
				numMicrobes -= 2;
				
				printf("2\n");
				fflush(stdout);
				
			} else {
				G[x-1][y-1] = 0;
				numMicrobes -= 1;
				numSuccess++;
				
				printf("1\n");
				fflush(stdout);
			}
			
		} else {
			return WA();
		}
	}
	
	char excess[101];
	if (scanf("%99s", excess) == 1) return WA();
	
	return getFinalVerdict(numSuccess, numAccelerate);
}

int main(int argc, char* argv[]) {
	readInput(argv[1]);
	initInteraction();
	return doInteraction();
}
