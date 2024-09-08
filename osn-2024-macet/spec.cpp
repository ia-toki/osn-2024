#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

using ii = pair<int, int>;

#define pb push_back
#define f1 first
#define s2 second

const int MAXN = 1e5;
const int MAXM = 1e5;
const int MAXA = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M, Z;
	vector<int> L, R, A;

	void InputFormat() {
		LINE(N);
		LINES(L, R) % SIZE(N);
		LINE(M);
		LINE(A % SIZE(M));
	}

	void OutputFormat() {
		LINE(Z);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}

	void Constraints() {
		CONS(1 <= N && N <= MAXN);
		CONS(eachIntervalBetween(L, R, 1, MAXA));
		CONS(1 <= M && M <= MAXN);
		CONS(eachElementBetween(A, 1, MAXA));
	}

	void Subtask1() {
		Points(5);

		CONS(N == 1 && M == 1);
	}

	void Subtask2() {
		Points(15);

		CONS(isDisjointSortedInterval(L, R));
	}

	void Subtask3() {
		Points(19);

		CONS(N <= 100 && M <= 100);
	}

	void Subtask4() {
		Points(11);

		CONS(N <= 2000 && M <= 2000);
	}

	void Subtask5() {
		Points(15);

		CONS(isIncreasing(L));
		CONS(isIncreasing(R));
		CONS(isNonDecreasing(A));
	}

	void Subtask6() {
		Points(16);

		CONS(isNonDecreasing(A));
	}

	void Subtask7() {
		Points(19);
	}

private:
	bool eachIntervalBetween(const vector<int> &lt, vector<int> &rt, int lo, int hi) {
		if (lt.size() != rt.size())
			return false;
		for (int i = 0; i < (int)lt.size(); ++i) if (!(lo <= lt[i] && lt[i] <= rt[i] && rt[i] <= hi))
			return false;
		return true;
	}

	bool isDisjointSortedInterval(const vector<int> &lt, const vector<int> &rt) {
		if (lt.size() != rt.size())
			return false;
		for (int i = 0; i+1 < (int)lt.size(); ++i) if (!(rt[i] < lt[i+1]))
			return false;
		return true;

	}

	bool eachElementBetween(const vector<int> &v, int lo, int hi) {
		for (int x : v) if (!(lo <= x && x <= hi))
			return false;
		return true;
	}

	bool isIncreasing(const vector<int> &V) {
		for (int i = 0; i+1 < (int)V.size(); ++i) {
			if (V[i] >= V[i+1])
				return false;
		}
		return true;
	}

	bool isNonDecreasing(const vector<int> &V) {
		for (int i = 0; i+1 < (int)V.size(); ++i) {
			if (V[i] > V[i+1])
				return false;
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({ 3, 4, 7 });
		Input({
			"4",
			"1 4",
			"7 7",
			"6 9",
			"8 10",
			"6",
			"3 8 10 2 7 7",
		});
		Output({
			"3",
		});
	}

	void SampleTestCase2() {
		Subtasks({ 3, 4, 5, 6, 7 });
		Input({
			"3",
			"1 1000",
			"1000 1000000",
			"1000000 1000000000",
			"7",
			"2 5 6 25 26 65 265",
		});
		Output({
			"0",
		});
	}

	void SampleTestCase3() {
		Subtasks({ 3, 4, 7 });
		Input({
			"4",
			"1 4",
			"7 7",
			"6 9",
			"8 10",
			"6",
			"2 10 3 5 7 6"
		});
		Output({
			"-1",
		});
	}

	void BeforeTestCase() {
		L.clear(); R.clear();
		A.clear();
	}

	void TestGroup1() {
		Subtasks({ 1, 2, 3, 4, 5, 6, 7 });
		CASE(N = 1, M = 1, L = {6}, R = {9}, A = {69});
		CASE(N = 1, M = 1, L = {13}, R = {177}, A = {69});
		CASE(N = 1, M = 1, L = {420}, R = {1273}, A = {69});
		CASE(N = 1, M = 1, L = {69}, R = {69}, A = {69});
	}

	void TestGroup2() {
		Subtasks({ 2, 3, 4, 7 });

		CASE(N = rnd.nextInt(10, 20), M = rnd.nextInt(20, 30), generateRandomDisjointInterval(N, 1, 100), generateSmallSteps(1, 100));
		CASE(N = rnd.nextInt(10, 20), M = rnd.nextInt(20, 30), generateRandomDisjointInterval(N, 1, 100), generateSmallSteps(1, 100), setFailure());
	}

	void TestGroup3() {
		Subtasks({ 2, 7 });

		CASE(N = MAXN, M = MAXM, generateRandomDisjointInterval(N, 1, MAXA), generateSmallSteps(1, MAXA));
		CASE(N = MAXN, M = MAXM, generateRandomDisjointInterval(N, 1, MAXA), generateMediumSteps(1, MAXA));
		CASE(N = MAXN, M = MAXM, generateRandomDisjointInterval(N, 1, MAXA), generateLargeSteps(1, MAXA));
		CASE(N = MAXN, M = MAXM, generateRandomDisjointInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA));
		CASE(N = MAXN, M = MAXM, generateRandomDisjointInterval(N, 1, MAXA), generateRandomSteps(1, MAXA));
		CASE(N = MAXN, M = MAXM, generateRandomDisjointInterval(N, 1, MAXA), generateSmallSteps(1, MAXA), setFailure());
	}

	void TestGroup4() {
		Subtasks({ 3, 4, 7 });

		CASE(N = 100, M = 100, generateRandomInterval(N, 1, MAXA), generateSmallSteps(1, MAXA));
		CASE(N = 100, M = 69, generateRandomIntervalWithLength(N, 1, MAXA, 3, 6), generateSmallSteps(1, MAXA));
		CASE(N = 100, M = 100, generateRandomInterval(N, 1, MAXA), generateMediumSteps(1, MAXA));
		CASE(N = 100, M = 100, generateRandomInterval(N, 1, MAXA), generateLargeSteps(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomFullyContainedInterval(N, 1, MAXA), generateSmallSteps(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomFullyContainedInterval(N, 1, MAXA), generateMediumSteps(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomFullyContainedInterval(N, 1, MAXA), generateLargeSteps(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomFullyContainedInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateSmallSteps(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateMediumSteps(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateLargeSteps(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateSmallAndMediumStep(1, MAXA));
		CASE(N = rnd.nextInt(90, 100), M = rnd.nextInt(90, 100), generateRandomIntervalWithLength(N, 1, MAXA, 3, 6), generateSmallSteps(1, MAXA), setFailure());
	}

	void TestGroup5() {
		Subtasks({ 4, 7 });

		CASE(N = 2000, M = 2000, generateRandomInterval(N, 1, MAXA), generateSmallSteps(1, MAXA));
		CASE(N = 2000, M = 1600, generateRandomIntervalWithLength(N, 1, MAXA, 5, 8), generateSmallSteps(1, MAXA));
		CASE(N = 2000, M = 2000, generateRandomInterval(N, 1, MAXA), generateMediumSteps(1, MAXA));
		CASE(N = 2000, M = 2000, generateRandomInterval(N, 1, MAXA), generateLargeSteps(1, MAXA));
		CASE(N = 1998, M = 1998, generateRandomInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA));
		CASE(N = rnd.nextInt(1901, 2000), M = rnd.nextInt(1992, 2000), generateRandomFullyContainedInterval(N, 1, MAXA), generateSmallSteps(1, MAXA));
		CASE(N = rnd.nextInt(1902, 2000), M = rnd.nextInt(1993, 2000), generateRandomFullyContainedInterval(N, 1, MAXA), generateMediumSteps(1, MAXA));
		CASE(N = rnd.nextInt(1903, 2000), M = rnd.nextInt(1994, 2000), generateRandomFullyContainedInterval(N, 1, MAXA), generateLargeSteps(1, MAXA));
		CASE(N = rnd.nextInt(1905, 2000), M = rnd.nextInt(1995, 2000), generateRandomFullyContainedInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA));
		CASE(N = rnd.nextInt(1908, 2000), M = rnd.nextInt(1996, 2000), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateSmallSteps(1, MAXA));
		CASE(N = rnd.nextInt(1913, 2000), M = rnd.nextInt(1997, 2000), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateMediumSteps(1, MAXA));
		CASE(N = rnd.nextInt(1921, 2000), M = rnd.nextInt(1998, 2000), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateLargeSteps(1, MAXA));
		CASE(N = rnd.nextInt(1934, 2000), M = rnd.nextInt(1999, 2000), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateSmallAndMediumStep(1, MAXA));
		CASE(N = 1996, M = 1996, generateRandomInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA), setFailure());
	}

	void TestGroup6() {
		Subtasks({ 5, 6, 7 });

		CASE(N = MAXN, M = MAXM, generateRandomIncreasingInterval(N, 1, MAXA), generateSmallSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = MAXM/2, generateRandomIncreasingIntervalLowOverlap(N, 1, MAXA), generateSmallSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomIncreasingInterval(N, 1, MAXA), generateMediumSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomIncreasingInterval(N, 1, MAXA), generateLargeSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomIncreasingInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA), generateSmallSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomIncreasingInterval(N, 1, MAXA), generateLargeSteps(1, MAXA), setFailure(), sortSteps());
	}


	void TestGroup7() {
		Subtasks({ 6, 7 });

		CASE(N = MAXN, M = MAXM, generateRandomInterval(N, 1, MAXA), generateSmallSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = MAXM/2, generateRandomIntervalWithLength(N, 1, MAXA, 6, 9), generateSmallSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomInterval(N, 1, MAXA), generateMediumSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomInterval(N, 1, MAXA), generateLargeSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateSmallSteps(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomIncreasingIntervalHighOverlap(N, 1, MAXA, true), generateSmallAndMediumStep(1, MAXA), sortSteps());
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = MAXM/2, generateRandomIntervalWithLength(N, 1, MAXA, 6, 9), generateSmallSteps(1, MAXA), setFailure(), sortSteps());
	}


	void TestGroup8() {
		Subtasks({ 7 });

		CASE(N = MAXN, M = MAXM, generateRandomInterval(N, 1, MAXA), generateSmallSteps(1, MAXA));
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = MAXM/2, generateRandomIntervalWithLength(N, 1, MAXA, 6, 9), generateSmallSteps(1, MAXA));
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomInterval(N, 1, MAXA), generateMediumSteps(1, MAXA));
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomInterval(N, 1, MAXA), generateLargeSteps(1, MAXA));
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomInterval(N, 1, MAXA), generateRandomSteps(1, MAXA));
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomFullyContainedInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA));
		CASE(N = rnd.nextInt(MAXN-7, MAXN), M = rnd.nextInt(MAXM-13, MAXM), generateRandomInterval(N, 1, MAXA), generateSmallAndMediumStep(1, MAXA));
	}

private:
	void generateRandomDisjointInterval(int size, int lo, int hi) {
		assert(hi - lo >= 2 * size);

		set<int> st;
		while ((int)st.size() < 2 * size)
			st.insert(rnd.nextInt(lo, hi));

		for (auto it = st.begin(); it != st.end(); it++) {
			L.pb(*it); R.pb(*(++it));
		}
	}

	void generateRandomInterval(int size, int lo, int hi) {
		for (int i = 0; i < size; ++i) {
			int l = rnd.nextInt(lo, hi);
			int r = rnd.nextInt(l, hi);
			L.pb(l); R.pb(r);
		}
	}

	void generateRandomIntervalWithLength(int size, int lo, int hi, int lenLo, int lenHi) {
		for (int i = 0; i < size; ++i) {
			int l = rnd.nextInt(lo, hi - lenLo);
			int r = l + rnd.nextInt(lenLo, min(lenHi, hi-l));
			L.pb(l); R.pb(r);
		}
	}

	void generateRandomIncreasingInterval(int size, int lo, int hi) {		
		assert(hi - lo >= 2 * size);

		set<int> used;
		for (int i = 0; i < size; ++i)
		{
			int l, r;
			do {
				l = rnd.nextInt(lo, hi);
			} while (used.count(l));
			do {
				r = rnd.nextInt(l, hi);
			} while (used.count(r));

			used.insert(l), used.insert(r);
			L.pb(l); R.pb(r);
		}
		sort(L.begin(), L.end());
		sort(R.begin(), R.end());
	}

	void generateRandomFullyContainedInterval(int size, int lo, int hi) {
		generateRandomInterval(size, lo, hi);

		vector<int> all;
		for (int i = 0; i < size; ++i)
			all.pb(L[i]), all.pb(R[i]);
		sort(all.begin(), all.end());

		for (int i = 0; i < size; ++i)
			L[i] = all[i], R[i] = all[i + size];

		for (int i = 1; i < size; ++i) {
			int j = rnd.nextInt(0, i);
			swap(L[i], L[j]);
			swap(R[i], R[j]);
		}
	}

	void generateRandomIncreasingIntervalLowOverlap(int size, int lo, int hi) {
		assert(hi - lo >= 2 * size);

		set<int> st;
		while ((int)st.size() < 2 * size)
			st.insert(rnd.nextInt(lo, hi));

		for (auto it = st.begin(); it != st.end(); ++it) {
			if (L.size() == R.size()) L.pb(*it);
			else if ((int)L.size() == size) R.pb(*it);
			else
			{
				int coin = rnd.nextInt(0, 1);
				if (coin) L.pb(*it);
				else R.pb(*it);
			}
		}
	}

	void generateRandomIncreasingIntervalHighOverlap(int size, int lo, int hi, bool shuffle = false) {
		assert(hi - lo >= 2 * size);

		set<int> st;
		while ((int)st.size() < 2 * size)
			st.insert(rnd.nextInt(lo, hi));

		int init_L = rnd.nextInt((int)sqrt(size), 3 * (int)sqrt(size));
		for (auto it = st.begin(); it != st.end(); ++it) {
			if (L.size() == R.size() || init_L > 0) L.pb(*it), init_L--;
			else if ((int)L.size() == size) R.pb(*it);
			else
			{
				int coin = rnd.nextInt(0, 1);
				if (coin) L.pb(*it);
				else R.pb(*it);
			}
		}

		if (shuffle) {
			for (int i = 1; i < size; ++i) {
				int j = rnd.nextInt(0, i);
				swap(L[i], L[j]);
				swap(R[i], R[j]);
			}
		}
	}


	int good[2];
	vector<ii> extra[2];
	vector<int> zip, pfx_mx, sfx_mn;
	void setup(int lo, int hi) {
		// setup good (interval) & extra steps
		for (int inside : {0, 1}) {
			good[inside] = 0; extra[inside].clear();

			vector<ii> pfx = {{lo, 0}, {hi+1, 0}};
			for (int i = 0; i < (int)L.size(); ++i) {
				pfx.pb({L[i], 1});
				pfx.pb({R[i]+1, -1});
			}
			sort(pfx.begin(), pfx.end());

			{
				vector<ii> v;
				for (int i = 0; i < (int)pfx.size(); ++i)
				{
					if (!v.empty() && v.back().f1 == pfx[i].f1)
						v.back().s2 += pfx[i].s2;
					else v.pb(pfx[i]);
				}
				pfx = v;
			}
			for (int i = 1; i < (int)pfx.size(); ++i)
				pfx[i].s2 += pfx[i-1].s2;

			good[inside] = 0; int bad = 0;
			for (int i = 0; i+1 < (int)pfx.size(); ++i) {
				if ((pfx[i].s2 == 0) ^ (inside)) {
					// if inside is false, then [pfx[i].f1, pfx[i+1].f1) are outside any interval
					good[inside] += pfx[i+1].f1 - pfx[i].f1;	
				} else {
					bad += pfx[i+1].f1 - pfx[i].f1;

					if (!extra[inside].empty() && extra[inside].back().f1 == good[inside]) extra[inside].back().s2 = bad;
					else extra[inside].push_back({good[inside], bad});
				}
			}
		};

		// setup zip (coordinate compression), pfx_mx & sfx_mn
		zip.clear(); pfx_mx.clear(); sfx_mn.clear();
		for (int x : L)
			zip.pb(x);
		for (int x : R) 
			zip.pb(x);
		sort(zip.begin(), zip.end());
		zip.resize(unique(zip.begin(), zip.end()) - zip.begin());

		pfx_mx.resize(zip.size(), 0);
		sfx_mn.resize(zip.size(), MAXA + 1);
		for (int i = 0; i < (int)L.size(); ++i)
		{
			int id = (int)(lower_bound(zip.begin(), zip.end(), L[i]) - zip.begin());
			pfx_mx[id] = max(pfx_mx[id], R[i]);

			id = (int)(lower_bound(zip.begin(), zip.end(), R[i]) - zip.begin());
			sfx_mn[id] = min(sfx_mn[id], L[i]);
		}
		for (int i = 1; i < (int)zip.size(); ++i)
			pfx_mx[i] = max(pfx_mx[i], pfx_mx[i-1]);
		for (int i = (int)zip.size()-2; i >= 0; --i)
			sfx_mn[i] = min(sfx_mn[i], sfx_mn[i+1]);
	}

	int getRandomNumberWithRespectToInterval(bool inside) {
		int Z = rnd.nextInt(1, good[inside]);
		int id = (int)(upper_bound(extra[inside].begin(), extra[inside].end(), make_pair(Z, -1)) - extra[inside].begin());
		if (id != 0)
			Z += extra[inside][id-1].s2;
		return Z;
	}

	vector<int> getRepeatedStep(int init_x, int repeat) {
		vector<int> Z = { init_x };
		int P = init_x, Q = init_x;

		for (int rep = 1; rep < repeat; ++rep) {
			int rt = pfx_mx[upper_bound(zip.begin(), zip.end(), P) - zip.begin() - 1];
			int lt = sfx_mn[lower_bound(zip.begin(), zip.end(), Q) - zip.begin()];

			int nxt = rnd.nextInt(lt, rt);
			Z.pb(nxt); P = min(P, nxt); Q = max(Q, nxt); 
		}
		return Z;
	}

	vector<vector<int>> getSteps(int lo, int hi, int minStep, int maxStep, int cap) {
		vector<vector<int>> Z;
		while (cap) {

			int init_x = getRandomNumberWithRespectToInterval(true);
			if (cap <= maxStep) Z.pb(getRepeatedStep(init_x, cap)), cap = 0;
			else 
			{
				int step = rnd.nextInt(minStep, maxStep);
				Z.pb(getRepeatedStep(init_x, step));
				cap -= step;
			}
		}
		return Z;
	}

	void flattenSteps(vector<vector<int>> &steps, bool shuffle = false) {
		if (shuffle) {
			for (int i = 1; i < (int)steps.size(); ++i) {
				int j = rnd.nextInt(0, i);
				swap(steps[i], steps[j]);
			}
		}

		for (auto step : steps)
			for (int x : step)
				A.pb(x);
	}

	void generateSmallSteps(int lo, int hi) {
		setup(lo, hi);
		vector<vector<int>> steps = getSteps(lo, hi, 3, 6, M);
		flattenSteps(steps);
	}

	void generateMediumSteps(int lo, int hi) {
		setup(lo, hi);
		vector<vector<int>> steps = getSteps(lo, hi, min((int)sqrt(N)-2, 10), (int)sqrt(N), M);
		flattenSteps(steps);
	}

	void generateLargeSteps(int lo, int hi) {
		setup(lo, hi);
		vector<vector<int>> steps = getSteps(lo, hi, N/2, N, M);
		flattenSteps(steps);
	}

	void generateSmallAndMediumStep(int lo, int hi) {
		setup(lo, hi);

		int small = rnd.nextInt(M/3, 2*M/3);
		vector<vector<int>> smallSteps = getSteps(lo, hi, 3, 6, small);
		vector<vector<int>> medSteps = getSteps(lo, hi, min(10, (int)sqrt(N) - 2), (int)sqrt(N), M - small);

		for (auto steps : medSteps) smallSteps.pb(steps);
		flattenSteps(smallSteps, true);
	}

	void generateRandomSteps(int lo, int hi) {
		setup(lo, hi);

		for (int i = 0; i < M; ++i) {
			A.pb(getRandomNumberWithRespectToInterval(true));
		}
	}

	void sortSteps() {
		sort(A.begin(), A.end());
	}

	void setFailure(int repeat = 1) {
		assert(!A.empty());
		for (int rep = 0; rep < repeat; ++rep) {
			int id = rnd.nextInt(0, (int)A.size() - 1);
			A[id] = getRandomNumberWithRespectToInterval(false);
		}
	}
};