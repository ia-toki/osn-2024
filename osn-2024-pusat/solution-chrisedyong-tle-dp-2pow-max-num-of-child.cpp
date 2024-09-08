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
long long dp[mxN + 1][2];

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

void dfs(int cur) {
    if (g[cur].empty()) {
        dp[cur][0] = -W[cur];
        dp[cur][1] = W[cur];
    } else {
        for (auto i : g[cur]) {
            dfs(i);
        }
        dp[cur][0] = -1e18;
        dp[cur][1] = -1e18;
        for (unsigned long long i = 0; i < (1ULL << min((int) g[cur].size(), 63)); i++) { // di minimum kan dengan 63 karena overflow
            if (__builtin_popcount(i) == D[cur]) {
                long long newDP[2] = {-W[cur], W[cur]};
                for (int j = 0; j < g[cur].size(); j++) {
                    if ((i >> j) & 1) {
                        newDP[0] += dp[g[cur][j]][1];
                        newDP[1] += dp[g[cur][j]][0];
                    } else {
                        newDP[0] += dp[g[cur][j]][0];
                        newDP[1] += dp[g[cur][j]][1];
                    }
                }
                dp[cur][0] = max(dp[cur][0], newDP[0]);
                dp[cur][1] = max(dp[cur][1], newDP[1]);
            }
        }
    }
}

void solution_TLE() {
    dfs(0);
    ans = max(dp[0][0], dp[0][1]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    read();
    solution_TLE();

    return 0;
}
