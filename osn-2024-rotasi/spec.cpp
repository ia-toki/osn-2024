#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef long long ll;

const int MXN = 3e5;
const int MXN3 = 50;
const int MXN4 = 3000;
const int MXN5 = 8e4;

using namespace tcframe;
using namespace std;
using namespace __gnu_pbds;

#define mp make_pair
#define fr first
#define sc second

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

class ProblemSpec : public BaseProblemSpec {
protected:
	ll N, K;
	vector<int> A;
	int ANS;

	void InputFormat() {
		LINE(N, K);
		LINE(A % SIZE(N));
	}

	void OutputFormat() {
		LINE(ANS);
	}

	void GradingConfig() {
		TimeLimit(2);
		MemoryLimit(512);
	}

	void Constraints() {
		CONS(1 <= N && N <= MXN);
		CONS(1 <= K && K <= N);
		CONS(eachElementBetween(A,1,N));
	}

	void Subtask1() {
		Points(5);
		CONS(N == 10);
		CONS(K == 4);
		CONS(A == vector<int>({1, 7, 8, 4, 5, 1, 7, 8, 2, 4}));
	}

	void Subtask2() {
		Points(13);
		CONS(1 <= K && K <= 3);
	}

	void Subtask3() {
		Points(20);
		CONS(1 <= N && N <= MXN3);
	}

	void Subtask4() {
		Points(21);
		CONS(1 <= N && N <= MXN4);
	}

	void Subtask5() {
		Points(20);
		CONS(1 <= N && N <= MXN5);
	}

	void Subtask6() {
		Points(21);
	}
	
private:
	bool eachElementBetween(const vector<int>& X, int lo, int hi) {
		for (int x : X) {
			if (x < lo || x > hi) {
				return false;
			}
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({2, 3, 4, 5, 6});
		Input({			
			"4 3",
			"1 4 4 1"
		});
		Output({
			"2"
		});
	}

	bool rot;

	void BeforeTestCase() {
		A.clear();
		
		rot = true;
	}
	
	void AfterTestCase() {
		if (rot) {
			int numRotate=rnd.nextInt(0, N - 1);
			rotate(A.begin(), A.begin()+numRotate, A.end());
		}
	}

	void TestGroup1() {
		Subtasks({1, 3, 4, 5, 6});

		CASE(N = 10, K = 4, A = {1, 7, 8, 4, 5, 1, 7, 8, 2, 4}, rot = false);
	}
	
	void TestGroup2() {
		Subtasks({2, 3, 4, 5, 6});
		
		// Case (1)
		CASE(N = MXN3, K = 1, A = randomArray(N));
		
		// Case (2-6) small N
		CASE(N = 1, K = 1, A = {1});
		CASE(N = 2, K = 2, A = {1, 2});
		CASE(N = 2, K = 2, A = {2, 2});
		CASE(N = 3, K = 2, A = {3, 1, 3});
		CASE(N = 3, K = 3, A = {3, 1, 2});
	}
	
	void TestGroup3() {
		Subtasks({2, 4, 5, 6});
		
		// Case (1)
		CASE(N = MXN4, K = 1, A = randomArray(N));
	}
	
	void TestGroup4() {
		Subtasks({2, 5, 6});
		
		// Case (1)
		CASE(N = MXN5, K = 1, A = randomArray(N));
	}
	
	void TestGroup5() {
		Subtasks({2, 6});
		
		// Case (1-4) rand array
		CASE(N = rnd.nextInt(MXN5 + 1, MXN), K = 3, A = randomArray(N));
		CASE(N = MXN, K = 1, A = randomArray(N));
		CASE(N = MXN, K = 2, A = randomArray(N));
		CASE(N = MXN, K = 3, A = randomArray(N));
		
		// Case (5-7) same element array
		CASE(N = MXN, K = 1, A = sameElementArray(N, rnd.nextInt(1, N)));
		CASE(N = MXN, K = 2, A = sameElementArray(N, rnd.nextInt(1, N)));
		CASE(N = MXN, K = 3, A = sameElementArray(N, rnd.nextInt(1, N)));
		
		// Case (8-13) finished array (ans is 0)
		CASE(N = MXN, K = 2, A = finishedArray(N, K, 0), rot = false);
		CASE(N = MXN, K = 2, A = finishedArray(N, K, 1), rot = false);
		CASE(N = MXN, K = 3, A = finishedArray(N, K, 0), rot = false);
		CASE(N = MXN, K = 3, A = finishedArray(N, K, 1), rot = false);
		CASE(N = MXN, K = 3, A = finishedArray(N, K, 0, 1), rot = false);
		CASE(N = MXN, K = 3, A = finishedArray(N, K, 1, 1), rot = false);
		
		// Case (14-16) sorted array (A[i] = i, possibly with holes)
		CASE(N = MXN, K = 1, A = sortedArrayWithHoles(N, sqrt(N)), rot = false);
		CASE(N = MXN, K = 2, A = sortedArrayWithHoles(N, sqrt(N)), reverse(A.begin(), A.end()), rot = false);
		CASE(N = MXN, K = 3, A = sortedArrayWithHoles(N, sqrt(N)), rot = false);
	}

	void TestGroup6() {
		Subtasks({3, 4, 5, 6});
		
		// Case (1-2) rand array
		CASE(N = rnd.nextInt(4, MXN3), K = rnd.nextInt(4, N), A = randomArray(N));
		CASE(N = MXN3, K = N - sqrt(N), A = randomArray(N));
		
		// Case (3) same element array
		CASE(N = MXN3, K = N, A = sameElementArray(N, rnd.nextInt(1, N)));
		
		// Case (4-5) finished array (ans is 0)
		CASE(N = MXN3, K = rnd.nextInt(N / 3, N * 2 / 3), A = finishedArray(N, K, 0), rot = false);
		CASE(N = MXN3, K = rnd.nextInt(N / 3, N * 2 / 3), A = finishedArray(N, K, 1), rot = false);
		
		// Case (6-7) sorted array (A[i] = i, possibly with holes)
		CASE(N = MXN3, K = N - sqrt(N), A = sortedArrayWithHoles(N, sqrt(N)), rot = false);
		CASE(N = MXN3, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = sortedArrayWithHoles(N, sqrt(N)), reverse(A.begin(), A.end()), rot = false);
		
		// Case (8) special array 1 (small blocks of small values and small blocks of big values alternating)
		CASE(N = MXN3, K = rnd.nextInt(N / 3, N * 2 / 3), A = specialArray1(N));
		
		// Case (9) special array 2 (diff between adjacent elements is bounded)
		CASE(N = MXN3, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = specialArray2(N, sqrt(N)));
		
		// Case (10) special array 3 (1, N/2+1, 2, N/2+2, 3, N/3+3, ...)
		CASE(N = MXN3, K = N / 2 + sqrt(N), A = specialArray3(N));
		
		// Case (11) permutation array
		CASE(N = MXN3, K = N, A = permutationArray(N));
		
		// Case (12) bitonic array (1 2 3 ... N-1 N N-1 ... 3 2 1)
		CASE(N = MXN3, K = rnd.nextInt(N / 3 - sqrt(N), N / 3 + sqrt(N)), A = bitonicArrayWithHoles(N, sqrt(N)));
		
		// Case (13) periodic array
		CASE(N = MXN3, K = N / 5 + sqrt(N), A = periodicArray(N, N / 5));
		
		// Case (14) periodic sorted array
		CASE(N = MXN3, K = N / 5 + sqrt(N), A = periodicSortedArray(N, N / 5));
		
		// Case (15) diamond array
		CASE(N = MXN3, K = rnd.nextInt(N / 3 - sqrt(N), N / 3 + sqrt(N)), A = diamondArray(N));
		
		// Case (16-19) distant-duplicate array blocks (consists of blocks, in each block, duplicates are far apart)
		CASE(N = MXN3, K = N / 2, A = distantDuplicateArrayBlocks(N, N / 2, N / 3, 1));
		CASE(N = MXN3, K = N / 3, A = distantDuplicateArrayBlocks(N, N / 4, N / 5, 2));
		CASE(N = MXN3, K = N / 4, A = distantDuplicateArrayBlocks(N, N / 5, N / 6, 5));
		CASE(N = MXN3, K = N / 9, A = distantDuplicateArrayBlocks(N, N / 10, N / 11, 5));
		
		// Case (20-22) somewhat increasing distinct array (array is somewhat increasing but each element is distinct)
		CASE(N = MXN3, K = N - sqrt(N), A = somewhatIncreasingArray(N, N / 2));
		CASE(N = MXN3, K = N - sqrt(N), A = somewhatIncreasingArray(N, sqrt(N)), reverse(A.begin(), A.end()));
		CASE(N = MXN3, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = somewhatIncreasingArray(N, sqrt(N)));
	}

	void TestGroup7() {
		Subtasks({4, 5, 6});
		
		// Case (1-2) rand array
		CASE(N = rnd.nextInt(MXN3 + 1, MXN4), K = rnd.nextInt(4, N), A = randomArray(N));
		CASE(N = MXN4, K = N - sqrt(N), A = randomArray(N));
		
		// Case (3) same element array
		CASE(N = MXN4, K = N, A = sameElementArray(N, rnd.nextInt(1, N)));
		
		// Case (4-5) finished array (ans is 0)
		CASE(N = MXN4, K = rnd.nextInt(N / 3, N * 2 / 3), A = finishedArray(N, K, 0), rot = false);
		CASE(N = MXN4, K = rnd.nextInt(N / 3, N * 2 / 3), A = finishedArray(N, K, 1), rot = false);
		
		// Case (6-7) sorted array (A[i] = i, possibly with holes)
		CASE(N = MXN4, K = N - sqrt(N), A = sortedArrayWithHoles(N, sqrt(N)), rot = false);
		CASE(N = MXN4, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = sortedArrayWithHoles(N, sqrt(N)), reverse(A.begin(), A.end()), rot = false);
		
		// Case (8) special array 1 (small blocks of small values and small blocks of big values alternating)
		CASE(N = MXN4, K = rnd.nextInt(N / 3, N * 2 / 3), A = specialArray1(N));
		
		// Case (9) special array 2 (diff between adjacent elements is bounded)
		CASE(N = MXN4, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = specialArray2(N, sqrt(N)));
		
		// Case (10) special array 3 (1, N/2+1, 2, N/2+2, 3, N/3+3, ...)
		CASE(N = MXN4, K = N / 2 + sqrt(N), A = specialArray3(N));
		
		// Case (11) permutation array
		CASE(N = MXN4, K = N, A = permutationArray(N));
		
		// Case (12) bitonic array (1 2 3 ... N-1 N N-1 ... 3 2 1)
		CASE(N = MXN4, K = rnd.nextInt(N / 3 - sqrt(N), N / 3 + sqrt(N)), A = bitonicArrayWithHoles(N, sqrt(N)));
		
		// Case (13) periodic array
		CASE(N = MXN4, K = N / 5 + sqrt(N), A = periodicArray(N, N / 5));
		
		// Case (14) periodic sorted array
		CASE(N = MXN4, K = N / 5 + sqrt(N), A = periodicSortedArray(N, N / 5));
		
		// Case (15) diamond array
		CASE(N = MXN4, K = rnd.nextInt(N / 3 - sqrt(N), N / 3 + sqrt(N)), A = diamondArray(N));
		
		// Case (16-19) distant-duplicate array blocks (consists of blocks, in each block, duplicates are far apart)
		CASE(N = MXN4, K = N / 2, A = distantDuplicateArrayBlocks(N, N / 2, N / 3, 1));
		CASE(N = MXN4, K = N / 3, A = distantDuplicateArrayBlocks(N, N / 4, N / 5, 2));
		CASE(N = MXN4, K = N / 4, A = distantDuplicateArrayBlocks(N, N / 5, N / 6, 5));
		CASE(N = MXN4, K = N / 9, A = distantDuplicateArrayBlocks(N, N / 10, N / 11, 5));
		
		// Case (20-22) somewhat increasing distinct array (array is somewhat increasing but each element is distinct)
		CASE(N = MXN4, K = N - sqrt(N), A = somewhatIncreasingArray(N, N / 2));
		CASE(N = MXN4, K = N - sqrt(N), A = somewhatIncreasingArray(N, sqrt(N)), reverse(A.begin(), A.end()));
		CASE(N = MXN4, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = somewhatIncreasingArray(N, sqrt(N)));
	}

	void TestGroup8() {
		Subtasks({5, 6});
		
		// Case (1-2) rand array
		CASE(N = rnd.nextInt(MXN4 + 1, MXN5), K = rnd.nextInt(4, N), A = randomArray(N));
		CASE(N = MXN5, K = N - sqrt(N), A = randomArray(N));
		
		// Case (3) same element array
		CASE(N = MXN5, K = N, A = sameElementArray(N, rnd.nextInt(1, N)));
		
		// Case (4-5) finished array (ans is 0)
		CASE(N = MXN5, K = rnd.nextInt(N / 3, N * 2 / 3), A = finishedArray(N, K, 0), rot = false);
		CASE(N = MXN5, K = rnd.nextInt(N / 3, N * 2 / 3), A = finishedArray(N, K, 1), rot = false);
		
		// Case (6-7) sorted array (A[i] = i, possibly with holes)
		CASE(N = MXN5, K = N - sqrt(N), A = sortedArrayWithHoles(N, sqrt(N)), rot = false);
		CASE(N = MXN5, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = sortedArrayWithHoles(N, sqrt(N)), reverse(A.begin(), A.end()), rot = false);
		
		// Case (8) special array 1 (small blocks of small values and small blocks of big values alternating)
		CASE(N = MXN5, K = rnd.nextInt(N / 3, N * 2 / 3), A = specialArray1(N));
		
		// Case (9) special array 2 (diff between adjacent elements is bounded)
		CASE(N = MXN5, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = specialArray2(N, sqrt(N)));
		
		// Case (10) special array 3 (1, N/2+1, 2, N/2+2, 3, N/3+3, ...)
		CASE(N = MXN5, K = N / 2 + sqrt(N), A = specialArray3(N));
		
		// Case (11) permutation array
		CASE(N = MXN5, K = N, A = permutationArray(N));
		
		// Case (12) bitonic array (1 2 3 ... N-1 N N-1 ... 3 2 1)
		CASE(N = MXN5, K = rnd.nextInt(N / 3 - sqrt(N), N / 3 + sqrt(N)), A = bitonicArrayWithHoles(N, sqrt(N)));
		
		// Case (13) periodic array
		CASE(N = MXN5, K = N / 5 + sqrt(N), A = periodicArray(N, N / 5));
		
		// Case (14) periodic sorted array
		CASE(N = MXN5, K = N / 5 + sqrt(N), A = periodicSortedArray(N, N / 5));
		
		// Case (15) diamond array
		CASE(N = MXN5, K = rnd.nextInt(N / 3 - sqrt(N), N / 3 + sqrt(N)), A = diamondArray(N));
		
		// Case (16-19) distant-duplicate array blocks (consists of blocks, in each block, duplicates are far apart)
		CASE(N = MXN5, K = N / 2, A = distantDuplicateArrayBlocks(N, N / 2, N / 3, 1));
		CASE(N = MXN5, K = N / 3, A = distantDuplicateArrayBlocks(N, N / 4, N / 5, 2));
		CASE(N = MXN5, K = N / 4, A = distantDuplicateArrayBlocks(N, N / 5, N / 6, 5));
		CASE(N = MXN5, K = N / 9, A = distantDuplicateArrayBlocks(N, N / 10, N / 11, 5));
		
		// Case (20-22) somewhat increasing distinct array (array is somewhat increasing but each element is distinct)
		CASE(N = MXN5, K = N - sqrt(N), A = somewhatIncreasingArray(N, N / 2));
		CASE(N = MXN5, K = N - sqrt(N), A = somewhatIncreasingArray(N, sqrt(N)), reverse(A.begin(), A.end()));
		CASE(N = MXN5, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = somewhatIncreasingArray(N, sqrt(N)));
	}

	void TestGroup9() {
		Subtasks({6});
		
		// Case (1-2) rand array
		CASE(N = rnd.nextInt(MXN5 + 1, MXN), K = rnd.nextInt(4, N), A = randomArray(N));
		CASE(N = MXN, K = N - sqrt(N), A = randomArray(N));
		
		// Case (3) same element array
		CASE(N = MXN, K = N, A = sameElementArray(N, rnd.nextInt(1, N)));
		
		// Case (4-5) finished array (ans is 0)
		CASE(N = MXN, K = rnd.nextInt(N / 3, N * 2 / 3), A = finishedArray(N, K, 0), rot = false);
		CASE(N = MXN, K = rnd.nextInt(N / 3, N * 2 / 3), A = finishedArray(N, K, 1), rot = false);
		
		// Case (6-7) sorted array (A[i] = i, possibly with holes)
		CASE(N = MXN, K = N - sqrt(N), A = sortedArrayWithHoles(N, sqrt(N)), rot = false);
		CASE(N = MXN, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = sortedArrayWithHoles(N, sqrt(N)), reverse(A.begin(), A.end()), rot = false);
		
		// Case (8) special array 1 (small blocks of small values and small blocks of big values alternating)
		CASE(N = MXN, K = rnd.nextInt(N / 3, N * 2 / 3), A = specialArray1(N));
		
		// Case (9) special array 2 (diff between adjacent elements is bounded)
		CASE(N = MXN, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = specialArray2(N, sqrt(N)));
		
		// Case (10) special array 3 (1, N/2+1, 2, N/2+2, 3, N/3+3, ...)
		CASE(N = MXN, K = N / 2 + sqrt(N), A = specialArray3(N));
		
		// Case (11) permutation array
		CASE(N = MXN, K = N, A = permutationArray(N));
		
		// Case (12) bitonic array (1 2 3 ... N-1 N N-1 ... 3 2 1)
		CASE(N = MXN, K = rnd.nextInt(N / 3 - sqrt(N), N / 3 + sqrt(N)), A = bitonicArrayWithHoles(N, sqrt(N)));
		
		// Case (13) periodic array
		CASE(N = MXN, K = N / 5 + sqrt(N), A = periodicArray(N, N / 5));
		
		// Case (14) periodic sorted array
		CASE(N = MXN, K = N / 5 + sqrt(N), A = periodicSortedArray(N, N / 5));
		
		// Case (15) diamond array
		CASE(N = MXN, K = rnd.nextInt(N / 3 - sqrt(N), N / 3 + sqrt(N)), A = diamondArray(N));
		
		// Case (16-19) distant-duplicate array blocks (consists of blocks, in each block, duplicates are far apart)
		CASE(N = MXN, K = N / 2, A = distantDuplicateArrayBlocks(N, N / 2, N / 3, 1));
		CASE(N = MXN, K = N / 3, A = distantDuplicateArrayBlocks(N, N / 4, N / 5, 2));
		CASE(N = MXN, K = N / 4, A = distantDuplicateArrayBlocks(N, N / 5, N / 6, 5));
		CASE(N = MXN, K = N / 9, A = distantDuplicateArrayBlocks(N, N / 10, N / 11, 5));
		
		// Case (20-22) somewhat increasing distinct array (array is somewhat increasing but each element is distinct)
		CASE(N = MXN, K = N - sqrt(N), A = somewhatIncreasingArray(N, N / 2));
		CASE(N = MXN, K = N - sqrt(N), A = somewhatIncreasingArray(N, sqrt(N)), reverse(A.begin(), A.end()));
		CASE(N = MXN, K = rnd.nextInt(N / 2 - sqrt(N), N / 2 + sqrt(N)), A = somewhatIncreasingArray(N, sqrt(N)));
	}

private:
	vector<int> randomArray(int n){
		vector<int> a;
		a.clear();
		for (int i=0; i<n; i++){
			a.push_back(rnd.nextInt(1, n));
		}
		return a;
	}

	vector<int> sameElementArray(int n, int va) {
		return vector<int>(n, va);
	}

	vector<int> finishedArray(int n, int k, bool wrap = true, int cntHoles = 0) {
		int l = rnd.nextInt(1, n - k + 1);
		vector<int> v;
		for (int i = 0; i < k; i++)
			v.push_back(l + i);
		for (int i = 0; i < cntHoles; i++) {
			v.erase(v.begin() + rnd.nextInt(0, v.size() - 1));
		}
		rnd.shuffle(v.begin(), v.begin() + k);
		for (int i = k - cntHoles; i < n; i++) v.push_back(rnd.nextInt(1, n));

		if (wrap) {
			int numRotate = rnd.nextInt(1, k - 1);
			rotate(v.begin(), v.begin()+numRotate, v.end());
		}
		return v;
	}

	vector<int> sortedArray(int n) {
		vector<int> v(n);
		for (int i = 0; i < n; i++) v[i] = i + 1;
		return v;
	}
	
	vector<int> sortedArrayWithHoles(int n, int cntHoles) {
		vector<int> v = sortedArray(n);
		for (int i = 0; i < cntHoles; i++) {
			v.erase(v.begin() + rnd.nextInt(0, v.size() - 1));
		}
		for (int i = 0; i < cntHoles; i++) {
			v.push_back(rnd.nextInt(1, n));
		}
		return v;
	}

	vector<int> specialArray1(int n) {
		vector<int> v;
		for (; v.size() < n;) {
			int g = rnd.nextInt(2, 5);
			for (; v.size() < n && g > 0; g--) {
				v.push_back(rnd.nextInt(1, n / 4));
			}
			g = rnd.nextInt(2, 5);
			for (; v.size() < n && g > 0; g--) {
				v.push_back(rnd.nextInt(3 * n / 4, n));
			}
		}

		return v;
	}

	vector<int> specialArray2(int n, int maxdiff) {
		vector<int> v;
		v.push_back(rnd.nextInt(1, n));
		for (; v.size() < n; v.push_back(max(min(n, v.back() + rnd.nextInt(-maxdiff, maxdiff)), 1)));
		return v;
	}

	vector<int> specialArray3(int n) {
		vector<int> v(n);
		int a = 1, b = n / 2 + 1 + (n % 2);
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) v[i] = a++;
			else v[i] = b++;
		}
		return v;
	}
	
	vector<int> permutationArray(int n) {
		vector<int> v = sortedArray(n);
		rnd.shuffle(v.begin(), v.end());
		return v;
	}
	
	vector<int> bitonicArrayWithHoles(int n, int cntHoles) {
		vector<int> v;
		int mid = (n + cntHoles + 1) / 2;
		for (int i = 1; i <= mid; i++) {
			v.push_back(i);
		}
		for (int i = 1; i <= n + cntHoles - mid; i++)
		{
			v.push_back(mid + 2 - i);
		}
		for (int i = 0; i < cntHoles; i++) {
			v.erase(v.begin() + rnd.nextInt(0, v.size() - 1));
		}
		return v;
	}
	
	vector<int> periodicArray(int n, int period) {
		vector<int> v, perm;
		perm = permutationArray(period);
		int offset = rnd.nextInt(0, n - period);
		for (int i = 0; i < perm.size(); i++) {
			perm[i] += offset;
		}
		for (int i = 0; i < n; i++)
		{
			v.push_back(perm[i % period]);
		}
		return v;
	}
	
	vector<int> periodicSortedArray(int n, int period) {
		vector<int> v;
		int offset = rnd.nextInt(0, n - period);
		for (int i = 0; i < n; i++)
		{
			v.push_back(i % period + 1 + offset);
		}
		return v;
	}
	
	vector<int> diamondArray(int n) {
		vector<int> v;
		int mid = rnd.nextInt(n * 2 / 5, n * 3 / 5);
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				v.push_back(mid + min(i / 2, (n - 1 - i) / 2));
			} else {
				v.push_back(mid - min(i / 2, (n - 1 - i) / 2));
			}
		}
		return v;
	}
	
	vector<int> increasingArray(int n, int lo, int hi) {
		vector<int> v;
		for (int i = 0; i < n; i++) {
			v.push_back(rnd.nextInt(lo, hi - (n - 1)));
		}
		sort(v.begin(), v.end());
		for (int i = 0; i < n; i++) {
			v[i] += i;
		}
		return v;
	}
	
	vector<int> distantDuplicateArrayBlocks(int n, int range, int minDist, int cntBlocks) {
		vector<int> pos = increasingArray(cntBlocks - 1, 1, n - 1);
		pos.push_back(n);
		
		vector<int> v;
		int p = 0;
		for (int i = 0; i < cntBlocks; i++) {
			int offset = rnd.nextInt(0, n - range);
			
			ordered_set<pair<int, int>> lastPos;
			for (int j = 1; j <= range; j++)
			{
				lastPos.insert({-minDist, offset + j});
			}
			
			for (int j = p + 1; j <= pos[i]; j++) {
				int ub = lastPos.order_of_key({j - minDist, n + 1});
				pair<int, int> tmp = *lastPos.find_by_order(rnd.nextInt(0, ub - 1));
				
				v.push_back(tmp.sc);
				
				lastPos.erase(tmp);
				lastPos.insert({j, tmp.sc});
			}
			p = pos[i];
		}
		
		return v;
	}
	
	vector<int> somewhatIncreasingArray(int n, int range) {
		int loList[n + 69], hiList[n + 69];
		for (int i = 1; i <= n; i++) {
			loList[i] = 1 + (long long)(n - range) * (i - 1) / (n - 1);
			hiList[i] = range + (long long)(n - range) * (i - 1) / (n - 1);
		}
		
		ordered_set<int> vals;
		for (int i = 1; i <= range; i++) {
			vals.insert(i);
		}
		
		vector<int> v;
		for (int i = 1; i <= n; i++) {
			if(i > 1 && hiList[i] > hiList[i - 1]) {
				vals.insert(hiList[i]);
			}
			
			int k;
			if (i < n && loList[i] < loList[i + 1] && *vals.begin() == loList[i]) {
				k = loList[i];
			} else {
				k = *vals.find_by_order(rnd.nextInt(0, vals.size() - 1));
			}
			v.push_back(k);
			vals.erase(k);
		}
		return v;
	}
};
