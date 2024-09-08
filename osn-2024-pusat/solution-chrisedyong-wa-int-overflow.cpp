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
int ans;

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

    // leave: base case
    if (g[cur].size() == 0) {
        dp[cur][0] = -W[cur];
        dp[cur][1] = W[cur];
        return;
    }

    // not leave: transition
    sort(g[cur].begin(), g[cur].end(), [](int a, int b){
        return dp[a][1] - dp[a][0] < dp[b][1] - dp[b][0];
    });

    pref[0] = dp[g[cur][0]][0];
    for (int i = 1; i < g[cur].size(); i++) {
        pref[i] = pref[i - 1] + dp[g[cur][i]][0];
    }
    suff[g[cur].size() - 1] = dp[g[cur].back()][1];
    for (int i = g[cur].size() - 2; i >= 0; i--) {
        suff[i] = suff[i + 1] + dp[g[cur][i]][1];
    }

    dp[cur][0] = -W[cur];
    int beda = g[cur].size() - D[cur];
    if (0 <= beda && beda < g[cur].size()) {
        dp[cur][0] += suff[beda];
    }
    if (0 <= beda - 1 && beda - 1 < g[cur].size()) {
        dp[cur][0] += pref[beda - 1];
    }

    beda = D[cur] - 1;
    dp[cur][1] = W[cur];
    if (0 <= beda && beda < g[cur].size()) {
        dp[cur][1] += pref[beda];
    }
    if (0 <= beda + 1 && beda + 1 < g[cur].size()) {
        dp[cur][1] += suff[beda + 1];
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
