#include <bits/stdc++.h>
using namespace std;

// constant variable
constexpr int mxN = 100'000;

// input variable
int N;
int P[mxN + 1];
int W[mxN + 1];
int D[mxN + 1];

// global variable
vector<int> g[mxN + 1];

// output variable
long long ans;

void read() {
    cin >> N;
    for (int i = 1; i < N; i++) {
        cin >> P[i];
        --P[i];
        g[P[i]].emplace_back(i);
    }
    for (int i = 0; i < N; i++) {
        cin >> W[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> D[i];
    }
}

unsigned long long col;
bool ok;
void dfs(int cur) {
    int colCur = (col >> cur) & 1;
    int cnt = 0;
    for (auto i : g[cur]) {
        cnt += (((col >> i) & 1) ^ colCur);
        dfs(i);
    }
    if (cnt != D[cur]) {
        ok = false;
    }
}

// solution ini melakukan bruteforce 2^n
// mencoba semua kombinasi warna hitam dan putih
void solution_TLE() {
    ans = 0;
    for (col = 0; col < (1ULL << min(N, 63)); col++) { // di minimum kan dengan 63 karena overflow
        ok = true;
        dfs(0);
        if (ok) {
            long long newans = 0;
            for (int j = 0; j < N; j++) {
                if ((col >> j) & 1) {
                    newans += W[j];
                } else {
                    newans -= W[j];
                }
            }
            if (abs(newans) > ans) {
                ans = abs(newans);
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    read();
    solution_TLE();

    return 0;
}
