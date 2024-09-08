#include <bits/stdc++.h>
using namespace std;

int query(vector<int> &a);
void answer(int z);

int main() {
  int N = 256;
  vector<int> a(N / 2), responses;

  iota(a.begin(), a.end(), 1);
  responses.push_back(query(a));
  iota(a.begin(), a.end(), N / 2 + 1);
  responses.push_back(query(a));
  iota(a.begin(), a.end(), N / 4 + 1);
  responses.push_back(query(a));

  if (responses[0] == 0) {
    if (responses[2] == 0) {
      answer(N / 2 + 1 - responses[1]);
    } else {
      answer(responses[1]);
    }
  } else {
    if (responses[2] == 0) {
      answer(N / 2 + responses[0]);
    } else {
      answer(N + 1 - responses[0]);
    }
  }

  return 0;
}

int query(vector<int> &a) {
  cout << "TANYA " << a.size() << endl;
  for (auto &e : a) {
    cout << e << " ";
  }
  cout << endl;

  int response;
  cin >> response;

  return response;
}

void answer(int z) {
  cout << "JAWAB " << z << endl;

  return;
}