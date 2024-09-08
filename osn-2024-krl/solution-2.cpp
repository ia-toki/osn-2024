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
                long long &T, int &P, int &Q) { // O(M)
  assert((int)trains.size() == M);

  long long min_commuter_cost =
      ranges::min_element(trains, {}, &Train::commuter_cost)->commuter_cost;
  long long min_express_cost =
      ranges::min_element(trains, {}, &Train::express_cost)->express_cost;

  if (P > Q) {
    swap(P, Q);
  }

  return min(
      {K * (Q - P),
       T + min_commuter_cost * (Q - P),
       K * (P - 1) + T + min_express_cost + K * (N - Q),
       T + min_commuter_cost * (P - 1) + min_express_cost + min_commuter_cost * (N - Q)});
}