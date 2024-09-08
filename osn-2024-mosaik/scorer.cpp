#include <bits/stdc++.h>
using namespace std;

ifstream tc_in, tc_out;
FILE* con_out;

const int MAX_OPERATIONS = 200000;
const string OP_ROW = "BARIS";
const string OP_COL = "KOLOM";
const string WHITE = ".";
const string BLACK = "#";

int N, M;
vector<string> S;

int numOperations, numMatches;
vector<int> ROW, COL;
vector<char> BW_ROW, BW_COL;

// ======================================
// ===== RETURN & SCORING FUNCTIONS =====
// ======================================

int AC() {
	cout << "AC" << endl;
	return 0;
}

int OK(double score, int numMatches) {
	cout << "OK" << endl;
	cout << fixed << setprecision(2) << 100.0 * score << "% " << numMatches << "/" << N * M << endl;
	return 0;
}

int WA() {
	cout << "WA" << endl;
	return 0;
}

int getFinalVerdict(int numMatches) {	
	if (numMatches == N * M) {
		return AC();
	} else {
		double score = pow((double) numMatches / (N * M), 3.0);
		return OK(score, numMatches);
	}
}

// ============================
// ===== HELPER FUNCTIONS =====
// ============================

void calculateNumMatches() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (ROW[i] > COL[j]) {
				if (S[i][j] == BW_ROW[i]) numMatches++;
			} else {
				if (S[i][j] == BW_COL[j]) numMatches++;
			}
		}
	}
}

// ==========================
// ===== MAIN FUNCTIONS =====
// ==========================

void readInput(char* argv) {
	ifstream tc_in(argv);
	
	tc_in >> N >> M;
	for (int i = 0; i < N; i++) {
		string tmp;
		tc_in >> tmp;
		S.push_back(tmp);
	}
}

void readOutput(char* argv) {
	ifstream tc_out(argv);
}

void readContestant(char* argv) {
	con_out = fopen(argv, "r");
}

int doGrading() {
	for (int i = 0; i < N; i++) ROW.push_back(0);
	for (int j = 0; j < M; j++) COL.push_back(0);
	for (int i = 0; i < N; i++) BW_ROW.push_back(WHITE[0]);
	for (int j = 0; j < M; j++) BW_COL.push_back(WHITE[0]);
	
	if (fscanf(con_out, "%d", &numOperations) != 1) return WA();
	if (numOperations > MAX_OPERATIONS) return WA();
	
	for (int i = 1; i <= numOperations; i++) {
		char op[101];
		if (fscanf(con_out, "%99s", op) != 1) return WA();
		
		if (op == OP_ROW) {
			int x;
			if (fscanf(con_out, "%d", &x) != 1) return WA();
			if (x < 1 || x > N) return WA();
			
			char color[101];
			if (fscanf(con_out, "%99s", color) != 1) return WA();
			if (color != WHITE && color != BLACK) return WA();
			
			x--;
			ROW[x] = i;
			BW_ROW[x] = color[0];
			
		} else if (op == OP_COL) {
			int y;
			if (fscanf(con_out, "%d", &y) != 1) return WA();
			if (y < 1 || y > M) return WA();
			
			char color[101];
			if (fscanf(con_out, "%99s", color) != 1) return WA();
			if (color != WHITE && color != BLACK) return WA();
			
			y--;
			COL[y] = i;
			BW_COL[y] = color[0];
			
		} else {
			return WA();
		}
	}
	
	char excess[101];
	if (fscanf(con_out, "%99s", excess) == 1) return WA();
	
	calculateNumMatches();
	return getFinalVerdict(numMatches);
}

int main(int argc, char* argv[]) {
	readInput(argv[1]);
	readOutput(argv[2]);
	readContestant(argv[3]);
	return doGrading();
}