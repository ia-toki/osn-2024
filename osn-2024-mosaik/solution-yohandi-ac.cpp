#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  vector<string> S(N);
  for (auto &e : S) {
    cin >> e;
  }

  vector<map<char, int>> freq(N + M);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      ++freq[i][S[i][j]];
      ++freq[N + j][S[i][j]];
    }
  }

  function<char(int)> check = [&](int index) {
    int cmp = (index < N ? M : N);
    if (freq[index]['.'] > 0 && freq[index]['.'] + freq[index]['?'] == cmp) {
      return '.';
    } else if (freq[index]['#'] > 0 &&
               freq[index]['#'] + freq[index]['?'] == cmp) {
      return '#';
    } else {
      return '?';
    }
  };

  vector<pair<int, char>> consider;
  for (int index = 0; index < N + M; ++index) {
    if (check(index) != '?') {
      consider.push_back({index, check(index)});
    }
  }

  vector<bool> painted(N + M, false);
  vector<pair<int, char>> ans;
  while (!consider.empty()) {
    pair<int, char> p = consider.back();
    consider.pop_back();

    if (painted[p.first]) {
      continue;
    }
    painted[p.first] = true;

    ans.push_back(p);

    if (p.first < N) {
      for (int j = 0; j < M; ++j) {
        freq[p.first][S[p.first][j]]--;
        freq[N + j][S[p.first][j]]--;

        S[p.first][j] = '?';

        freq[p.first][S[p.first][j]]++;
        freq[N + j][S[p.first][j]]++;

        if (check(N + j) != '?') {
          consider.push_back({N + j, check(N + j)});
        }
      }
    } else {
      for (int i = 0; i < N; ++i) {
        freq[i][S[i][p.first - N]]--;
        freq[p.first][S[i][p.first - N]]--;

        S[i][p.first - N] = '?';

        freq[i][S[i][p.first - N]]++;
        freq[p.first][S[i][p.first - N]]++;

        if (check(i) != '?') {
          consider.push_back({i, check(i)});
        }
      }
    }
  }

  reverse(ans.begin(), ans.end());

  cout << (int)ans.size() << endl;
  for (auto p : ans) {
    cout << (p.first < N ? "BARIS" : "KOLOM") << " "
         << (p.first < N ? p.first + 1 : p.first - N + 1) << " " << p.second
         << endl;
  }

  return 0;
}