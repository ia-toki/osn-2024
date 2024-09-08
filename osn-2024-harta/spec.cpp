#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int N = 256;

class ProblemSpec : public BaseProblemSpec {
protected:
	int ANS;

	void InputFormat() {
		LINE(ANS);
	}

	void StyleConfig() {
		InteractiveEvaluator();
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}
	
	void Constraints() {
		CONS(1 <= ANS && ANS <= N);
	}

	void Subtask1() {
		Points(9);
		CONS(ANS == 1);
	}
	
	void Subtask2() {
		Points(15);
		CONS(1 <= ANS && ANS <= 3);
	}
	
	void Subtask3() {
		Points(33);
		CONS(1 <= ANS && ANS <= 128);
	}
	
	void Subtask4() {
		Points(43);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({3, 4});
		Input({"42"});
	}

	void TestGroup1() {
		Subtasks({1, 2, 3, 4});
		
		CASE(ANS = 1);
	}

	void TestGroup2() {
		Subtasks({2, 3, 4});
		
		CASE(ANS = 3);
		CASE(ANS = 2);
	}
	
	void TestGroup3() {
		Subtasks({3, 4});
		
		CASE(ANS = 4);
		CASE(ANS = 63);
		CASE(ANS = 64);
		CASE(ANS = 65);
		CASE(ANS = 126);
		CASE(ANS = 127);
		CASE(ANS = 128);
		
		for (int i = 0; i < 16; i++) {
			CASE(ANS = rnd.nextInt(4, 128));
		}
	}
	
	void TestGroup4() {
		Subtasks({4});
		
		CASE(ANS = 129);
		CASE(ANS = 191);
		CASE(ANS = 192);
		CASE(ANS = 193);
		CASE(ANS = 254);
		CASE(ANS = 255);
		CASE(ANS = 256);
		
		for (int i = 0; i < 32; i++) {
			CASE(ANS = rnd.nextInt(129, N));
		}
	}
};
