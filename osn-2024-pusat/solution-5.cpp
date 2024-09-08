#include <bits/stdc++.h>
using namespace std;

// constant variable
constexpr int mxN = 100'000;
constexpr long long INF = 1e15;

// input variable
int N;
int P[mxN + 1];
int W[mxN + 1];
int D[mxN + 1];

// global variable
vector<int> g[mxN + 1];
int deg[mxN + 1];
long long dp[mxN + 1][2];
long long dp2[mxN + 1];

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

    // leave: base case
    if (deg[cur] == 0) {
        dp[cur][0] = -W[cur];
        dp[cur][1] = W[cur];
        return;
    }

    // not leave: transition
    for (int j = 0; j < 2; j++) {
        dp2[0] = 0;
        for (int i = 1; i <= deg[cur]; i++) {
            dp2[i] = -INF;
        }
        for (int i = 0; i < deg[cur]; i++) {
            for (int k = deg[cur]; k >= 0; k--) {
                dp2[k] = dp2[k] + dp[g[cur][i]][j];
                if (k > 0) {
                    dp2[k] = max(dp2[k], dp2[k - 1] + dp[g[cur][i]][j ^ 1]);
                }
            }
        }
        dp[cur][j] = dp2[D[cur]];
    }
    dp[cur][0] -= W[cur];
    dp[cur][1] += W[cur];
}

// subtask 5: N <= 2000
// dp[cur][j] = max(banyak warna true - banyak warna false) jika warna dari node cur adalah j
//     1 <= i <= N
//     j = true atau false
// dp2[i] = max(banyak warna true - banyak warna false) jika node cur punya i child yang beda warna dengan warna cur
//     transisi dp2 bisa menggunakan transisi knapsack
void solution_5() {
    memset(deg, 0, sizeof(deg));
    for (int i = 1; i < N; i++) {
        deg[P[i]]++;
    }
    dfs(0);
    ans = max(dp[0][0], dp[0][1]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    read();
    solution_5();

    return 0;
}
