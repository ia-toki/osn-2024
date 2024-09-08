#include <bits/stdc++.h>

using namespace std;

const int MXN = 500, MXM = 500;
const int INF = 1e9;

struct val
{
	int mn[2] = {INF, INF}, mx[2] = {-INF, -INF};
};

inline val mrg(val v1, val v2)
{
	val tmp;
	for(int ii = 0; ii < 2; ii++)
	{
		tmp.mn[ii] = min(v1.mn[ii], v2.mn[ii]);
		tmp.mx[ii] = max(v1.mx[ii], v2.mx[ii]);
	}
	return tmp;
}

int pos[MXN * MXM + 69][2];

struct segtree
{
	int l, r;
	val ans;
	segtree *lef, *rig;
	
	void bld(int lb, int rb)
	{
		l = lb;
		r = rb;
		
		if(l == r)
		{
			for(int ii = 0; ii < 2; ii++)
			{
				ans.mn[ii] = pos[l][ii];
				ans.mx[ii] = pos[l][ii];
			}
		}
		else
		{
			lef = new segtree;
			rig = new segtree;
			
			int mid = (l + r) / 2;
			lef->bld(l, mid);
			rig->bld(mid + 1, r);
			
			ans = mrg(lef->ans, rig->ans);
		}
	}
	
	void upd(int x, int w1, int w2)
	{
		if(x < l || r < x);
		else if(x <= l && r <= x)
		{
			ans.mn[0] = w1;
			ans.mx[0] = w1;
			ans.mn[1] = w2;
			ans.mx[1] = w2;
		}
		else
		{
			lef->upd(x, w1, w2);
			rig->upd(x, w1, w2);
			
			ans = mrg(lef->ans, rig->ans);
		}
	}
	
	val qry(int lb, int rb)
	{
		if(rb < l || r < lb)
		{
			val val0;
			return val0;
		}
		else if(lb <= l && r <= rb)
		{
			return ans;
		}
		else
		{
			return mrg(lef->qry(lb, rb), rig->qry(lb, rb));
		}
	}
};

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	
	int A[N + 69][M + 69];
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++)
		{
			scanf("%d", &A[i][j]);
			pos[A[i][j]][0] = i;
			pos[A[i][j]][1] = j;
		}
	}
	
	segtree seg;
	seg.bld(0, N * M - 1);
	
	int Q;
	scanf("%d", &Q);
	for(int rr = 0; rr < Q; rr++)
	{
		int type;
		scanf("%d", &type);
		if(type == 1)
		{
			int R1, C1, R2, C2;
			scanf("%d%d%d%d", &R1, &C1, &R2, &C2);
			
			int w1, w2;
			w1 = A[R1][C1];
			w2 = A[R2][C2];
			swap(A[R1][C1], A[R2][C2]);
			seg.upd(w1, R2, C2);
			seg.upd(w2, R1, C1);
		}
		else if(type == 2)
		{
			int W;
			scanf("%d", &W);
			
			for(int i = 1; i <= N; i++)
			{
				for(int j = 1; j <= M; j++)
				{
					A[i][j] = (A[i][j] + W) % (N * M);
					pos[A[i][j]][0] = i;
					pos[A[i][j]][1] = j;
				}
			}
			
			seg.bld(0, N * M - 1);
		}
		else
		{
			int R1, C1, R2, C2;
			scanf("%d%d%d%d", &R1, &C1, &R2, &C2);
			
			int lef, rig, ans;
			lef = 0;
			rig = N * M - 1;
			ans = -1;
			while(lef <= rig)
			{
				int mid = (lef + rig) / 2;
				
				val res = seg.qry(0, mid);
				if(res.mn[0] < R1 || res.mn[1] < C1 || res.mx[0] > R2 || res.mx[1] > C2)
				{
					ans = mid;
					rig = mid - 1;
				}
				else
				{
					lef = mid + 1;
				}
			}
			printf("%d\n", ans);
		}
	}
}
