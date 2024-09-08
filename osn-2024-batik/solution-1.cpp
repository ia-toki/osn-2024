#include <bits/stdc++.h>

using namespace std;

const int MXN = 500, MXM = 500;

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
		}
	}
	
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
			swap(A[R1][C1], A[R2][C2]);
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
				}
			}
		}
		else
		{
			int R1, C1, R2, C2;
			scanf("%d%d%d%d", &R1, &C1, &R2, &C2);
			
			bitset<MXN * MXM + 69> isIn;
			for(int i = R1; i <= R2; i++)
			{
				for(int j = C1; j <= C2; j++)
				{
					isIn[A[i][j]] = true;
				}
			}
			
			int ans = 0;
			while(ans < N * M && isIn[ans])
			{
				ans++;
			}
			if(ans == N * M)
			{
				ans = -1;
			}
			printf("%d\n", ans);
		}
	}
}
