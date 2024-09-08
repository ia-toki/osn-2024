#include <bits/stdc++.h>
using namespace std;

struct Train {
  int from, to;
  long long commuter_cost, express_cost;
  auto operator<=>(const Train &) const = default;
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
                long long &T, int &P,
                int &Q) { // O((N + M) log N + M log M)
  assert((int)trains.size() == M);

  const long long INF = 10000000000;
  vector<pair<int, long long>> edges[N + 1];

  // Public Transportation
  trains.push_back({1, N, K, K * (N - 1)});

  // Commuter
  vector<int> refer(N + 1);
  vector<long long> cheapest(N + 1, INF);
  iota(refer.begin(), refer.end(), 0);
  sort(trains.begin(), trains.end(), [](const Train &a, const Train &b) {
    return a.commuter_cost < b.commuter_cost;
  });
  function<int(int)> next = [&](int x) -> int {
    if (refer[x] != x) {
      refer[x] = next(refer[x]);
    }
    return refer[x];
  };
  for (auto [from, to, commuter_cost, express_cost] : trains) {
    for (int station = next(from); station + 1 <= to; station = next(station)) {
      cheapest[station] = commuter_cost;
      if (refer[station] == station) {
        refer[station] = next(station + 1);
      }
    }
  }
  for (int station = 1; station + 1 <= N; ++station) {
    edges[station].push_back({station + 1, cheapest[station]});
    edges[station + 1].push_back({station, cheapest[station]});
  }

  // Express
  for (auto [from, to, commuter_cost, express_cost] : trains) {
    edges[from].push_back({to, express_cost});
    edges[to].push_back({from, express_cost});
  }

  vector<long long> dist(N + 1, INF);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>>
      costs;

  dist[P] = 0;
  costs.push({0, P});
  while (!costs.empty()) {
    long long cost = costs.top().first;
    int node = costs.top().second;
    costs.pop();

    if (cost <= dist[node]) {
      for (auto [next_node, move_cost] : edges[node]) {
        if (dist[next_node] > dist[node] + move_cost) {
          dist[next_node] = dist[node] + move_cost;
          costs.push({dist[next_node], next_node});
        }
      }
    }
  }

  return dist[Q];
}