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
        long long cnt = max(dp[g[cur][0]][0] + dp[g[cur][1]][1], dp[g[cur][0]][1] + dp[g[cur][1]][0]);
        dp[cur][0] = -W[cur] + cnt;
        dp[cur][1] = W[cur] + cnt;
    }
}

void solution_6() {
    dfs(0);
    ans = max(dp[0][0], dp[0][1]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    read();
    solution_6();

    return 0;
}
