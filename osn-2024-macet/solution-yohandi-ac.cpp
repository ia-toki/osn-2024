#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<pair<int, int>> intervals(N);
  for (auto &p : intervals) {
    cin >> p.first >> p.second;
  }
  sort(intervals.begin(), intervals.end(),
       [&](pair<int, int> p, pair<int, int> q) {
         if (p.second == q.second) {
           return p.first > q.first;
         }
         return p.second < q.second;
       });

  vector<int> L = {intervals[0].first}, R = {intervals[0].second};
  for (int i = 1; i < N; ++i) {
    while (!L.empty() && intervals[i].first <= L.back()) {
      L.pop_back();
      R.pop_back();
    }
    L.push_back(intervals[i].first);
    R.push_back(intervals[i].second);
  }

  int M;
  cin >> M;

  int ans = -1, pL = -1, pR = -1;
  vector<int> A(M);
  for (auto &e : A) {
    cin >> e;

    int qL = lower_bound(R.begin(), R.end(), e) - R.begin();
    int qR = upper_bound(L.begin(), L.end(), e) - L.begin() - 1;

    if (qL > qR) {
      ans = -1;
      break;
    }

    if (qL > pR || pL > qR) {
      ++ans;
      pL = qL;
      pR = qR;
    } else {
      pL = max(pL, qL);
      pR = min(pR, qR);
    }
  }

  cout << ans << endl;

  return 0;
}