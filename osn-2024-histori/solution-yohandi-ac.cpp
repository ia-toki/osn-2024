#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int N;
  cin >> N;

  int youngest = INT_MAX - 1, oldest = -1, ducks = 0;
  double average = 0;

  vector<int> A(N);
  for (auto &e : A) {
    cin >> e;

    ++ducks;

    youngest = min(youngest + 1, e);
    oldest = max(oldest + 1, e);
    average = ((average + 1) * (ducks - 1) + e) / ducks;

    cout << fixed << setprecision(4) << youngest << " " << oldest << " "
         << average << "\n";
  }

  return 0;
}