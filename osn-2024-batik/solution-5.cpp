#include <bits/stdc++.h>

using namespace std;

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	
	int A[N + 69][M + 69], pos[N * M + 69][2];
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++)
		{
			scanf("%d", &A[i][j]);
			pos[A[i][j]][0] = i;
			pos[A[i][j]][1] = j;
		}
	}
	
	int prefMin[N * M + 69][2], prefMax[N * M + 69][2];
	for(int i = 0; i < N * M; i++)
	{
		for(int ii = 0; ii < 2; ii++)
		{
			prefMin[i][ii] = pos[i][ii];
			prefMax[i][ii] = pos[i][ii];
			if(i > 0)
			{
				prefMin[i][ii] = min(prefMin[i][ii], prefMin[i - 1][ii]);
				prefMax[i][ii] = max(prefMax[i][ii], prefMax[i - 1][ii]);
			}
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
			
			for(int i = 1; i <= N; i++)
			{
				for(int j = 1; j <= M; j++)
				{
					pos[A[i][j]][0] = i;
					pos[A[i][j]][1] = j;
				}
			}
			
			for(int i = 0; i < N * M; i++)
			{
				for(int ii = 0; ii < 2; ii++)
				{
					prefMin[i][ii] = pos[i][ii];
					prefMax[i][ii] = pos[i][ii];
					if(i > 0)
					{
						prefMin[i][ii] = min(prefMin[i][ii], prefMin[i - 1][ii]);
						prefMax[i][ii] = max(prefMax[i][ii], prefMax[i - 1][ii]);
					}
				}
			}
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
			
			for(int i = 0; i < N * M; i++)
			{
				for(int ii = 0; ii < 2; ii++)
				{
					prefMin[i][ii] = pos[i][ii];
					prefMax[i][ii] = pos[i][ii];
					if(i > 0)
					{
						prefMin[i][ii] = min(prefMin[i][ii], prefMin[i - 1][ii]);
						prefMax[i][ii] = max(prefMax[i][ii], prefMax[i - 1][ii]);
					}
				}
			}
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
				
				if(prefMin[mid][0] < R1 || prefMin[mid][1] < C1 || prefMax[mid][0] > R2 || prefMax[mid][1] > C2)
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
