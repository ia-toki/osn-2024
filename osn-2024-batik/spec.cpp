#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

#define mp make_pair
#define fr first
#define sc second

const int MXNM = 500, MXQ = 1e5;
const int CNT23 = 10;

class ProblemSpec : public BaseProblemSpec
{
	protected:
		int N, M, Q, askCount;
		vector<vector<int>> A, events;
		vector<int> ans;

		void InputFormat()
		{
			LINE(N, M);
			GRID(A) % SIZE(N, M);
			LINE(Q);
			LINES(events) % SIZE(Q);
		}
		void OutputFormat()
		{
			LINES(ans) % SIZE(askCount);
		}
		void BeforeOutputFormat()
		{
			askCount = 0;
			for(int i = 0; i < events.size(); i++)
			{
				int type = events[i][0];
				if(type == 3)
				{
					askCount++;
				}
			}
		}
		void GradingConfig()
		{
			TimeLimit(2);
			MemoryLimit(512);
		}
		void Constraints()
		{
			CONS(1 <= N && N <= MXNM);
			CONS(1 <= M && M <= MXNM);
			CONS(eachElementBetween2(A, 0, N * M - 1));
			CONS(eachElementDistinct2(A));
			CONS(1 <= Q && Q <= MXQ);
			CONS(eachEventValid(events));
		}
		void Subtask1()
		{
			Points(9);
			CONS(maxCntEvents(events, 2, CNT23));
			CONS(maxCntEvents(events, 3, CNT23));
		}
		void Subtask2()
		{
			Points(10);
			CONS(maxCntEvents(events, 3, CNT23));
		}
		void Subtask3()
		{
			Points(15);
			CONS(maxCntEvents(events, 2, 0));
			CONS(specialType3Events(events));
		}
		void Subtask4()
		{
			Points(8);
			CONS(specialType3Events(events));
		}
		void Subtask5()
		{
			Points(28);
			CONS(maxCntEvents(events, 1, 0));
			CONS(maxCntEvents(events, 2, 0));
		}
		void Subtask6()
		{
			Points(23);
			CONS(maxCntEvents(events, 2, 0));
		}
		void Subtask7()
		{
			Points(7);
		}

	private:
		bool eachElementBetween(vector<int> &curV, int lo, int hi)
		{
			for(int i = 0; i < curV.size(); i++)
			{
				if(!(lo <= curV[i] && curV[i] <= hi))
				{
					return false;
				}
			}
			return true;
		}
		bool eachElementBetween2(vector<vector<int>> &curV, int lo, int hi)
		{
			for(int i = 0; i < curV.size(); i++)
			{
				if(!eachElementBetween(curV[i], lo, hi))
				{
					return false;
				}
			}
			return true;
		}
		bool eachElementDistinct2(vector<vector<int>> &curV)
		{
			vector<int> sortedV;
			for(int i = 0; i < curV.size(); i++)
			{
				sortedV.insert(sortedV.end(), curV[i].begin(), curV[i].end());
			}
			sort(sortedV.begin(), sortedV.end());
			
			for(int i = 0; i < (int)sortedV.size() - 1; i++)
			{
				if(sortedV[i] == sortedV[i + 1])
				{
					return false;
				}
			}
			return true;
		}
		bool eachEventValid(vector<vector<int>> &curEvents)
		{
			bool type3Exists = false;
			for(int i = 0; i < curEvents.size(); i++)
			{
				vector<int> event = curEvents[i];
				if(event.empty())
				{
					return false;
				}
				
				int type = event[0];
				if(type == 1)
				{
					if(event.size() != 5)
					{
						return false;
					}
					
					int R1, C1, R2, C2;
					R1 = event[1];
					C1 = event[2];
					R2 = event[3];
					C2 = event[4];
					if(!(1 <= R1 && R1 <= N && 1 <= C1 && C1 <= M))
					{
						return false;
					}
					if(!(1 <= R2 && R2 <= N && 1 <= C2 && C2 <= M))
					{
						return false;
					}
					if(mp(R1, C1) == mp(R2, C2))
					{
						return false;
					}
				}
				else if(type == 2)
				{
					if(event.size() != 2)
					{
						return false;
					}
					
					int W = event[1];
					if(!(1 <= W && W <= N * M - 1))
					{
						return false;
					}
				}
				else if(type == 3)
				{
					if(event.size() != 5)
					{
						return false;
					}
					
					int R1, C1, R2, C2;
					R1 = event[1];
					C1 = event[2];
					R2 = event[3];
					C2 = event[4];
					if(!(1 <= R1 && R1 <= R2 && R2 <= N))
					{
						return false;
					}
					if(!(1 <= C1 && C1 <= C2 && C2 <= M))
					{
						return false;
					}
					
					type3Exists = true;
				}
				else
				{
					return false;
				}
			}
			return type3Exists;
		}
		bool maxCntEvents(vector<vector<int>> &curEvents, int type, int maxCnt)
		{
			int cnt = 0;
			for(int i = 0; i < curEvents.size(); i++)
			{
				vector<int> event = curEvents[i];
				if(event[0] == type)
				{
					cnt++;
				}
			}
			return cnt <= maxCnt;
		}
		bool specialType3Events(vector<vector<int>> &curEvents)
		{
			for(int i = 0; i < curEvents.size(); i++)
			{
				vector<int> event = curEvents[i];
				int type = event[0];
				if(type == 3)
				{
					int R1, C1, R2, C2;
					R1 = event[1];
					C1 = event[2];
					R2 = event[3];
					C2 = event[4];
					if(!(R1 == 1 && C1 == 1 && R2 == (N + 1) / 2 && C2 == M))
					{
						return false;
					}
				}
			}
			return true;
		}
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
	protected:
		void SampleTestCase1()
		{
			Subtasks({1, 2, 7});
			Input
			({
				"4 3",
				"11 10 9",
				"2 6 7",
				"1 5 0",
				"3 8 4",
				"6",
				"3 2 1 3 3",
				"1 2 3 1 2",
				"2 7",
				"3 1 2 4 2",
				"3 1 1 4 3",
				"3 4 1 4 1",
			});
			Output
			({
				"3",
				"4",
				"-1",
				"0",
			});
		}
		void BeforeTestCase()
		{
			events.clear();
		}
		void AfterTestCase()
		{
			for(int i = 0; i < events.size(); i++)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 1 && rnd.nextInt(2))
				{
					swap(events[i][1], events[i][3]);
					swap(events[i][2], events[i][4]);
				}
			}
		}
		void TestGroup1()
		{
			Subtasks({1, 2, 3, 4, 5, 6, 7});
			
			// Case (1) small N M Q
			CASE(N = 1, M = 1, A = {{0}}, Q = 1, events = {{3, 1, 1, 1, 1}});
			
			// Case (2) small N M for sub 1 2
			CASE(N = 1, M = 1, A = permGrid(N, M), Q = CNT23, rndEvents(0, 0, CNT23, 0));
		}
		void TestGroup2()
		{
			Subtasks({1, 2, 7});
			
			// Case (1-2) pure rand
			CASE(N = rnd.nextInt(1, sqrt(MXNM)), M = rnd.nextInt(1, sqrt(MXNM)), A = permGrid(N, M), Q = rnd.nextInt(sqrt(MXQ) / 2, sqrt(MXQ)), rndEvents(Q - CNT23 * 2, CNT23, CNT23, 10));
			CASE(N = MXNM, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q - CNT23 * 2, CNT23, CNT23, 100));
			
			// Case (3-5) gradual grid
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q - CNT23 * 2, CNT23, CNT23, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q - CNT23 * 2, CNT23, CNT23, 10), makeType1Adjacent(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q - CNT23 * 2, CNT23, CNT23, 100), makeType1Adjacent(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			
			// Case (6) narrow grid
			CASE(N = 1, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q - CNT23 * 2, CNT23, CNT23, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
		}
		void TestGroup3()
		{
			Subtasks({2, 7});
			
			// Case (1-2) pure rand
			CASE(N = rnd.nextInt(1, sqrt(MXNM)), M = rnd.nextInt(1, sqrt(MXNM)), A = permGrid(N, M), Q = rnd.nextInt(sqrt(MXQ) / 2, sqrt(MXQ)), rndEvents((Q - CNT23) / 2, Q - CNT23 - (Q - CNT23) / 2, CNT23, 10));
			CASE(N = MXNM, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents((Q - CNT23) / 2, Q - CNT23 - (Q - CNT23) / 2, CNT23, 100));
			
			// Case (3-5) gradual grid
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents((Q - CNT23) / 2, Q - CNT23 - (Q - CNT23) / 2, CNT23, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents((Q - CNT23) / 2, Q - CNT23 - (Q - CNT23) / 2, CNT23, 10), makeType1Adjacent(), makeType2Alternating(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents((Q - CNT23) / 2, Q - CNT23 - (Q - CNT23) / 2, CNT23, 100), makeType1Adjacent(), makeType2Alternating(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			
			// (6) narrow grid
			CASE(N = MXNM, M = 1, A = permGrid(N, M), Q = MXQ, rndEvents((Q - CNT23) / 2, Q - CNT23 - (Q - CNT23) / 2, CNT23, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
		}
		void TestGroup4()
		{
			Subtasks({3, 4, 5, 6, 7});
			
			// Case (1) small N M for sub 3 4 5 6 7
			CASE(N = 1, M = 1, A = permGrid(N, M), Q = MXQ, rndEvents(0, 0, Q, 0));
		}
		void TestGroup5()
		{
			Subtasks({3, 4, 6, 7});
			
			// Case (1-2) pure rand
			CASE(N = rnd.nextInt(1, sqrt(MXNM)), M = rnd.nextInt(1, sqrt(MXNM)), A = permGrid(N, M), Q = rnd.nextInt(sqrt(MXQ) / 2, sqrt(MXQ)), rndEvents(Q / 2, 0, Q - Q / 2, 10), makeType3Special());
			CASE(N = MXNM, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100), makeType3Special());
			
			// Case (3-4) half half grid
			CASE(N = MXNM, M = MXNM, A = halfHalfGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100), makeType3Special(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = halfHalfGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100), makeType1Reset(Q / 2), makeType3Special(), getAFromMiddle(Q / 2));
			
			// Case (5) narrow grid
			CASE(N = 1, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100), makeType3Special(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
		}
		void TestGroup6()
		{
			Subtasks({4, 7});
			
			// Case (1-2) pure rand
			CASE(N = rnd.nextInt(1, sqrt(MXNM)), M = rnd.nextInt(1, sqrt(MXNM)), A = permGrid(N, M), Q = rnd.nextInt(sqrt(MXQ) / 2, sqrt(MXQ)), rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 10), makeType3Special());
			CASE(N = MXNM, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100), makeType3Special());
			
			// Case (3-4) half half grid
			CASE(N = MXNM, M = MXNM, A = halfHalfGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100), makeType3Special(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = halfHalfGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100), makeType1Reset(Q / 2), makeType2Alternating(), makeType3Special(), getAFromMiddle(Q / 2));
			
			// Case (5) narrow grid
			CASE(N = 1, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100), makeType3Special(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
		}
		void TestGroup7()
		{
			Subtasks({5, 6, 7});
			
			// Case (1-2) pure rand
			CASE(N = rnd.nextInt(1, sqrt(MXNM)), M = rnd.nextInt(1, sqrt(MXNM)), A = permGrid(N, M), Q = rnd.nextInt(sqrt(MXQ) / 2, sqrt(MXQ)), rndEvents(0, 0, Q, 10));
			CASE(N = MXNM, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(0, 0, Q, 100));
			
			// Case (3-4) gradual grid
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(0, 0, Q, 10), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(0, 0, Q, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			
			// Case (5) narrow grid
			CASE(N = MXNM, M = 1, A = permGrid(N, M), Q = MXQ, rndEvents(0, 0, Q, 10), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
		}
		void TestGroup8()
		{
			Subtasks({6, 7});
			
			// Case (1-2) pure rand
			CASE(N = rnd.nextInt(1, sqrt(MXNM)), M = rnd.nextInt(1, sqrt(MXNM)), A = permGrid(N, M), Q = rnd.nextInt(sqrt(MXQ) / 2, sqrt(MXQ)), rndEvents(Q / 2, 0, Q - Q / 2, 10));
			CASE(N = MXNM, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100));
			
			// Case (3-6) gradual grid
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 10), makeType1Adjacent(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100), makeType1Adjacent(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100), makeType1SameValue(Q / 2, 10), getAFromMiddle(Q / 2));
			
			// Case (7) narrow grid
			CASE(N = 1, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q / 2, 0, Q - Q / 2, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
		}
		void TestGroup9()
		{
			Subtasks({7});
			
			// Case (1-2) pure rand
			CASE(N = rnd.nextInt(1, sqrt(MXNM)), M = rnd.nextInt(1, sqrt(MXNM)), A = permGrid(N, M), Q = rnd.nextInt(sqrt(MXQ) / 2, sqrt(MXQ)), rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 10));
			CASE(N = MXNM, M = MXNM, A = permGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100));
			
			// Case (3-6) gradual grid
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 10), makeType1Adjacent(), makeType2Alternating(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100), makeType1Adjacent(), makeType2Alternating(), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
			CASE(N = MXNM, M = MXNM, A = gradualGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100), makeType1SameValue(Q / 2, 10), makeType2Alternating(), getAFromMiddle(Q / 2));
			
			// Case (7) narrow grid
			CASE(N = MXNM, M = 1, A = permGrid(N, M), Q = MXQ, rndEvents(Q / 3, Q / 3, Q - Q / 3 * 2, 100), getAFromMiddle(rnd.nextInt(Q / 3, Q * 2 / 3)));
		}

	private:
		int wrnd(int lo, int hi, int w)
		{
			int ret = rnd.nextInt(lo, hi);
			if(w > 0)
			{
				for(int i = 0; i < w; i++)
				{
					ret = max(ret, rnd.nextInt(lo, hi));
				}
			}
			else
			{
				for(int i = 0; i < -w; i++)
				{
					ret = min(ret, rnd.nextInt(lo, hi));
				}
			}
			return ret;
		}
		vector<int> rndArray(int sz, int lo, int hi)
		{
			vector<int> ret;
			for(int i = 0; i < sz; i++)
			{
				ret.push_back(rnd.nextInt(lo, hi));
			}
			return ret;
		}
		vector<int> wrndArray(int sz, int lo, int hi, int w)
		{
			vector<int> ret;
			for(int i = 0; i < sz; i++)
			{
				ret.push_back(wrnd(lo, hi, w));
			}
			return ret;
		}
		vector<int> nonDecreasingArray(int sz, int lo, int hi)
		{
			vector<int> ret = rndArray(sz, lo, hi);
			sort(ret.begin(), ret.end());
			return ret;
		}
		vector<int> increasingArray(int sz, int lo, int hi)
		{
			vector<int> ret = nonDecreasingArray(sz, lo, hi - (sz - 1));
			for(int i = 0; i < sz; i++)
			{
				ret[i] += i;
			}
			return ret;
		}
		vector<int> distinctArray(int sz, int lo, int hi)
		{
			vector<int> ret = increasingArray(sz, lo, hi);
			rnd.shuffle(ret.begin(), ret.end());
			return ret;
		}
		vector<vector<int>> permGrid(int sz, int sz2)
		{
			vector<int> vals = distinctArray(sz * sz2, 0, sz * sz2 - 1);
			
			vector<vector<int>> ret;
			for(int i = 0; i < sz; i++)
			{
				vector<int> v;
				for(int j = 0; j < sz2; j++)
				{
					v.push_back(vals.back());
					vals.pop_back();
				}
				ret.push_back(v);
			}
			return ret;
		}
		vector<vector<int>> gradualGrid(int sz, int sz2)
		{
			vector<vector<int>> ret;
			for(int i = 0; i < sz; i++)
			{
				vector<int> v(sz2, 0);
				ret.push_back(v);
			}
			
			vector<int> directions;
			directions.insert(directions.end(), sz - 1, 0);
			directions.insert(directions.end(), sz2 - 1, 1);
			rnd.shuffle(directions.begin(), directions.end());
			
			int ub, db, lb, rb, p;
			ub = 0;
			db = sz - 1;
			lb = 0;
			rb = sz2 - 1;
			p = sz * sz2;
			for(int i = 0; i < directions.size(); i++)
			{
				if(directions[i] == 0)
				{
					int len = rb - lb + 1;
					vector<int> vals = distinctArray(len, p - len, p - 1);
					
					if(rnd.nextInt(0, 1))
					{
						for(int j = 0; j < len; j++)
						{
							ret[ub][lb + j] = vals[j];
						}
						
						ub++;
					}
					else
					{
						for(int j = 0; j < len; j++)
						{
							ret[db][lb + j] = vals[j];
						}
						
						db--;
					}
					
					p -= len;
				}
				else
				{
					int len = db - ub + 1;
					vector<int> vals = distinctArray(len, p - len, p - 1);
					
					if(rnd.nextInt(0, 1))
					{
						for(int j = 0; j < len; j++)
						{
							ret[ub + j][lb] = vals[j];
						}
						
						lb++;
					}
					else
					{
						for(int j = 0; j < len; j++)
						{
							ret[ub + j][rb] = vals[j];
						}
						
						rb--;
					}
					
					p -= len;
				}
			}
			
			return ret;
		}
		vector<vector<int>> halfHalfGrid(int sz, int sz2)
		{
			vector<vector<int>> ret;
			
			vector<int> vals = distinctArray((sz + 1) / 2 * sz2, 0, (sz + 1) / 2 * sz2 - 1);
			for(int i = 0; i < (sz + 1) / 2; i++)
			{
				vector<int> v;
				for(int j = 0; j < sz2; j++)
				{
					v.push_back(vals.back());
					vals.pop_back();
				}
				ret.push_back(v);
			}
			
			vals = distinctArray(sz / 2 * sz2, (sz + 1) / 2 * sz2, sz * sz2 - 1);
			for(int i = 0; i < sz / 2; i++)
			{
				vector<int> v;
				for(int j = 0; j < sz2; j++)
				{
					v.push_back(vals.back());
					vals.pop_back();
				}
				ret.push_back(v);
			}
			
			return ret;
		}
		void rndEvents(int cnt1, int cnt2, int cnt3, int w)
		{
			for(int i = 0; i < cnt1; i++)
			{
				int p1, p2;
				p1 = rnd.nextInt(0, N * M - 1);
				p2 = rnd.nextInt(0, N * M - 2);
				if(p2 >= p1)
				{
					p2++;
				}
				
				int R1, C1, R2, C2;
				R1 = p1 / M + 1;
				C1 = p1 % M + 1;
				R2 = p2 / M + 1;
				C2 = p2 % M + 1;
				events.push_back({1, R1, C1, R2, C2});
			}
			for(int i = 0; i < cnt2; i++)
			{
				int W = rnd.nextInt(1, N * M - 1);
				events.push_back({2, W});
			}
			for(int i = 0; i < cnt3; i++)
			{
				int R1, C1, R2, C2;
				R1 = wrnd(1, N, -w);
				C1 = wrnd(1, M, -w);
				R2 = wrnd(1, N, w);
				C2 = wrnd(1, M, w);
				if(R1 > R2)
				{
					swap(R1, R2);
				}
				if(C1 > C2)
				{
					swap(C1, C2);
				}
				events.push_back({3, R1, C1, R2, C2});
			}
			rnd.shuffle(events.begin(), events.end());
		}
		void makeType1Adjacent()
		{
			for(int i = 0; i < events.size(); i++)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 1)
				{
					int R1, C1, R2, C2;
					if(rnd.nextInt((N - 1) * M + N * (M - 1)) <= (N - 1) * M)
					{
						R1 = rnd.nextInt(1, N - 1);
						C1 = rnd.nextInt(1, M);
						R2 = R1 + 1;
						C2 = C1;
					}
					else
					{
						R1 = rnd.nextInt(1, N);
						C1 = rnd.nextInt(1, M - 1);
						R2 = R1;
						C2 = C1 + 1;
					}
					events[i] = {1, R1, C1, R2, C2};
				}
			}
		}
		tuple<int, int> getRCImportant(int centerR, int centerC, int w)
		{
			if(rnd.nextInt(5) == 0)
			{
				return {centerR, centerC};
			}
			else
			{
				int R, C;
				if(rnd.nextInt(2))
				{
					R = wrnd(1, N, -w);
				}
				else
				{
					R = wrnd(1, N, w);
				}
				if(rnd.nextInt(2))
				{
					C = wrnd(1, M, -w);
				}
				else
				{
					C = wrnd(1, M, w);
				}
				return {R, C};
			}
		}
		void addCenterType1(int pos, int centerR, int centerC)
		{
			int lef = pos - 1;
			while(lef >= 0)
			{
				vector<int> event = events[lef];
				int type = event[0];
				if(type == 1)
				{
					break;
				}
				
				lef--;
			}
			
			int rig = pos;
			while(rig < Q)
			{
				vector<int> event = events[rig];
				int type = event[0];
				if(type == 1)
				{
					break;
				}
				
				rig++;
			}
			
			if(lef >= 0)
			{
				events[lef][3] = centerR;
				events[lef][4] = centerC;
			}
			if(rig < Q)
			{
				events[rig][1] = centerR;
				events[rig][2] = centerC;
			}
		}
		void makeType1SameValue(int mid, int w)
		{
			int centerR, centerC;
			for(int i = 1; i <= N; i++)
			{
				for(int j = 1; j <= M; j++)
				{
					if(A[i - 1][j - 1] == 0)
					{
						centerR = i;
						centerC = j;
					}
				}
			}
			
			int lastR, lastC;
			tie(lastR, lastC) = getRCImportant(centerR, centerC, w);
			for(int i = 0; i < Q; i++)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 1)
				{
					int R, C;
					tie(R, C) = getRCImportant(centerR, centerC, w);
					events[i] = {1, lastR, lastC, R, C};
					lastR = R;
					lastC = C;
				}
			}
			
			addCenterType1(mid, centerR, centerC);
			
			for(int i = 0; i < Q; i++)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 1)
				{
					int R1, C1, R2, C2;
					R1 = event[1];
					C1 = event[2];
					R2 = event[3];
					C2 = event[4];
					if(mp(R1, C1) == mp(R2, C2))
					{
						R1 = wrnd(1, N, -w);
						C1 = wrnd(1, M, -w);
						R2 = wrnd(1, N, w);
						C2 = wrnd(1, M, w);
						if(R1 > R2)
						{
							swap(R1, R2);
						}
						if(C1 > C2)
						{
							swap(C1, C2);
						}
						events[i] = {3, R1, C1, R2, C2};
					}
				}
			}
		}
		void makeType1Reset(int mid)
		{
			int R1, C1, R2, C2;
			
			R1 = -1;
			for(int i = mid - 1; i >= 0; i--)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 1)
				{
					if(R1 == -1)
					{
						R1 = event[1];
						C1 = event[2];
						R2 = event[3];
						C2 = event[4];
					}
					else
					{
						events[i] = {1, R1, C1, R2, C2};
						R1 = -1;
					}
				}
			}
			
			R1 = -1;
			for(int i = mid; i < Q; i++)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 1)
				{
					if(R1 == -1)
					{
						R1 = event[1];
						C1 = event[2];
						R2 = event[3];
						C2 = event[4];
					}
					else
					{
						events[i] = {1, R1, C1, R2, C2};
						R1 = -1;
					}
				}
			}
		}
		void makeType2Alternating()
		{
			int w = rnd.nextInt(1, N * M - 1);
			for(int i = 0; i < events.size(); i++)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 2)
				{
					events[i][1] = w;
					w = (N * M) - w;
				}
			}
		}
		void makeType3Special()
		{
			for(int i = 0; i < events.size(); i++)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 3)
				{
					events[i] = {3, 1, 1, (N + 1) / 2, M};
				}
			}
		}
		void getAFromMiddle(int mid)
		{
			int offset = 0;
			for(int i = mid - 1; i >= 0; i--)
			{
				vector<int> event = events[i];
				int type = event[0];
				if(type == 1)
				{
					int R1, C1, R2, C2;
					R1 = event[1];
					C1 = event[2];
					R2 = event[3];
					C2 = event[4];
					swap(A[R1 - 1][C1 - 1], A[R2 - 1][C2 - 1]);
				}
				else if(type == 2)
				{
					int W = event[1];
					offset = (offset + W) % (N * M);
				}
			}
			
			for(int i = 0; i < N; i++)
			{
				for(int j = 0; j < M; j++)
				{
					A[i][j] = (A[i][j] + N * M - offset) % (N * M);
				}
			}
		}
};
