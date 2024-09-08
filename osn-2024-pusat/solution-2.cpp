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

void dfs(int cur, int col) {
    if (col) ans += W[cur];
    else ans -= W[cur];
    for (auto &i : g[cur]) {
        dfs(i, col ^ (D[cur] != 0));
    }
}

// subtask 2: D[i] = 0 atau D[i] = deg[i]; deg[i] = banyak child node i
void solution_2() {
    ans = 0;
    dfs(0, 0);
    ans = abs(ans);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    read();
    solution_2();

    return 0;
}
