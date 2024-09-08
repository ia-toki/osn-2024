#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int MAX_NM = 100000;
const int MAX_N_TIMES_M = 2000000;
const char WHITE_TILE = '.';
const char BLACK_TILE = '#';

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M;
	vector<string> S;

	void InputFormat() {
		LINE(N, M);
		LINES(S) % SIZE(N);
	}

	void StyleConfig() {
		CustomScorer();
	}

	void Constraints() {
		CONS(2 <= N && N <= MAX_NM);
		CONS(2 <= M && M <= MAX_NM);
		CONS((long long) N * M <= MAX_N_TIMES_M);
		CONS(allValidLength());
		CONS(allBlackOrWhite());
	}

	void Subtask1() {
		Points(20);
		CONS(N == 6);
		CONS(M == 9);
	}
	
	void Subtask2() {
		Points(20);
		CONS(N == 12);
		CONS(M == 100);
	}
	
	void Subtask3() {
		Points(20);
		CONS(N == 2);
		CONS(M == MAX_NM);
	}
	
	void Subtask4() {
		Points(20);
		CONS(N == 1234);
		CONS(M == 1234);
	}
	
	void Subtask5() {
		Points(20);
		CONS(N == MAX_NM);
		CONS(M == 20);
	}
	
private:
	bool allValidLength() {
		for (int i = 0; i < N; i++) {
			if (S[i].length() != M) return false;
		}
		return true;
	}

	bool allBlackOrWhite() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (S[i][j] != BLACK_TILE && S[i][j] != WHITE_TILE) return false;
			}
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1});
		
		Input({
			"6 9",
			"##.###.##",
			".#.#.#.#.",
			"##.###.##",
			".#.....#.",
			"#########",
			"##.###.##",
		});
	}

	void BeforeTestCase() {
		S.clear();
	}

	void TestGroup1() {
		Subtasks({1});
		CASE(N = 6, M = 9, S = {
			{"##.###.##"},
			{".#.#.#.#."},
			{"##.###.##"},
			{".#.....#."},
			{"#########"},
			{"##.###.##"}
		});
	}

	void TestGroup2() {
		Subtasks({2});
		CASE(N = 12, M = 100, S = {
			{"####################################################################################################"},
			{"#############################################.......################################################"},
			{"#########################################..............#############################################"},
			{"########################################..................##########################################"},
			{"################################............................########################################"},
			{"###########################......................................###################################"},
			{"#########################.........................................##################################"},
			{"########################..................................................##########################"},
			{"#####################...........................................................####################"},
			{"###################..............................................................###################"},
			{"################......................................................................##############"},
			{"#########.........................................................................................##"}
		});
	}
	
	void TestGroup3() {
		Subtasks({3});
		CASE(N = 2, M = MAX_NM, buildTC3());
	}
	
	void TestGroup4() {
		Subtasks({4});
		CASE(N = 1234, M = 1234, buildTC4());
	}
	
	void TestGroup5() {
		Subtasks({5});
		CASE(N = MAX_NM, M = 20, buildTC5(2000000000)); // Beware, this may take 1-2 minutes
	}

private:
	void buildTC3() {
		string tmp;
		for (int j = 0; j < M; j++) tmp += '?';
		for (int i = 0; i < N; i++) S.push_back(tmp);
		
		for (int j = 0; j < M; j++) {
			int x = rnd.nextInt(3);
			
			if (x == 0) {
				S[0][j] = WHITE_TILE;
				S[1][j] = WHITE_TILE;
			} else if (x == 1) {
				S[0][j] = BLACK_TILE;
				S[1][j] = WHITE_TILE;
			} else {
				S[0][j] = BLACK_TILE;
				S[1][j] = BLACK_TILE;
			}
		}
	}
	
	void buildTC4() {
		string tmp;
		for (int j = 0; j < M; j++) tmp += '?';
		for (int i = 0; i < N; i++) S.push_back(tmp);
		
		vector<int> ROW, COL;
		for (int i = 1; i <= N+M; i += 2) ROW.push_back(i);
		for (int i = 2; i <= N+M; i += 2) COL.push_back(i);
		
		vector<char> BW_ROW, BW_COL;
		for (int i = 0; i < N; i++) BW_ROW.push_back(BLACK_TILE);
		for (int j = 0; j < M; j++) BW_COL.push_back(WHITE_TILE);
		
		rnd.shuffle(ROW.begin(), ROW.end());
		rnd.shuffle(COL.begin(), COL.end());
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (ROW[i] > COL[j]) {
					S[i][j] = BW_ROW[i];
				} else {
					S[i][j] = BW_COL[j];
				}
			}
		}
	}
	
	void buildTC5(int rep) {
		string tmp;
		for (int j = 0; j < M; j++) tmp += '?';
		for (int i = 0; i < N; i++) S.push_back(tmp);
		
		vector<int> ROW, COL;
		for (int i = 0; i < N; i++) ROW.push_back(0);
		for (int j = 0; j < M; j++) COL.push_back(0);
		
		vector<char> BW_ROW, BW_COL;
		for (int i = 0; i < N; i++) BW_ROW.push_back(rnd.nextInt(2) ? BLACK_TILE : WHITE_TILE);
		for (int j = 0; j < M; j++) BW_COL.push_back(rnd.nextInt(2) ? BLACK_TILE : WHITE_TILE);
		
		for (int i = 1; i <= rep; i++) {
			int x = rnd.nextInt(N + M);
			
			if (x < N) {
				ROW[x] = i;
			} else {
				COL[x - N] = i;
			}
		}
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (ROW[i] > COL[j]) {
					S[i][j] = BW_ROW[i];
				} else {
					S[i][j] = BW_COL[j];
				}
			}
		}
	}
};
