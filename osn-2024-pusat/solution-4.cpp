#include <bits/stdc++.h>
using namespace std;

// constant variable
constexpr int mxN = 100'000;
constexpr int mxN4 = 100;

// input variable
int N;
int P[mxN + 1];
int W[mxN + 1];
int D[mxN + 1];

// global variable
vector<int> g[mxN + 1];
bool dp[mxN4 + 1][2][mxN4 + mxN4 + 1];
// node, color, sum of weight (bisa negative jadi perlu di shift)
int subtree[mxN4 + 1];

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
    subtree[cur] = 1;
    for (auto i : g[cur]) {
        dfs(i);
        subtree[cur] += subtree[i];
    }

    // leave: base case
    if (subtree[cur] == 1) {
        dp[cur][0][mxN4 - W[cur]] = true;
        dp[cur][1][mxN4 + W[cur]] = true;
        return;
    }

    // non-leave: transition
    bool dp2[2][D[cur] + 5][mxN4 + mxN4 + 5];
    // child ke berapa (optimized flying table), berapa elemen yang beda color sejauh ini, sum of weight

    for (int c = 0; c < 2; c++) {
        memset(dp2, false, sizeof(dp2));

        dp2[1][0][mxN4 + (c == 0 ? -1 : 1)] = true;

        for (int i = 0; i < g[cur].size(); i++) {
            // set dp jadi false semua untuk sekarang
            for (int j = 0; j <= D[cur]; j++) {
                for (int k = mxN4 - subtree[cur]; k <= mxN4 + subtree[cur]; k++) {
                    dp2[i & 1][j][k] = false;
                }
            }

            // update dp 
            for (int j = 0; j <= D[cur]; j++) {
                for (int k = mxN4 - subtree[cur]; k <= mxN4 + subtree[cur]; k++) {
                    if (!dp2[1 ^ i & 1][j][k]) continue;
                    for (int l = max(mxN4 - subtree[g[cur][i]], mxN4 - k); l <= mxN4 + subtree[g[cur][i]] && k + l - mxN4 <= mxN4 + mxN4; l++) {
                        dp2[i & 1][j][k + l - mxN4] |= dp[g[cur][i]][c][l];
                        dp2[i & 1][j + 1][k + l - mxN4] |= dp[g[cur][i]][c ^ 1][l];
                    }
                }
            }
        }

        // copy ke dp
        for (int i = mxN4 - subtree[cur]; i <= mxN4 + subtree[cur]; i++) {
            dp[cur][c][i] = dp2[1 ^ g[cur].size() & 1][D[cur]][i];
        }
    }
}

// subtask 4: N <= 100, W[i] = 1
void solution_4() {
    dfs(0);
    ans = 0;
    for (int i = mxN4 - subtree[0]; i <= mxN4 + subtree[0]; i++) {
        if (dp[0][0][i]) ans = max(ans, 1LL * i);
        if (dp[0][1][i]) ans = max(ans, 1LL * i);
    }
    ans -= mxN4;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    read();
    solution_4();

    return 0;
}
