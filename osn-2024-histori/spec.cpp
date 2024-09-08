#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int MAX_N = 100000;
const int MAX_A = 200000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	vector<int> A;

	vector<int> MIN, MAX;
	vector<double> AVG;

	void InputFormat() {
		LINE(N);
		LINE(A % SIZE(N));
	}
	
	void OutputFormat() {
		LINES(MIN, MAX, AVG) % SIZE(N);
	}

	void StyleConfig() {
		CustomScorer();
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}
	
	void Constraints() {
		CONS(1 <= N && N <= MAX_N);
		CONS(allBetween(A, 1, MAX_A));
	}

	void Subtask1() {
		Points(10);
		CONS(N == 5);
		CONS(A == vector<int>({4, 2, 3, 9, 4}));
	}
	
	void Subtask2() {
		Points(16);
		CONS(arrayOfIndex(A));
	}
	
	void Subtask3() {
		Points(12);
		CONS(allBetween(A, A[0], A[0]));
	}
	
	void Subtask4() {
		Points(32);
		CONS(N <= 1000);
	}
	
	void Subtask5() {
		Points(30);
	}
	
private:
	bool allBetween(vector<int> arr, int lo, int hi) {
		for (int i = 0; i < N; i++) {
			if (arr[i] < lo || arr[i] > hi) return false;
		}
		return true;
	}

	bool arrayOfIndex(vector<int> arr) {
		for (int i = 0; i < N; i++) {
			if (arr[i] != i + 1) return false;
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({4, 5});
		
		Input({
			"4",
			"3 1 3 7",
		});
		Output({
			"3 3 3.0000",
			"1 4 2.5000",
			"2 5 3.3333",
			"3 7 5.0000",
		});
	}

	void BeforeTestCase() {
		A.clear();
	}

	void TestGroup1() {
		Subtasks({1, 4, 5});
		CASE(N = 5, A = {4, 2, 3, 9, 4});
	}

	void TestGroup2() {
		Subtasks({2, 3, 4, 5});
		CASE(N = 1, A = {1});
	}
	
	void TestGroup3() {
		Subtasks({2, 4, 5});
		
		CASE(N = 2, genStepArray(1, 1));
		CASE(N = 3, genStepArray(1, 1));
		CASE(N = 4, genStepArray(1, 1));
		CASE(N = 5, genStepArray(1, 1));
		CASE(N = rnd.nextInt(6, 998), genStepArray(1, 1));
		CASE(N = 999, genStepArray(1, 1));
		CASE(N = 1000, genStepArray(1, 1));
	}
	
	void TestGroup4() {
		Subtasks({2, 5});
		
		CASE(N = 1001, genStepArray(1, 1));
		CASE(N = rnd.nextInt(1002, MAX_N - 4), genStepArray(1, 1));
		CASE(N = MAX_N - 1, genStepArray(1, 1));
		CASE(N = MAX_N, genStepArray(1, 1));
	}
	
	void TestGroup5() {
		Subtasks({3, 4, 5});
		
		CASE(N = 1, genStepArray(42, 0));
		CASE(N = 2, genStepArray(42, 0));
		CASE(N = 3, genStepArray(42, 0));
		CASE(N = 4, genStepArray(42, 0));
		CASE(N = 5, genStepArray(42, 0));
		CASE(N = rnd.nextInt(6, 998), genStepArray(rnd.nextInt(1, MAX_A), 0));
		CASE(N = 999, genStepArray(rnd.nextInt(1, MAX_A), 0));
		CASE(N = 1000, genStepArray(MAX_A, 0));
	}
	
	void TestGroup6() {
		Subtasks({3, 5});
		
		CASE(N = 1001, genStepArray(42, 0));
		CASE(N = rnd.nextInt(1002, MAX_N - 4), genStepArray(rnd.nextInt(1, MAX_A), 0));
		CASE(N = MAX_N - 1, genStepArray(rnd.nextInt(1, MAX_A), 0));
		CASE(N = MAX_N, genStepArray(MAX_A, 0));
	}
	
	void TestGroup7() {
		Subtasks({4, 5});
		
		CASE(N = 1000, genStepArray(1, 2));
		CASE(N = 1000, genStepArray(rnd.nextInt(N, MAX_A), -1));
		CASE(N = 1000, genStepArray(MAX_A, -2));
		CASE(N = 1000, upDown(rnd.nextInt(1, MAX_A - 2000)));
		CASE(N = 1000, upDownRandom(rnd.nextInt(1, MAX_A - 2000)));
		CASE(N = 1000, upDownRandomMidThird(rnd.nextInt(1, MAX_A - 2000)));
		CASE(N = 1000, upDownRandomMidWide(rnd.nextInt(1, MAX_A - 2000)));
		CASE(N = 1000, randomArray(1, MAX_A));
		CASE(N = 1000, randomArray(MAX_A - 100, MAX_A));
	}
	
	void TestGroup8() {
		Subtasks({5});
		
		CASE(N = MAX_N, genStepArray(1, 2));
		CASE(N = MAX_N, genStepArray(rnd.nextInt(N, MAX_A), -1));
		CASE(N = MAX_N, genStepArray(MAX_A, -2));
		CASE(N = MAX_N, upDown(1));
		CASE(N = MAX_N, upDownRandom(1));
		CASE(N = MAX_N, upDownRandomMidThird(1));
		CASE(N = MAX_N, upDownRandomMidWide(1));
		CASE(N = MAX_N, randomArray(1, MAX_A));
		CASE(N = MAX_N, randomArray(MAX_A - 100, MAX_A));
	}

private:
	void genStepArray(int init, int step) {
		for (int i = 0; i < N; i++) {
			A.push_back(init);
			init += step;
		}
	}
	
	void upDown(int init) {
		int minim = init;
		int maxim = init;
		
		A.push_back(init);
		
		for (int i = 1; i < N; i++) {
			minim++;
			maxim++;
			
			if (i % 2 == 0) {
				A.push_back(minim - 1);
			} else {
				A.push_back(maxim + 1);
			}
			
			minim = min(minim, A[i]);
			maxim = max(maxim, A[i]);
		}
	}
	
	void upDownRandom(int init) {
		int minim = init;
		int maxim = init;
		
		A.push_back(init);
		
		for (int i = 1; i < N; i++) {
			minim++;
			maxim++;
			
			if (rnd.nextInt(2) == 0) {
				A.push_back(minim - 1);
			} else {
				A.push_back(maxim + 1);
			}
			
			minim = min(minim, A[i]);
			maxim = max(maxim, A[i]);
		}
	}
	
	void upDownRandomMidThird(int init) {
		int minim = init;
		int maxim = init;
		
		A.push_back(init);
		
		for (int i = 1; i < N; i++) {
			minim++;
			maxim++;
			
			if (rnd.nextInt(3) == 0) {
				A.push_back(rnd.nextInt(minim, maxim));
			} else if (rnd.nextInt(2) == 0) {
				A.push_back(minim - 1);
			} else {
				A.push_back(maxim + 1);
			}
			
			minim = min(minim, A[i]);
			maxim = max(maxim, A[i]);
		}
	}
	
	void upDownRandomMidWide(int init) {
		int minim = init;
		int maxim = init;
		
		A.push_back(init);
		
		for (int i = 1; i < N; i++) {
			minim++;
			maxim++;
			
			A.push_back(rnd.nextInt(minim - 1, maxim - 1));
			
			minim = min(minim, A[i]);
			maxim = max(maxim, A[i]);
		}
	}
	
	void randomArray(int minim, int maxim) {
		for (int i = 0; i < N; i++) {
			A.push_back(rnd.nextInt(minim, maxim));
		}
	}
};
