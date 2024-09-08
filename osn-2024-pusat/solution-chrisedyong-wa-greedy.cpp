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
long long pref[mxN + 1], suff[mxN + 1];

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
    for (auto i : g[cur]) {
        dfs(i);
    }

    dp[cur][0] = -W[cur];
    dp[cur][1] = W[cur];

    // leave: base case
    if (g[cur].size() == 0) {
        return;
    }

    // not leave: transition

    // greedy WA: sort according to weight
    sort(g[cur].begin(), g[cur].end(), [](int a, int b){
        return W[a] < W[b];
    });

    for (int i = 0; i < (int) g[cur].size(); i++) {
        if (i < D[cur]) {
            dp[cur][0] += dp[g[cur][i]][1];
            dp[cur][1] += dp[g[cur][i]][0];
        } else {
            dp[cur][0] += dp[g[cur][i]][0];
            dp[cur][1] += dp[g[cur][i]][1];
        }
    }
}

void solution_WA() {
    dfs(0);
    ans = max(dp[0][0], dp[0][1]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    read();
    solution_WA();

    return 0;
}
