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
                int &Q) { // O(MN^2 log N)
  assert((int)trains.size() == M);

  const long long INF = 10000000000;
  vector<pair<int, long long>> edges[N + 1];

  // Public Transportation
  for (int station_from = 1; station_from <= N; ++station_from) {
    for (int station_to = 1; station_to <= N; ++station_to) {
      long long move_cost = K * abs(station_to - station_from);
      edges[station_from].push_back({station_to, move_cost});
    }
  }

  for (auto [from, to, commuter_cost, express_cost] : trains) {
    // Express
    edges[from].push_back({to, express_cost});
    edges[to].push_back({from, express_cost});

    // Commuter
    for (int station_from = from; station_from <= to; ++station_from) {
      for (int station_to = from; station_to <= to; ++station_to) {
        long long move_cost = commuter_cost * abs(station_to - station_from);
        edges[station_from].push_back({station_to, move_cost});
        edges[station_to].push_back({station_from, move_cost});
      }
    }
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