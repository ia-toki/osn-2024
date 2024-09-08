#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int MAX_NM = 23;
const int MAX_T = 1000;
const int KK = (1 << 1); // KANAN/RIGHT-microbe
const int BB = (1 << 2); // BAWAH/DOWN-microbe

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M;
	bool IS_GEN_SUB_4; // To "silent" tcframe error of not assigning satisfied subtask
	vector<vector<int>> G;

	void InputFormat() {
		LINE(N, M);
		GRID(G) % SIZE(N, M);
	}

	void StyleConfig() {
		InteractiveEvaluator();
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}
	
	void Constraints() {
		CONS(2 <= N && N <= MAX_NM);
		CONS(2 <= M && M <= MAX_NM);
		CONS(N != M);
		CONS(isPrime(N) && isPrime(M));
		CONS(hasNonEmptyCell());
		CONS(hasEmptyCell());
		CONS(atMostTwoMicrobes());
	}

	void Subtask1() {
		Points(8);
		CONS(IS_GEN_SUB_4 == false);
		CONS(N == 3);
		CONS(M == 5);
		
		vector<vector<int>> SAMPLE_TC = {
			{KK^BB,     0,     0, KK^BB,    BB},
			{    0,     0, KK   ,     0, KK   },
			{   BB,     0, KK   ,     0, KK   }
		};
		CONS(G == SAMPLE_TC);
	}
	
	void Subtask2() {
		Points(17);
		CONS(IS_GEN_SUB_4 == false);
		CONS(hasEmptyRow());
		CONS(hasEmptyCol());
	}
	
	void Subtask3() {
		Points(19);
		CONS(IS_GEN_SUB_4 == false);
		CONS(hasEmptyCol());
	}
	
	void Subtask4() {
		Points(30);
		CONS(IS_GEN_SUB_4 == true);
		CONS(possibleZeroOneMicrobe());
	}
	
	void Subtask5() {
		Points(26);
	}
	
private:
	bool isPrime(int x) {
		if (x <= 1) return false;
		for (int i = 2; i < x; i++) {
			if (x % i == 0) return false;
		}
		return true;
	}
	
	bool hasNonEmptyCell() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (
					G[i][j] == KK ||
					G[i][j] == BB ||
					G[i][j] == (KK^BB)
				) return true;
			}
		}
		return false;
	}
	
	bool hasEmptyCell() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (G[i][j] == 0) return true;
			}
		}
		return false;
	}
	
	bool atMostTwoMicrobes() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (
					G[i][j] !=  0 &&
					G[i][j] != KK &&
					G[i][j] != BB &&
					G[i][j] != (KK^BB)
				) return false;
			}
		}
		return true;
	}
	
	bool hasEmptyRow() {
		for (int i = 0; i < N; i++) {
			bool allEmpty = true;
			for (int j = 0; j < M; j++) {
				if (G[i][j] != 0) allEmpty = false;
			}
			if (allEmpty) return true;
		}
		return false;
	}
	
	bool hasEmptyCol() {
		for (int j = 0; j < M; j++) {
			bool allEmpty = true;
			for (int i = 0; i < N; i++) {
				if (G[i][j] != 0) allEmpty = false;
			}
			if (allEmpty) return true;
		}
		return false;
	}
	
	vector<vector<int>> accel(vector<vector<int>> A, int T) {
		vector<int> TMP;
		vector<vector<int>> TMP2;
		for (int j = 0; j < M; j++) TMP.push_back(0);
		for (int i = 0; i < N; i++) TMP2.push_back(TMP);
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (A[i][j] & KK) TMP2[i][(j + T) % M] |= KK;
				if (A[i][j] & BB) TMP2[(i + T) % N][j] |= BB;
			}
		}
		
		return TMP2;
	}
	
	bool isZeroOneMicrobe(vector<vector<int>> A) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (A[i][j] == (KK ^ BB)) return false;
			}
		}
		return true;
	}
	
	bool possibleZeroOneMicrobe() {
		for (int t = 1; t <= MAX_T; t++) {
			if (isZeroOneMicrobe(accel(G, t))) return true;
		}
		return false;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	int X, Y;
	vector<int> ODD_PRIMES;
	
	void SampleTestCase1() {
		Subtasks({1, 3, 5});
		
		Input({
			"3 5",
			"6 0 0 6 4",
			"0 0 2 0 2",
			"4 0 2 0 2",
		});
	}
	
	void BeforeTestCase() {
		IS_GEN_SUB_4 = false;
		ODD_PRIMES = {3, 5, 7, 11, 13, 17, 19, 23};
		rnd.shuffle(ODD_PRIMES.begin(), ODD_PRIMES.end());
	}

	void TestGroup1() {
		Subtasks({1, 3, 5});
		// None other than the sample
	}

	void TestGroup2() {
		Subtasks({2, 3, 5});
		
		CASE(init(2, 3), G[X][Y] = KK);
		CASE(init(3, 2), G[X][Y] = (KK^BB), G[(X + 1) % N][Y] = (KK^BB));
		CASE(init(19, 23), G[X][Y] = BB);
		CASE(init(23, 19), G[X][Y] = (KK^BB));
		
		CASE(init(ODD_PRIMES[0], ODD_PRIMES[1]), fill({KK^BB}, {100}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(ODD_PRIMES[2], ODD_PRIMES[3]), fill({BB}, {100}), fill({KK, 0}, {65, 35}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(ODD_PRIMES[4], ODD_PRIMES[5]), fill({ 0, KK, BB, KK^BB}, {20, 10, 10, 60}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(ODD_PRIMES[6], ODD_PRIMES[7]), fill({ 0, KK, BB, KK^BB}, {15, 35, 35, 15}), assignCol(Y, 0), assignRow(X, 0));
		
		CASE(init(19, 23), fill({KK^BB}, {100}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(19, 23), fill({KK, BB}, {50, 50}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(23, 19), fill({KK}, {100}), fill({BB, 0}, {20, 80}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(19, 23), fill({BB}, {100}), fill({KK, 0}, {65, 35}), assignCol(Y, 0), assignRow(X, 0));
		
		CASE(init(19, 23), fill({ 0, KK, BB, KK^BB}, { 0, 10, 30, 60}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(23, 19), fill({ 0, KK, BB, KK^BB}, {25, 25, 25, 25}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(19, 23), fill({ 0, KK, BB, KK^BB}, {20, 10, 10, 60}), assignCol(Y, 0), assignRow(X, 0));
		CASE(init(23, 19), fill({ 0, KK, BB, KK^BB}, {15, 35, 35, 15}), assignCol(Y, 0), assignRow(X, 0));
	}
	
	void TestGroup3() {
		Subtasks({3, 5});
		
		CASE(init(2, 3), G = {{KK^BB, 0, KK   }, {   BB, 0, KK^BB}});
		CASE(init(2, 3), G = {{KK^BB, 0,    BB}, {KK^BB, 0, KK   }});
		CASE(init(2, 3), G = {{   BB, 0, KK^BB}, {KK   , 0, KK^BB}});
		
		CASE(init(2, 3), fill({KK^BB}, {100}), assignCol(Y, 0));
		CASE(init(3, 2), fill({KK, BB}, {50, 50}), assignCol(Y, 0));
		CASE(init(2, 3), fill({ 0, KK, BB, KK^BB}, { 0, 10, 30, 60}), assignCol(Y, 0));
		CASE(init(3, 2), fill({ 0, KK, BB, KK^BB}, { 25, 25, 25, 25}), assignCol(Y, 0));
		
		CASE(init(ODD_PRIMES[0], ODD_PRIMES[1]), fill({KK^BB}, {100}), assignCol(Y, 0));
		CASE(init(ODD_PRIMES[2], ODD_PRIMES[3]), fill({BB}, {100}), fill({KK, 0}, {65, 35}), assignCol(Y, 0));
		CASE(init(ODD_PRIMES[4], ODD_PRIMES[5]), fill({ 0, KK, BB, KK^BB}, {20, 10, 10, 60}), assignCol(Y, 0));
		CASE(init(ODD_PRIMES[6], ODD_PRIMES[7]), fill({ 0, KK, BB, KK^BB}, {15, 35, 35, 15}), assignCol(Y, 0));
		
		CASE(init(19, 23), fill({KK^BB}, {100}), assignCol(Y, 0));
		CASE(init(19, 23), fill({KK, BB}, {50, 50}), assignCol(Y, 0));
		CASE(init(23, 19), fill({KK}, {100}), fill({BB, 0}, {20, 80}), assignCol(Y, 0));
		CASE(init(19, 23), fill({BB}, {100}), fill({KK, 0}, {65, 35}), assignCol(Y, 0));
		
		CASE(init(19, 23), fill({ 0, KK, BB, KK^BB}, { 0, 10, 30, 60}), assignCol(Y, 0));
		CASE(init(23, 19), fill({ 0, KK, BB, KK^BB}, {25, 25, 25, 25}), assignCol(Y, 0));
		CASE(init(19, 23), fill({ 0, KK, BB, KK^BB}, {20, 10, 10, 60}), assignCol(Y, 0));
		CASE(init(23, 19), fill({ 0, KK, BB, KK^BB}, {15, 35, 35, 15}), assignCol(Y, 0));
	}
	
	void TestGroup4() {
		Subtasks({4, 5});
		
		CASE(IS_GEN_SUB_4 = true, init(19, 23), G[X][Y] = KK);
		CASE(IS_GEN_SUB_4 = true, init(23, 19), G[X][Y] = (KK^BB));
		CASE(IS_GEN_SUB_4 = true, init(19, 23), fill({KK, BB}, {50, 50}), G[X][Y] = 0);
		CASE(IS_GEN_SUB_4 = true, init(23, 19), fill({ 0, KK, BB, KK^BB}, {10, 30, 60, 0}), G = accel(G, rnd.nextInt(1, N * M - 1)));
		
		CASE(IS_GEN_SUB_4 = true, init(2, 3), fill({KK^BB}, {100}), assignRow(X, 0));
		CASE(IS_GEN_SUB_4 = true, init(23, 2), fill({KK^BB}, {100}), assignCol(Y, 0));
		CASE(IS_GEN_SUB_4 = true, init(ODD_PRIMES[0], ODD_PRIMES[1]), fill({KK, BB}, {50, 50}), assignCol(Y, KK), assignCol((Y + rnd.nextInt(1, M - 1)) % M, BB), G = accel(G, rnd.nextInt(1, M - 1)));
		CASE(IS_GEN_SUB_4 = true, init(19, 23), fill({KK, BB}, {20, 80}), assignCol(Y, KK), assignCol((Y + rnd.nextInt(1, M - 1)) % M, BB), G = accel(G, rnd.nextInt(1, M - 1)));
		
		CASE(IS_GEN_SUB_4 = true, init(3, 2), zigzag(), G = accel(G, N * M / 2));
		CASE(IS_GEN_SUB_4 = true, init(23, 2), zigzag(), G = accel(G, N * M / 2));
		CASE(IS_GEN_SUB_4 = true, init(ODD_PRIMES[0], ODD_PRIMES[1]), zigzag(), G = accel(G, N * M / 2));
		CASE(IS_GEN_SUB_4 = true, init(19, 23), zigzag(), G = accel(G, N * M / 2));
		
		CASE(IS_GEN_SUB_4 = true, init(3, 2), zigzag(), G = accel(G, rnd.nextInt(1, N * M - 1)));
		CASE(IS_GEN_SUB_4 = true, init(23, 2), zigzag(), G = accel(G, rnd.nextInt(1, N * M - 1)));
		CASE(IS_GEN_SUB_4 = true, init(ODD_PRIMES[0], ODD_PRIMES[1]), zigzag(), G = accel(G, rnd.nextInt(1, N * M - 1)));
		CASE(IS_GEN_SUB_4 = true, init(19, 23), zigzag(), G = accel(G, rnd.nextInt(1, N * M - 1)));
		
		CASE(IS_GEN_SUB_4 = true, init(19, 23), fill({KK}, {100}), G[X][Y] = BB, G = accel(G, 1));
		CASE(IS_GEN_SUB_4 = true, init(23, 19), fill({BB}, {100}), G[X][Y] = KK, G = accel(G, rnd.nextInt(1, N * M - 1)));
		CASE(IS_GEN_SUB_4 = true, init(19, 23), fill({KK}, {100}), G[X][Y] = BB, G = accel(G, N * M - 1));
		CASE(IS_GEN_SUB_4 = true, init(23, 19), fill({BB}, {100}), G[X][Y] = KK, G = accel(G, N * M / 2));
		
		CASE(IS_GEN_SUB_4 = true, init(19, 23), fill({KK, BB}, {50, 50}), G = accel(G, 1));
		CASE(IS_GEN_SUB_4 = true, init(23, 19), fill({KK, BB}, {50, 50}), G = accel(G, rnd.nextInt(1, N * M - 1)));
		CASE(IS_GEN_SUB_4 = true, init(19, 23), fill({KK, BB}, {20, 80}), G = accel(G, N * M - 1));
		CASE(IS_GEN_SUB_4 = true, init(23, 19), fill({KK, BB}, {80, 20}), G = accel(G, N * M / 2));
	}
	
	void TestGroup5() {
		Subtasks({5});
		
		CASE(init(2, 3), G = {{KK^BB, 0, KK   }, {0,    BB, 0}});
		CASE(init(2, 3), G = {{KK   , 0,    BB}, {0, KK^BB, 0}});
		CASE(init(2, 3), G = {{BB   , 0, KK^BB}, {0, KK   , 0}});
		
		CASE(init(2, 3), fill({KK^BB}, {100}), G[X][Y] = 0);
		CASE(init(3, 2), fill({KK, BB}, {50, 50}), G[X][Y] = 0);
		CASE(init(2, 3), fill({ 0, KK, BB, KK^BB}, { 0, 10, 30, 60}), G[X][Y] = 0);
		CASE(init(3, 2), fill({ 0, KK, BB, KK^BB}, {25, 25, 25, 25}), G[X][Y] = 0);
		
		CASE(init(ODD_PRIMES[0], ODD_PRIMES[1]), fill({KK^BB}, {100}), G[X][Y] = 0);
		CASE(init(ODD_PRIMES[2], ODD_PRIMES[3]), fill({BB}, {100}), fill({KK, 0}, {65, 35}), G[X][Y] = 0);
		CASE(init(ODD_PRIMES[4], ODD_PRIMES[5]), fill({ 0, KK, BB, KK^BB}, {20, 10, 10, 60}), G[X][Y] = 0);
		CASE(init(ODD_PRIMES[6], ODD_PRIMES[7]), fill({ 0, KK, BB, KK^BB}, {15, 35, 35, 15}), G[X][Y] = 0);
		
		CASE(init(19, 23), fill({KK^BB}, {100}), G[X][Y] = 0);
		CASE(init(19, 23), fill({KK, BB}, {50, 50}), G[X][Y] = 0);
		CASE(init(23, 19), fill({KK}, {100}), fill({BB, 0}, {20, 80}), G[X][Y] = 0);
		CASE(init(19, 23), fill({BB}, {100}), fill({KK, 0}, {65, 35}), G[X][Y] = 0);
		
		CASE(init(19, 23), fill({ 0, KK, BB, KK^BB}, { 0, 10, 30, 60}), G[X][Y] = 0);
		CASE(init(23, 19), fill({ 0, KK, BB, KK^BB}, {25, 25, 25, 25}), G[X][Y] = 0);
		CASE(init(19, 23), fill({ 0, KK, BB, KK^BB}, {20, 10, 10, 60}), G[X][Y] = 0);
		CASE(init(23, 19), fill({ 0, KK, BB, KK^BB}, {15, 35, 35, 15}), G[X][Y] = 0);
	}

private:
	void init(int n, int m) {
		N = n;
		M = m;
		
		G.clear();
		vector<int> TMP;
		for (int j = 0; j < M; j++) TMP.push_back(0);
		for (int i = 0; i < N; i++) G.push_back(TMP);
		
		X = rnd.nextInt(N);
		Y = rnd.nextInt(M);
	}

	void fill(vector<int> opt, vector<int> prob) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				int x = rnd.nextInt(100);
				int y = 0;
				while (x >= prob[y]) {
					x -= prob[y];
					y++;
				}
				G[i][j] ^= opt[y];
			}
		}
	}
	
	void assignCol(int j, int val) {
		for (int i = 0; i < N; i++) G[i][j] = val;
	}
	
	void assignRow(int i, int val) {
		for (int j = 0; j < M; j++) G[i][j] = val;
	}
	
	void zigzag() {
		int x = X;
		int y = Y;
		for (int i = 0; i < N * M; i++) {
			G[x][y] = (i < N * M / 2) ? KK : BB;
			x = (x + 1) % N;
			y = (y - 1 + M) % M;
		}
	}
	
	vector<vector<int>> accel(vector<vector<int>> A, int T) {
		vector<int> TMP;
		vector<vector<int>> TMP2;
		for (int j = 0; j < M; j++) TMP.push_back(0);
		for (int i = 0; i < N; i++) TMP2.push_back(TMP);
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (A[i][j] & KK) TMP2[i][(j + T) % M] |= KK;
				if (A[i][j] & BB) TMP2[(i + T) % N][j] |= BB;
			}
		}
		
		return TMP2;
	}
};
