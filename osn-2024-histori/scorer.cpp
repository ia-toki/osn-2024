#include <bits/stdc++.h>
using namespace std;

ifstream tc_in, tc_out;
FILE* con_out;

const double EPS = 0.01;

int N;
int A[100007];
int MINN[100007], MAXX[100007];
double AVGG[100007];

// ======================================
// ===== RETURN & SCORING FUNCTIONS =====
// ======================================

int AC() {
	cout << "AC" << endl;
	return 0;
}

int OK(double percentage) {
	cout << "OK" << endl;
	cout << fixed << setprecision(2) << percentage << "%" << endl;
	return 0;
}

int WA() {
	cout << "WA" << endl;
	return 0;
}

int getFinalVerdict(bool correctMinMax, bool correctAvg) {	
	if (!correctMinMax) return WA();
	if (!correctAvg) return OK(50);
	return AC();
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
	
	tc_in >> N;
	for (int i = 0; i < N; i++) {
		tc_in >> A[i];
	}
}

void readOutput(char* argv) {
	ifstream tc_out(argv);
	
	for (int i = 0; i < N; i++) {
		tc_out >> MINN[i] >> MAXX[i] >> AVGG[i];
	}
}

void readContestant(char* argv) {
	con_out = fopen(argv, "r");
}

int doGrading() {
	bool correctMinMax = true;
	bool correctAvg = true;
	
	for (int i = 0; i < N; i++) {
		int conMin;
		if (fscanf(con_out, "%d", &conMin) != 1) return WA();
		
		int conMax;
		if (fscanf(con_out, "%d", &conMax) != 1) return WA();
		
		double conAvg;
		if (fscanf(con_out, "%lf", &conAvg) != 1) return WA();
		
		if (conMin != MINN[i]) correctMinMax = false;
		if (conMax != MAXX[i]) correctMinMax = false;
		if (abs(conAvg - AVGG[i]) >= EPS) correctAvg = false;
	}
	
	char excess[101];
	if (fscanf(con_out, "%99s", excess) == 1) return WA();
	
	return getFinalVerdict(correctMinMax, correctAvg);
}

int main(int argc, char* argv[]) {
	readInput(argv[1]);
	readOutput(argv[2]);
	readContestant(argv[3]);
	return doGrading();
}