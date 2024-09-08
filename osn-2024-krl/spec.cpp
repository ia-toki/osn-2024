#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAX_N = 100000;
const int MAX_M = 200000;
const int MAX_K = 100000;
const int MAX_T = 100000;
const int MAX_C = 100000;
const int MAX_D = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, M, P, Q, K, T;
  vector<int> A, B, C, D;

  long long ans;

  void InputFormat() {
    LINE(N, M, K, T, P, Q);
    LINES(A, B, C, D) % SIZE(M);
  }

  void OutputFormat() { LINE(ans); }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAX_N);
    CONS(1 <= M && M <= MAX_M);
    CONS(1 <= K && K <= MAX_K);
    CONS(0 <= T && T <= MAX_T);
    CONS(1 <= P && P <= N);
    CONS(1 <= Q && Q <= N);
    CONS(P != Q);
    CONS(eachElementBetween(A, 1, N));
    CONS(eachElementIsSmallerThan(A, B));
    CONS(eachElementBetween(B, 1, N));
    CONS(eachElementBetween(C, 1, MAX_C));
    CONS(eachElementBetween(D, 1, MAX_D));
  }

  void Subtask1() {
    Points(8);

    CONS(N == 20);
    CONS(M == 3);
    CONS(K == 10);
    CONS(T == 1);
    CONS(P == 4);
    CONS(Q == 18);
    CONS(A == vector<int>({1, 2, 17}));
    CONS(B == vector<int>({4, 20, 20}));
    CONS(C == vector<int>({11, 10, 9}));
    CONS(D == vector<int>({7, 100, 7}));
  }

  void Subtask2() {
    Points(11);

    CONS(eachElementBetween(A, 1, 1));
    CONS(eachElementBetween(B, N, N));
  }

  void Subtask3() {
    Points(21);

    CONS(N <= 1000);
    CONS(M <= 5);
    CONS(T == 0);
  }

  void Subtask4() {
    Points(23);
    CONS(M <= 5);
  }

  void Subtask5() {
    Points(26);
    CONS(T == 0);
  }

  void Subtask6() { Points(11); }

private:
  bool eachElementBetween(const vector<int> &v, int lo, int hi) {
    for (int x : v) {
      if (x < lo || x > hi) {
        return false;
      }
    }
    return true;
  }
  bool eachElementIsSmallerThan(const vector<int> &a, const vector<int> &b) {
    if (a.size() != b.size()) {
      return false;
    }
    int n = a.size();
    for (int i = 0; i < n; ++i) {
      if (a[i] >= b[i]) {
        return false;
      }
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({4, 6});

    Input({"10 2 10 1 9 5", "7 10 10 8", "1 6 8 1"});
    Output({"38"});
  }

  void SampleTestCase2() {
    Subtasks({4, 6});

    Input({"16 3 3 1 2 14", "1 9 2 12", "4 7 4 5", "12 15 3 1"});
    Output({"28"});
  }

  void SampleTestCase3() {
    Subtasks({2, 4, 6});

    Input({"4 1 10 100 4 1", "1 4 1 1"});
    Output({"30"});
  }


  void TestGroup1() {
    Subtasks({1, 4, 6});

    CASE(N = 20, M = 3, K = 10, T = 1, P = 4, Q = 18, A = {1, 2, 17},
         B = {4, 20, 20}, C = {11, 10, 9}, D = {7, 100, 7});
  }

  void TestGroup2() {
    vector<int> result;
    Subtasks({2, 3, 4, 5, 6});

    // Case 1: Public Transportation
    // Case 2: Commuter
    // Case 3 - 4: Public Transportation -> Express -> Public Transportation
    // Case 5 - 6: Commuter -> Express -> Commuter
    for (auto type : {1, 2, 3, 4}) {
      int cases = vector<int>({1, 1, 2, 2})[type - 1];

      while (cases--) {
        int n = randomInt(900, 1000);
        int m = randomInt(4, 5);

        do {
          result = randomSubtask2(n, 0);
        } while (result[0] != type);

        CASE(N = n, M = m, K = result[1], T = result[2], P = result[3],
             Q = result[4], A = randomFill(m, 1, 1), B = randomFill(m, n, n),
             C = randomFill(m, result[5], min(MAX_C, 2 * result[5]),
                            {result[5]}),
             D = randomFill(m, result[6], min(MAX_D, 2 * result[6]),
                            {result[6]}));
      }
    }

    CASE(N = 30, M = 5, K = 100, T = 0, P = 1, Q = 30, A = randomFill(5, 1, 1),
         B = randomFill(5, 30, 30), C = randomFill(5, 100, 100),
         D = randomFill(5, 2024, 2024));
    CASE(N = 2, M = 1, K = 1, T = 0, P = 1, Q = 2, A = {1}, B = {2}, C = {1},
         D = {1});
  }

  void TestGroup3() {
    vector<int> result;
    Subtasks({2, 4, 5, 6});

    // Case 1: Public Transportation
    // Case 2: Commuter
    // Case 3: Public Transportation -> Express -> Public Transportation
    // Case 4: Commuter -> Express -> Commuter
    for (auto type : {1, 2, 3, 4}) {
      int cases = vector<int>({1, 1, 1, 1})[type - 1];

      while (cases--) {
        int n = randomInt(4 * MAX_N / 5, MAX_N);
        int m = randomInt(4, 5);

        do {
          result = randomSubtask2(n, 0);
        } while (result[0] != type);

        CASE(N = n, M = m, K = result[1], T = result[2], P = result[3],
             Q = result[4], A = randomFill(m, 1, 1), B = randomFill(m, n, n),
             C = randomFill(m, result[5], min(MAX_C, 2 * result[5]),
                            {result[5]}),
             D = randomFill(m, result[6], min(MAX_D, 2 * result[6]),
                            {result[6]}));
      }
    }
  }

  void TestGroup4() {
    vector<int> result;
    Subtasks({2, 4, 6});

    // Case 1: Public Transportation (Overflow)
    CASE(N = MAX_N, M = 1, K = MAX_K, T = MAX_T, P = 1,
         Q = (int)(MAX_N / 2) + 1, A = {1}, B = {MAX_N}, C = {MAX_C},
         D = {MAX_D});

    // Case 2: Public Transportation
    // Case 3: Commuter
    // Case 4: Public Transportation -> Express -> Public Transportation
    // Case 5: Commuter -> Express -> Commuter
    for (auto type : {1, 2, 3, 4}) {
      int cases = vector<int>({1, 1, 1, 1})[type - 1];

      while (cases--) {
        int n = randomInt(MAX_N - 10000, MAX_N);
        int m = 5;

        do {
          result = randomSubtask2(n);
        } while (result[0] != type);

        CASE(N = n, M = m, K = result[1], T = result[2], P = result[3],
             Q = result[4], A = randomFill(m, 1, 1), B = randomFill(m, n, n),
             C = randomFill(m, result[5], min(MAX_C, (int)(1.5 * result[5])),
                            {result[5]}),
             D = randomFill(m, result[6], min(MAX_D, (int)(1.5 * result[6])),
                            {result[6]}));
      }
    }
  }

  void TestGroup5() {
    vector<int> result;
    Subtasks({2, 5, 6});

    // Case 2: Public Transportation
    // Case 3: Commuter
    // Case 4: Public Transportation -> Express -> Public Transportation
    // Case 5: Commuter -> Express -> Commuter
    for (auto type : {1, 2, 3, 4}) {
      int cases = vector<int>({1, 1, 1, 1})[type - 1];

      while (cases--) {
        int n = randomInt(MAX_N - 10000, MAX_N);
        int m = randomInt(MAX_M - 10000, MAX_M);

        do {
          result = randomSubtask2(n, 0);
        } while (result[0] != type);

        CASE(N = n, M = m, K = result[1], T = result[2], P = result[3],
             Q = result[4], A = randomFill(m, 1, 1), B = randomFill(m, n, n),
             C = randomFill(m, result[5], min(MAX_C, (int)(1.5 * result[5])),
                            {result[5]}),
             D = randomFill(m, result[6], min(MAX_D, (int)(1.5 * result[6])),
                            {result[6]}));
      }
    }
  }

  void TestGroup6() {
    int n, m;
    vector<int> result;
    Subtasks({2, 6});

    // Brainrot Random
    CASE(N = 30, M = 30, K = randomInt(1, MAX_K), T = randomInt(1, MAX_T),
         P = randomInt(1, 30), Q = randomInt(1, 30), A = randomFill(30, 1, 1),
         B = randomFill(30, 30, 30), C = randomFill(30, 1, MAX_C),
         D = randomFill(30, 1, MAX_D));

    // Case 1 - 2: Public Transportation
    // Case 3 - 4: Commuter
    // Case 5 - 6: Public Transportation -> Express -> Public Transportation
    // Case 7 - 8: Commuter -> Express -> Commuter
    for (auto type : {1, 2, 3, 4}) {
      int cases = vector<int>({2, 2, 2, 2})[type - 1];

      while (cases--) {
        int n = randomInt(MAX_N / 2, MAX_N);
        int m = randomInt(n / 2, MAX_M);

        do {
          result = randomSubtask2(n);
        } while (result[0] != type);

        CASE(N = n, M = m, K = result[1], T = result[2], P = result[3],
             Q = result[4], A = randomFill(m, 1, 1), B = randomFill(m, n, n),
             C = randomFill(m, result[5], min(MAX_C, (int)(1.5 * result[5])),
                            {result[5]}),
             D = randomFill(m, result[6], min(MAX_D, (int)(1.5 * result[6])),
                            {result[6]}));
      }
    }

    // Case 9: Smallest Constraint
    CASE(N = 1001, M = 6, K = 2, T = 1, P = 1, Q = 1001,
         A = randomFill(6, 1, 1), B = randomFill(6, 1001, 1001),
         C = vector<int>({1, 1, 1, 1, 1, 1}),
         D = vector<int>({2, 2, 2, 2, 2, 2}));
  }

  void TestGroup7() {
    vector<vector<int>> result;
    Subtasks({3, 4, 5, 6});

    CASE(N = 1000, M = 5, K = 99999, T = 0, P = 1000, Q = 1,
         A = vector<int>({1, 180, 380, 580, 780}),
         B = vector<int>({200, 400, 600, 800, 1000}),
         C = vector<int>({MAX_C, MAX_C, MAX_C, MAX_C, MAX_C}),
         D = vector<int>({1, 1, 1, 1, 1}));

    result = randomAlternate(1000, 5, 85, 95, -10, 5);
    CASE(N = 1000, M = 5, K = 100, T = 0, P = 1000, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    CASE(N = 30, M = 2, K = 10, T = 0, P = 5, Q = 9, A = vector<int>({7, 1}),
         B = vector<int>({10, 6}), C = vector<int>({10, 8}),
         D = vector<int>({8, 1}));

    CASE(N = 30, M = 3, K = 3, T = 0, P = 14, Q = 2,
         A = vector<int>({1, 4, 12}), B = vector<int>({9, 7, 15}),
         C = vector<int>({2, 4, 3}), D = vector<int>({12, 5, 1}));

    // Alternate between {Public Transportation, Commuter}
    result = randomAlternate(1000, 5, 2000, 3000, 0, 0);
    CASE(N = 1000, M = 5, K = 2500, T = 0, P = 1000, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Alternate between {Public Transportation, Express}
    result = randomAlternate(1000, 5, 2500, 2500, -5, 0);
    CASE(N = 1000, M = 5, K = 2500, T = 0, P = 1000, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Alternate between {Public Transportation, Commuter / Express}
    result = randomAlternate(1000, 5, 2499, 2501, -1000, 1000);
    CASE(N = 1000, M = 5, K = 2500, T = 0, P = 1000, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Alternate between {Public Transportation (->), Express, Public
    // Transportation (<-)}
    CASE(N = 1000, M = 5, K = MAX_K - 1, T = 0, P = 1000, Q = 1,
         A = vector<int>({1, 1000 / 5 - 20, 2 * 1000 / 5 - 20,
                          3 * 1000 / 5 - 20, 4 * 1000 / 5 - 20}),
         B = vector<int>(
             {1000 / 5, 2 * 1000 / 5, 3 * 1000 / 5, 4 * 1000 / 5, 1000}),
         C = vector<int>({MAX_C, MAX_C, MAX_C, MAX_C, MAX_C}),
         D = randomFill(5, 1, 1000));

    // Alternate between {Express (<-), Express (->)}
    CASE(
        N = 1000, M = 5, K = MAX_K - 1, T = 0, P = 420, Q = 1,
        A = vector<int>({1, 1000 / 5, 1000 / 5, 2 * 1000 / 5, 2 * 1000 / 5}),
        B = vector<int>({1000, 1000, 4 * 1000 / 5, 4 * 1000 / 5, 3 * 1000 / 5}),
        C = vector<int>({MAX_C, MAX_C, MAX_C, MAX_C, MAX_C}),
        D = vector<int>({1000000, 1000000, 1000000, 1000000, 1000000}));

    // Public Transportation
    CASE(N = 1000, M = 1, K = MAX_K - 1, T = 0, P = 1, Q = 1000,
         A = vector<int>({1}), B = vector<int>({2}), C = vector<int>({MAX_C}),
         D = vector<int>({1000000000}));
  }

  void TestGroup8() {
    vector<int> a, b, c, d;
    vector<vector<int>> result;
    Subtasks({4, 5, 6});

    // Case 1: Alternate between {Public Transportation, Commuter}
    result = randomAlternate(MAX_N, 5, 2000, 3000, 0, 0);
    CASE(N = MAX_N, M = 5, K = 2500, T = 0, P = MAX_N, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 2: Alternate between {Public Transportation, Express}
    result = randomAlternate(1000, 5, 2500, 2500, -5, 0);
    CASE(N = MAX_N, M = 5, K = 2500, T = 0, P = MAX_N, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 3: Alternate between {Public Transportation, Commuter / Express}
    result = randomAlternate(100000, 5, 2499, 2501, -1000, 1000);
    CASE(N = MAX_N, M = 5, K = 2500, T = 0, P = MAX_N, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 4: Nested Intervals
    result = randomNested(1, MAX_N, 5);
    c = randomFill(5, 8990, 9010);
    CASE(N = MAX_N, M = 5, K = 9000, T = 0, P = randomInt(1, 10000),
         Q = randomInt(MAX_N - 10000, MAX_N), A = result[0], B = result[1],
         C = c, D = randomExpress(result[0], result[1], c, -1, 1));

    // Case 5: Connected End
    result = add({randomNested(1, (int)MAX_N / 3, 2),
                  randomNested((int)2 * MAX_N / 3, MAX_N, 2),
                  {{1}, {MAX_N}}});
    c = vector<int>({49999, 29999, 49999, 29999, MAX_C});
    d = vector<int>({100000, 100000, 100000, 100000, 1});
    CASE(N = MAX_N, M = 5, K = MAX_K, T = 0, P = (int)MAX_N / 3,
         Q = (int)2 * MAX_N / 3, A = result[0], B = result[1], C = c, D = d);

    // Case 6: Alternate between {Public Transportation (->), Express, Public
    // Transportation (<-)}
    CASE(N = MAX_N, M = 5, K = MAX_K - 1, T = 0, P = MAX_N, Q = 1,
         A = vector<int>({1, MAX_N / 5 - 2000, 2 * MAX_N / 5 - 2000,
                          3 * MAX_N / 5 - 2000, 4 * MAX_N / 5 - 2000}),
         B = vector<int>(
             {MAX_N / 5, 2 * MAX_N / 5, 3 * MAX_N / 5, 4 * MAX_N / 5, MAX_N}),
         C = vector<int>({MAX_C, MAX_C, MAX_C, MAX_C, MAX_C}),
         D = randomFill(5, 1, 1000));

    // Case 7: Alternate between {Express (<-), Express (->)}
    CASE(N = MAX_N, M = 5, K = MAX_K - 1, T = 0, P = 42069, Q = 1,
         A = vector<int>(
             {1, MAX_N / 5, MAX_N / 5, 2 * MAX_N / 5, 2 * MAX_N / 5}),
         B = vector<int>(
             {MAX_N, MAX_N, 4 * MAX_N / 5, 4 * MAX_N / 5, 3 * MAX_N / 5}),
         C = vector<int>({MAX_C, MAX_C, MAX_C, MAX_C, MAX_C}),
         D = vector<int>({1000000, 1000000, 1000000, 1000000, 1000000}));

    // Case 8: Public Transportation
    CASE(N = MAX_N, M = 1, K = MAX_K - 1, T = 0, P = 1, Q = MAX_N,
         A = vector<int>({1}), B = vector<int>({2}), C = vector<int>({MAX_C}),
         D = vector<int>({1000000000}));
  }

  void TestGroup9() {
    vector<int> a, b, c, d;
    vector<vector<int>> result;
    Subtasks({4, 6});

    // Case 1: Alternate between {Public Transportation, Commuter}
    result = randomAlternate(1000, 5, 85, 95, 1, 10);
    CASE(N = 1000, M = 5, K = 100, T = 10, P = 1000, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 2: Alternate between {Public Transportation, Express}
    result = randomAlternate(1000, 5, 85, 95, -6, 0);
    CASE(N = 1000, M = 5, K = 100, T = 10, P = 1000, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 3: Alternate between {Public Transportation, Commuter / Express}
    result = randomAlternate(1000, 5, 85, 95, -10, 5);
    CASE(N = 1000, M = 5, K = 100, T = 10, P = 1000, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 4: Nested Intervals
    result = randomNested(1, 1000, 5);
    c = randomFill(5, 8990, 9010);
    CASE(N = 1000, M = 5, K = 9000, T = 1, P = randomInt(1, 100),
         Q = randomInt(900, 999), A = result[0], B = result[1], C = c,
         D = randomExpress(result[0], result[1], c, -1, 1));

    // Case 5: Multi Nested Intervals
    result = add({randomNested(1, 500, 2), randomNested(501, 1000, 3)});
    c = randomFill(5, 8990, 9010);
    CASE(N = 1000, M = 5, K = 9000, T = 1, P = 998, Q = 3, A = result[0],
         B = result[1], C = c,
         D = randomExpress(result[0], result[1], c, -5, 5));

    // Case 6: Connected End
    result = add(
        {randomNested(1, 333, 2), randomNested(667, 1000, 2), {{1}, {1000}}});
    c = vector<int>({49999, 29999, 49999, 29999, MAX_C});
    d = vector<int>({100000, 100000, 100000, 100000, 1});
    CASE(N = 1000, M = 5, K = 100000, T = 1, P = 333, Q = 667, A = result[0],
         B = result[1], C = c, D = d);

    // Case 7: Alternate between {Public Transportation (->), Express, Public
    // Transportation (<-)}
    CASE(N = 1000, M = 5, K = 99999, T = 1, P = 1000, Q = 1,
         A = vector<int>({1, 180, 380, 580, 780}),
         B = vector<int>({200, 400, 600, 800, 1000}),
         C = vector<int>({MAX_C, MAX_C, MAX_C, MAX_C, MAX_C}),
         D = vector<int>({1, 1, 1, 1, 1}));

    // Case 8: Alternate between {Express (<-), Express (->)}
    CASE(N = 1000, M = 5, K = 99999, T = 100, P = 550, Q = 1,
         A = vector<int>({1, 200, 200, 400, 400}),
         B = vector<int>({1000, 1000, 800, 800, 600}),
         C = vector<int>({MAX_C, MAX_C, MAX_C, MAX_C, MAX_C}),
         D = vector<int>({1, 1, 1, 1, 1}));

    // Case 9 - 10: Center Station  (a.k.a Star Graph)
    CASE(N = 1000, M = 5, K = 10, T = 2, P = 999, Q = 8,
         A = vector<int>({1, 1, 1, 1, 1}),
         B = vector<int>({200, 400, 600, 800, 1000}),
         C = vector<int>({9, 9, 9, 9, 9}), D = vector<int>({5, 5, 5, 5, 5}));
    CASE(N = 1000, M = 5, K = 12, T = 2, P = 8, Q = 999,
         A = vector<int>({1, 1, 1, 1, 1}),
         B = vector<int>({200, 400, 600, 800, 1000}),
         C = vector<int>({9, 9, 9, 9, 9}), D = vector<int>({5, 5, 5, 5, 5}));

    // Case 11: Smallest Constraint
    CASE(N = 31, M = 1, K = 2, T = 1, P = 1, Q = 31, A = vector<int>({2}),
         B = vector<int>({29}), C = vector<int>({1}), D = vector<int>({2}));

    // Case 1: Nested Intervals
    result = randomNested(1, MAX_N, 5);
    c = randomFill(5, 8990, 9010);
    CASE(N = MAX_N, M = 5, K = 9000, T = 5, P = randomInt(1, 10000),
         Q = randomInt(MAX_N - 10000, MAX_N), A = result[0], B = result[1],
         C = c, D = randomExpress(result[0], result[1], c, -1, 1));

    // Case 2 - 3: Multi Nested Intervals
    for (int _case = 2; _case <= 3; ++_case) {
      result =
          add({randomNested(1, MAX_N / 2, 2), randomNested(501, MAX_N, 3)});
      c = randomFill(5, 8900, 9100);
      CASE(N = MAX_N, M = 5, K = 9000, T = 1, P = MAX_N - 2, Q = 3,
           A = result[0], B = result[1], C = c,
           D = randomExpress(result[0], result[1], c, -10, 10));
    }

    // Case 4 - 5: Center Station  (a.k.a Star Graph)
    CASE(N = MAX_N, M = 5, K = 10, T = 2, P = MAX_N - 1, Q = 8,
         A = vector<int>({1, 1, 1, 1, 1}),
         B = vector<int>(
             {MAX_N / 5, 2 * MAX_N / 5, 3 * MAX_N / 5, 4 * MAX_N / 5, MAX_N}),
         C = vector<int>({9, 9, 9, 9, 9}), D = vector<int>({5, 5, 5, 5, 5}));
    CASE(N = MAX_N, M = 5, K = 12, T = 2, P = 8, Q = MAX_N - 1,
         A = vector<int>({1, 1, 1, 1, 1}),
         B = vector<int>(
             {MAX_N / 5, 2 * MAX_N / 5, 3 * MAX_N / 5, 4 * MAX_N / 5, MAX_N}),
         C = vector<int>({9, 9, 9, 9, 9}), D = vector<int>({5, 5, 5, 5, 5}));

    // Case 6: Public Transportation -> Express -> Public Transportation
    CASE(N = MAX_N, M = 5, K = 77, T = 1098, P = 25, Q = 5,
         A = randomFill(5, 1, 1), B = randomFill(5, 30, 30),
         C = randomFill(5, 47, MAX_C, {47}), D = randomFill(5, 1, MAX_D, {1}));

    // Case 7: Commuter -> Express -> Commuter
    CASE(N = MAX_N, M = 5, K = 100, T = 1098, P = MAX_N - 75, Q = 5,
         A = randomFill(5, 1, 1), B = randomFill(5, MAX_N - 1, MAX_N - 1),
         C = randomFill(5, 47, MAX_C, {47}),
         D = randomFill(5, 42069, MAX_D, {42069}));

    // Case 8: Smallest Constraint
    CASE(N = 1001, M = 1, K = 2, T = 1, P = 1, Q = 1001, A = vector<int>({69}),
         B = vector<int>({420}), C = vector<int>({1}), D = vector<int>({1}));
  }

  void TestGroup10() {
    int n, m, p, q;
    vector<int> a, b, c, d;
    vector<vector<int>> result;
    vector<vector<vector<int>>> to_add;
    Subtasks({5, 6});

    // Case 11: Incorrect Implementation of Dijkstra
    int x = 42069;
    result = incorrectDijkstraTLE(x);
    CASE(N = 2 * x + 3, M = 4 * x, K = 2 * x, T = 0, P = 2 * x + 1,
         Q = 2 * x + 3, A = result[0], B = result[1], C = result[2],
         D = result[3]);

    // Case 1: Nested Intervals
    result = randomNested(1, MAX_N, 5000);
    c = randomFill(5000, 8990, 9010);
    CASE(N = MAX_N, M = 5000, K = 9000, T = 0, P = randomInt(1, 10000),
         Q = randomInt(MAX_N - 10000, MAX_N), A = result[0], B = result[1],
         C = c, D = randomExpress(result[0], result[1], c, -1, 1));

    // Case 2: Multi Nested Intervals
    for (int i = 0; i < 10; ++i) {
      to_add.push_back(
          randomNested(i * (MAX_N / 10) + 1, (i + 1) * (MAX_N / 10), 500));
    }
    result = add(to_add);
    c = randomFill(5000, 8900, 9100);
    CASE(N = MAX_N, M = 5000, K = 9000, T = 0, P = MAX_N - 2, Q = 3,
         A = result[0], B = result[1], C = c,
         D = randomExpress(result[0], result[1], c, -10, 10));

    // Case 3: Alternate between {Public Transportation, Commuter}
    result = randomAlternate(MAX_N, MAX_N / 4, 2000, 3000, 0, 0);
    CASE(N = MAX_N, M = MAX_N / 4, K = 2500, T = 0, P = MAX_N, Q = 1,
         A = result[0], B = result[1], C = result[2], D = result[3]);

    // Case 4: Alternate between {Public Transportation, Express}
    result = randomAlternate(MAX_N, MAX_N / 8, 2500, 2500, -5, 0);
    CASE(N = MAX_N, M = MAX_N / 8, K = 2500, T = 0, P = MAX_N, Q = 1,
         A = result[0], B = result[1], C = result[2], D = result[3]);

    // Case 5: Alternate between {Public Transportation, Commuter / Express}
    result = randomAlternate(MAX_N, MAX_N / 8, 2499, 2501, -1000, 1000);
    CASE(N = MAX_N, M = MAX_N / 8, K = 2500, T = 0, P = MAX_N, Q = 1,
         A = result[0], B = result[1], C = result[2], D = result[3]);

    // Case 6: All Expresses
    n = randomInt(MAX_N / 2, MAX_N / 2 + 10000);
    m = randomInt(n + 1, MAX_M);
    result = generateConnectedGraph(n, m);
    c = randomFill(m, MAX_C / 2, MAX_C);
    d = randomFill(m, MAX_C / 2, MAX_C);
    tie(p, q) = chooseExpressPQ(n, result[0], result[1]);
    CASE(N = n, M = m, K = MAX_K, T = 0, P = p, Q = q, A = result[0],
         B = result[1], C = c, D = d);

    // Case 7 - 8: All Expresses (Tree Graph)
    n = randomInt(MAX_N / 2, MAX_N / 2 + 10000);
    m = randomInt(n - 1, n - 1);
    result = generateConnectedGraph(n, m);
    c = randomFill(m, MAX_C / 2, MAX_C);
    d = randomFill(m, MAX_C / 2, MAX_C);
    tie(p, q) = chooseExpressPQ(n, result[0], result[1]);
    CASE(N = n, M = m, K = MAX_K, T = 0, P = p, Q = q, A = result[0],
         B = result[1], C = c, D = d);

    n = MAX_N - 69;
    m = randomInt(n - 1, n - 1);
    result = generateConnectedGraph(n, m);
    c = randomFill(m, MAX_C / 2, MAX_C);
    d = randomFill(m, MAX_C / 2, MAX_C);
    tie(p, q) = chooseExpressPQ(n, result[0], result[1]);
    CASE(N = n, M = m, K = MAX_K, T = 0, P = p, Q = q, A = result[0],
         B = result[1], C = c, D = d);

    // Case 9: All Expresses (Almost Fully Connected Graph)
    n = randomInt(300, 300);
    m = randomInt(20000, 35000);
    result = generateConnectedGraph(n, m);
    c = randomFill(m, MAX_C / 2, MAX_C);
    d = randomFill(m, MAX_C / 2, MAX_C);
    tie(p, q) = chooseExpressPQ(n, result[0], result[1]);
    CASE(N = n, M = m, K = MAX_K, T = 0, P = p, Q = q, A = result[0],
         B = result[1], C = c, D = d);

    // Case 10: Smallest Constraint
    CASE(N = 1001, M = 6, K = 1, T = 0, P = 1, Q = 1001,
         A = vector<int>({1, 80, 100, 400, 700, 760}),
         B = vector<int>({69, 81, 200, 800, 760, 1001}),
         C = vector<int>({1, 1, 1, 1, 1, 1}),
         D = vector<int>({2, 2, 2, 2, 2, 2}));
  }

  void TestGroup11() {
    int n, m, p, q;
    vector<int> a, b, c, d;
    vector<vector<int>> result;
    vector<vector<vector<int>>> to_add;
    Subtasks({6});

    // Case 11: Incorrect Implementation of Dijkstra
    int x = 7;
    result = incorrectDijkstraTLE(x);
    CASE(N = 2 * x + 3, M = 4 * x, K = 2 * x, T = 2024, P = 2 * x + 1,
         Q = 2 * x + 3, A = result[0], B = result[1], C = result[2],
         D = result[3]);

    // Case 10: Incorrect Implementation of Dijkstra
    x = 49998;
    result = incorrectDijkstraTLE(x);
    CASE(N = 2 * x + 3, M = 4 * x, K = 2 * x, T = 2024, P = 2 * x + 1,
         Q = 2 * x + 3, A = result[0], B = result[1], C = result[2],
         D = result[3]);

    // Case 1: Alternate between {Public Transportation, Commuter}
    result = randomAlternate(30, 12, 90, 90, 1, 10);
    CASE(N = 30, M = 12, K = 100, T = 11, P = 30, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 2: Alternate between {Public Transportation, Express}
    result = randomAlternate(30, 12, 85, 95, -6, 0);
    CASE(N = 30, M = 12, K = 100, T = 10, P = 30, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 3: Alternate between {Public Transportation, Commuter / Express}
    result = randomAlternate(30, 12, 85, 95, -10, 5);
    CASE(N = 30, M = 12, K = 100, T = 10, P = 30, Q = 1, A = result[0],
         B = result[1], C = result[2], D = result[3]);

    // Case 4: Nested Intervals
    result = randomNested(1, 30, 10);
    c = randomFill(10, 90, 110);
    CASE(N = 30, M = 10, K = 100, T = 1, P = randomInt(7, 8),
         Q = randomInt(23, 24), A = result[0], B = result[1], C = c,
         D = randomExpress(result[0], result[1], c, -1, 1));

    // Case 5: Multi Nested Intervals
    result = add({randomNested(1, 10, 3), randomNested(15, 30, 5)});
    c = randomFill(8, 90, 110);
    CASE(N = 30, M = 8, K = 100, T = 1, P = 28, Q = 3, A = result[0],
         B = result[1], C = c,
         D = randomExpress(result[0], result[1], c, -1, 1));

    // Case 6 - 7: Connected End
    for (int _case = 6; _case <= 7; ++_case) {
      result =
          add({randomNested(1, 10, 4), randomNested(21, 30, 4), {{1}, {30}}});
      c = vector<int>({50, 30, 50, 30, 50, 30, 50, 30, MAX_C});
      d = vector<int>(
          {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 1});
      CASE(N = 30, M = 9, K = 101, T = 1, P = 10, Q = 21, A = result[0],
           B = result[1], C = c, D = d);
    }

    // Case 8 - 9: All Expresses
    for (int _case = 8; _case <= 9; ++_case) {
      int n = randomInt(20, 25);
      int m = randomInt(n + 1, 30);
      result = generateConnectedGraph(n, m);
      c = randomFill(m, 7000, 10000);
      d = randomFill(m, 100, 200);
      int p, q;
      do {
        p = randomInt(1, n);
        q = randomInt(1, n);
      } while (p == q);
      CASE(N = n, M = m, K = 6969, T = 2024, P = p, Q = q, A = result[0],
           B = result[1], C = c, D = d);
    }

    // Case 10: Smallest Constraint
    CASE(N = 5, M = 6, K = 2, T = 1, P = 1, Q = 5,
         A = vector<int>({1, 1, 2, 2, 3, 4}),
         B = vector<int>({3, 4, 3, 4, 5, 5}),
         C = vector<int>({1, 1, 1, 1, 1, 1}),
         D = vector<int>({2, 2, 2, 2, 2, 2}));

    // Case 1: All Expresses
    n = randomInt(MAX_N / 2, MAX_N / 2 + 10000);
    m = randomInt(n + 1, MAX_M);
    result = generateConnectedGraph(n, m);
    c = randomFill(m, MAX_C / 2, MAX_C);
    d = randomFill(m, MAX_C / 2, MAX_C);
    tie(p, q) = chooseExpressPQ(n, result[0], result[1]);
    CASE(N = n, M = m, K = MAX_K, T = randomInt(5000, 10000), P = p, Q = q,
         A = result[0], B = result[1], C = c, D = d);

    // Case 2 - 3: All Expresses (Tree Graph)
    n = randomInt(MAX_N / 2, MAX_N / 2 + 10000);
    m = randomInt(n - 1, n - 1);
    result = generateConnectedGraph(n, m);
    c = randomFill(m, MAX_C / 2, MAX_C);
    d = randomFill(m, MAX_C / 2, MAX_C);
    tie(p, q) = chooseExpressPQ(n, result[0], result[1]);
    CASE(N = n, M = m, K = MAX_K, T = 1, P = p, Q = q, A = result[0],
         B = result[1], C = c, D = d);

    n = MAX_N - 11;
    m = randomInt(n - 1, n - 1);
    result = generateConnectedGraph(n, m);
    c = randomFill(m, MAX_C / 2, MAX_C);
    d = randomFill(m, MAX_C / 2, MAX_C);
    tie(p, q) = chooseExpressPQ(n, result[0], result[1]);
    CASE(N = n, M = m, K = MAX_K, T = 1, P = p, Q = q, A = result[0],
         B = result[1], C = c, D = d);

    // Case 4: All Expresses (Almost Fully Connected Graph)
    n = 300;
    m = randomInt(20000, 35000);
    result = generateConnectedGraph(n, m);
    c = randomFill(m, MAX_C / 2, MAX_C);
    d = randomFill(m, MAX_C / 2, MAX_C);
    tie(p, q) = chooseExpressPQ(n, result[0], result[1]);
    CASE(N = n, M = m, K = MAX_K, T = 69, P = p, Q = q, A = result[0],
         B = result[1], C = c, D = d);

    // Case 5 - 6: Multi Nested Intervals (No Express)
    for (int i = 0; i < 10; ++i) {
      to_add.push_back(
          randomNested(i * (MAX_N / 10) + 1, (i + 1) * (MAX_N / 10), 500));
    }
    result = add(to_add);
    c = randomFill(5000, 8900, 9100);
    CASE(N = MAX_N, M = 5000, K = 9000, T = 1, P = MAX_N - 2, Q = 3,
         A = result[0], B = result[1], C = c,
         D = randomExpress(result[0], result[1], c, 1, 1));

    set<int> points;
    vector<int> points_v;
    while (points.size() < 9) {
      points.insert(randomInt(2, MAX_N - 1));
    }
    points_v.push_back(1);
    for (auto pt : points) {
      points_v.push_back(pt);
    }
    points_v.push_back(MAX_N);
    to_add.clear();
    m = 0;
    for (int i = 0; i < 10; ++i) {
      m += (int)(points_v[1] - points_v[0]) / 25;
      to_add.push_back(randomNested(points_v[0], points_v[1],
                                    (int)(points_v[1] - points_v[0]) / 25));
    }
    result = add(to_add);
    c = randomFill(m, 8900, 9030);
    CASE(N = MAX_N, M = m, K = 9000, T = 69, P = MAX_N, Q = 1, A = result[0],
         B = result[1], C = c,
         D = randomExpress(result[0], result[1], c, 1, 1));

    // Case 7: Alternate between {Public Transportation (->), Express, Public
    // Transportation (<-)}
    b.clear();
    for (int i = 20; i <= MAX_N; i += 20) {
      b.push_back(i);
    }
    a.clear();
    for (auto e : b) {
      a.push_back(e - 2);
    }
    CASE(N = MAX_N, M = b.size(), K = MAX_K - 1, T = 69, P = MAX_N - 3, Q = 1,
         A = a, B = b, C = randomFill(b.size(), MAX_C, MAX_C),
         D = randomFill(b.size(), 1, 1000));

    // Case 8: Alternate between {Express (<-), Express (->)}
    vector<int> br = b;
    a.clear();
    b.clear();
    int l = 0;
    int r = (int)br.size() - 1;
    while (l < r) {
      a.push_back(br[l]);
      b.push_back(br[r]);
      if (l + r % 2 == 0) {
        l++;
      } else {
        r--;
      }
    }
    CASE(N = MAX_N, M = b.size(), K = MAX_K - 1, T = 69, P = 42069, Q = 1,
         A = a, B = b, C = randomFill(b.size(), MAX_C, MAX_C),
         D = randomFill(b.size(), 1000000, 1000000));

    // Case 9: Smallest Constraint
    CASE(N = 1001, M = 6, K = 2, T = 1, P = 1, Q = 1001,
         A = vector<int>({1, 80, 100, 400, 690, 780}),
         B = vector<int>({69, 81, 200, 800, 900, 1001}),
         C = vector<int>({1, 1, 1, 1, 1, 1}),
         D = vector<int>({2, 2, 2, 2, 2, 2}));
  }

private:
  void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
    return;
  }

  int randomInt(int lo, int hi) { return rnd.nextInt(lo, hi); }

  vector<int> randomFill(int sz, int lo, int hi,
                         vector<int> must_include = {}) {
    vector<int> &ret = must_include;
    while ((int)ret.size() < sz) {
      ret.push_back(randomInt(lo, hi));
    }
    rnd.shuffle(ret.begin(), ret.end());
    return ret;
  }

  vector<int> randomSubtask2(int n, int t = -1) {
    int K, T, C, D, P, Q;

    if (t != -1) {
      T = t;
    } else {
      T = randomInt(0, 100000);
    }

    K = randomInt(1, 100000);
    P = randomInt(1, n);
    do {
      Q = randomInt(1, n);
    } while (Q == P);
    C = randomInt(1, 100000);
    D = randomInt(1, 1000000);

    if (P > Q)
      swap(P, Q);

    vector<pair<long long, int>> calc;

    calc.push_back({(long long)K * (Q - P), 1});
    calc.push_back({(long long)T + C * (Q - P), 2});
    calc.push_back({(long long)K * (P - 1) + T + D + K * (n - Q), 3});
    calc.push_back({(long long)T + C * (P - 1) + D + C * (n - Q), 4});
    sort(calc.begin(), calc.end());

    if (randomInt(1, 100) <= 50)
      swap(P, Q);

    vector<int> result = {calc[0].second, K, T, P, Q, C, D};
    return result;
  }

  void synchronizeShuffle(vector<int> &A, vector<int> &B) {
    vector<int> indices(A.size());
    iota(indices.begin(), indices.end(), 0);
    rnd.shuffle(indices.begin(), indices.end());

    vector<int> shuffledA(A.size());
    vector<int> shuffledB(B.size());
    for (size_t i = 0; i < indices.size(); ++i) {
      shuffledA[i] = A[indices[i]];
      shuffledB[i] = B[indices[i]];
    }

    A = move(shuffledA);
    B = move(shuffledB);
  }

  pair<int, int> chooseExpressPQ(int n, vector<int> &A, vector<int> &B) {
    unordered_map<int, vector<int>> graph;
    for (size_t i = 0; i < A.size(); ++i) {
      graph[A[i]].push_back(B[i]);
      graph[B[i]].push_back(A[i]);
    }

    int p = randomInt(1, n);

    unordered_set<int> visited;
    queue<int> q;
    q.push(p);
    visited.insert(p);

    int lastNode = (p % n) + 1;

    while (!q.empty()) {
      int current = q.front();
      q.pop();
      if (current != p)
        lastNode = current;

      for (int neighbor : graph[current]) {
        if (visited.find(neighbor) == visited.end()) {
          visited.insert(neighbor);
          q.push(neighbor);
        }
      }
    }

    if (randomInt(1, 100) <= 50)
      swap(p, lastNode);

    return {p, lastNode};
  }

  vector<vector<int>> add(vector<vector<vector<int>>> v) {
    int sz = (int)v[0].size();
    for (auto vv : v) {
      assert(sz == (int)vv.size());
    }

    vector<vector<int>> result;
    for (int i = 0; i < sz; ++i) {
      vector<int> res;
      for (int j = 0; j < v.size(); ++j) {
        for (auto e : v[j][i]) {
          res.push_back(e);
        }
      }
      result.push_back(res);
    }

    return result;
  }

  vector<int> randomExpress(vector<int> A, vector<int> B, vector<int> C,
                            int d_1, int d_2) {
    assert(A.size() == B.size() && B.size() == C.size());

    vector<int> D;
    for (int i = 0; i < A.size(); ++i) {
      D.push_back(C[i] * (B[i] - A[i]) + d_1 + randomInt(0, d_2 - d_1));
    }

    return D;
  }

  vector<vector<int>> randomAlternate(int n, int m, int c_1, int c_2, int d_1,
                                      int d_2) {
    assert(n >= 2 * m);

    set<int> points;
    while ((int)points.size() < 2 * m) {
      points.insert(randomInt(1, n));
    }

    vector<int> A, B, C, D;
    for (auto point : points) {
      if (A.size() <= B.size()) {
        A.push_back(point);
      } else {
        B.push_back(point);
      }
    }

    synchronizeShuffle(A, B);

    for (int i = 0; i < m; ++i) {
      C.push_back(randomInt(c_1, c_2));
    }

    D = randomExpress(A, B, C, d_1, d_2);

    vector<vector<int>> result = {A, B, C, D};

    return result;
  }

  vector<vector<int>> randomNested(int ll, int rr, int m) {
    assert(rr - ll + 1 >= 2 * m);

    set<int> points_set;
    while (points_set.size() < 2 * m) {
      points_set.insert(randomInt(ll, rr));
    }

    vector<int> points(points_set.begin(), points_set.end());
    sort(points.begin(), points.end());

    vector<int> A, B;
    for (int i = 0; i < m; ++i) {
      A.push_back(points[i]);
      B.push_back(points[2 * m - 1 - i]);
    }

    synchronizeShuffle(A, B);

    return {A, B};
  }

  vector<vector<int>> generateConnectedGraph(int n, int m) {
    assert(m >= n - 1);

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int u) {
      if (u != parent[u])
        parent[u] = find(parent[u]);
      return parent[u];
    };

    set<pair<int, int>> st;
    vector<int> A, B;

    for (int i = 0; i < m; ++i) {
      int a, b;
      if (i < n - 1) {
        do {
          a = randomInt(1, n);
          b = randomInt(1, n);
          if (a > b)
            swap(a, b);
        } while (a == b || find(a) == find(b));
      } else {
        do {
          a = randomInt(1, n);
          b = randomInt(1, n);
          if (a > b)
            swap(a, b);
        } while (a == b || st.find({a, b}) != st.end());
      }

      A.push_back(a);
      B.push_back(b);
      parent[find(a)] = find(b);
      st.insert({a, b});
    }

    return {A, B};
  }

  vector<vector<int>> incorrectDijkstraTLE(int x) {
    assert(2 * x + 3 <= MAX_N);
    assert(4 * x <= MAX_M);

    vector<int> A, B, C, D;
    for (int i = 1; i <= x; ++i) {
      A.push_back(i);
      B.push_back(2 * x + 1);
      C.push_back(2 * x);
      D.push_back(i);

      A.push_back(i);
      B.push_back(2 * x + 2);
      C.push_back(2 * x);
      D.push_back(2 * x - (2 * i - 1));

      A.push_back(x + i);
      B.push_back(2 * x + 2);
      C.push_back(2 * x);
      D.push_back(2 * x - (2 * i - 1));

      A.push_back(x + i);
      B.push_back(2 * x + 3);
      C.push_back(2 * x);
      D.push_back(i);
    }

    return {A, B, C, D};
  }
};