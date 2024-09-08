#include <bits/stdc++.h>
using namespace std;

constexpr int mxN = 500;
constexpr int mxNM = 250'000;

int N, M, Q, NM;
int A[mxN + 1][mxN + 1];
int R[mxNM + 1], C[mxNM + 1];

struct node {
    int minR, maxR, minC, maxC;
    node() {}
    node (int _minR, int _maxR, int _minC, int _maxC) {
        minR = _minR;
        maxR = _maxR;
        minC = _minC;
        maxC = _maxC;
    }
} segtree[8 * mxNM];

node merge(node x, node y) {
    return node(min(x.minR, y.minR), max(x.maxR, y.maxR), min(x.minC, y.minC), max(x.maxC, y.maxC));
}

void build(int pos = 0, int l = 0, int r = (NM << 1) - 1) {
    if (l == r) {
        segtree[pos] = node(R[l % NM], R[l % NM], C[l % NM], C[l % NM]);
        return;
    }
    int lc = (pos << 1) + 1, rc = (pos << 1) + 2, m = l + (r - l) / 2;
    build(lc, l, m);
    build(rc, m + 1, r);
    segtree[pos] = merge(segtree[lc], segtree[rc]);
}

void upd(int id, int pos = 0, int l = 0, int r = (NM << 1) - 1) {
    if (l == r) {
        segtree[pos] = node(R[l % NM], R[l % NM], C[l % NM], C[l % NM]);
        return;
    }
    int lc = (pos << 1) + 1, rc = (pos << 1) + 2, m = l + (r - l) / 2;
    if (l <= id && id <= m) {
        upd(id, lc, l, m);
    } else {
        upd(id, rc, m + 1, r);
    }
    segtree[pos] = merge(segtree[lc], segtree[rc]);
}

node qry(int ql, int qr, int pos = 0, int l = 0, int r = (NM << 1) - 1) {
    if (ql <= l && r <= qr) {
        return segtree[pos];
    }
    if (r < ql || qr < l) {
        return node(NM, -1, NM, -1);
    }
    int lc = (pos << 1) + 1, rc = (pos << 1) + 2, m = l + (r - l) / 2;
    return merge(qry(ql, qr, lc, l, m), qry(ql, qr, rc, m + 1, r));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> A[i][j];
            R[A[i][j]] = i;
            C[A[i][j]] = j;
        }
    }

    NM = N * M;
    build();
    int shift = 0;

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            --r1; --c1; --r2; --c2;

            swap(R[A[r1][c1]], R[A[r2][c2]]);
            swap(C[A[r1][c1]], C[A[r2][c2]]);
            swap(A[r1][c1], A[r2][c2]);

            upd(A[r1][c1]); upd(A[r1][c1] + NM);
            upd(A[r2][c2]); upd(A[r2][c2] + NM);
        } else if (t == 2) {
            int w;
            cin >> w;
            shift = (shift + NM - w) % NM;
        } else {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            --r1; --c1; --r2; --c2;

            if (r1 == 0 && r2 == N - 1 && c1 == 0 && c2 == M - 1) {
                cout << "-1\n";
                continue;
            }

            int lo = 0, hi = NM, ans = 0;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                node cur = qry(shift, shift + mid);
                if (r1 <= cur.minR && cur.maxR <= r2 && c1 <= cur.minC && cur.maxC <= c2) {
                    lo = ans = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }

            cout << ans << '\n';
        }
    }

    return 0;
}
