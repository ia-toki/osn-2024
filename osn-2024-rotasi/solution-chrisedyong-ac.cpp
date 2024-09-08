#include <bits/stdc++.h>
using namespace std;

constexpr int mxN = 500'000;

int N, K;
int A[2 * mxN + 5];
bool vis[mxN + 5];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        A[i + N] = A[i];
    }

    int ans = 0;

    deque<int> mini, maxi;
    for (int l = 0, r = 0; l < N; l++) {
        for (; r < 2 * N; r++) {
            if (mini.empty() && maxi.empty()) {
                mini.push_back(r);
                maxi.push_back(r);
                vis[A[r]] = true;
                continue;
            }

            if (vis[A[r]]) {
                break;
            }

            int selisih = max(A[maxi.front()], A[r]) - min(A[mini.front()], A[r]);
            if (selisih > K - 1) {
                break;
            }

            vis[A[r]] = true;

            for (; !mini.empty() && A[mini.back()] > A[r]; mini.pop_back()) ;
            mini.push_back(r);

            for (; !maxi.empty() && A[maxi.back()] < A[r]; maxi.pop_back()) ;
            maxi.push_back(r);
        }
        ans = max(ans, r - l);

        vis[A[l]] = false;
        for (; !mini.empty() && mini.front() <= l; mini.pop_front()) ;
        for (; !maxi.empty() && maxi.front() <= l; maxi.pop_front()) ;
    }

    ans = K - ans;
    cout << ans << '\n';

    return 0;
}
