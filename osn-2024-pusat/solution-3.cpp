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

// subtask 3: star graph, greedy yang weight besar-besar atau weight kecil-kecil
void solution_3() {
    long long mini = W[0], maxi = W[0], sum = 0;
    for (int i = 0; i < N; i++) {
        sum += W[i];
    }
    sort(W + 1, W + N);
    for (int i = 1; i <= N - 1 - D[0]; i++) {
        mini += W[i];
    }
    for (int i = N - 1; i >= D[0] + 1; i--) {
        maxi += W[i];
    }
    ans = max(abs(sum - 2LL * mini), abs(sum - 2LL * maxi));
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    read();
    solution_3();

    return 0;
}
