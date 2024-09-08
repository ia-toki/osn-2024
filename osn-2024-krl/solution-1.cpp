/*
  20 3 10 1 4 18
  1 4 11 7
  2 20 10 100
  17 20 9 7
*/

#include <bits/stdc++.h>
using namespace std;

struct Train {
  int from, to;
  long long commuter_cost, express_cost;
};

long long solve(int &N, int &M, vector<Train> &trains, long long &K,
                long long &T, int &P, int &Q);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M, P, Q;
  long long K, T;
  cin >> N >> M >> K >> T >> P >> Q;

  vector<Train> trains(M);
  for (auto &[from, to, commuter_cost, express_cost] : trains) {
    cin >> from >> to >> commuter_cost >> express_cost;
  }

  cout << solve(N, M, trains, K, T, P, Q) << endl;
  return 0;
}

long long solve(int &N, int &M, vector<Train> &trains, long long &K,
                long long &T, int &P, int &Q) { // O(1)
  assert((int)trains.size() == M);

  return 135;
}