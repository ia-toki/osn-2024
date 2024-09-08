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
                int &Q) { // O(MN log N)
  assert((int)trains.size() == M);

  const long long INF = 10000000000;
  vector<pair<int, long long>> edges[2 * N + 1];

  // Enter Station
  for (int station = 1; station <= N; ++station) {
    edges[station * 2 - 1].push_back({station * 2, T});
  }

  // Public Transportation
  for (int station = 1; station + 1 <= N; ++station) {
    edges[station * 2 - 1].push_back({(station + 1) * 2 - 1, K});
    edges[station * 2].push_back({(station + 1) * 2 - 1, K});
    edges[(station + 1) * 2 - 1].push_back({station * 2 - 1, K});
    edges[(station + 1) * 2].push_back({station * 2 - 1, K});
  }

  for (auto [from, to, commuter_cost, express_cost] : trains) {
    // Express
    edges[from * 2].push_back({to * 2, express_cost});
    edges[to * 2].push_back({from * 2, express_cost});

    // Commuter
    for (int station = from; station + 1 <= to; ++station) {
      edges[station * 2].push_back({(station + 1) * 2, commuter_cost});
      edges[(station + 1) * 2].push_back({station * 2, commuter_cost});
    }
  }

  vector<long long> dist(2 * N + 1, INF);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>>
      costs;

  dist[P * 2 - 1] = 0;
  costs.push({0, P * 2 - 1});
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

  return min(dist[Q * 2 - 1], dist[Q * 2]);
}