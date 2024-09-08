#include <bits/stdc++.h>

using namespace std;

const int MXN = 500, MXM = 500;

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	
	int A[N + 69][M + 69];
	set<int> outside;
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++)
		{
			scanf("%d", &A[i][j]);
			if(i > (N + 1) / 2)
			{
				outside.insert(A[i][j]);
			}
		}
	}
	
	int Q, offset = 0;
	scanf("%d", &Q);
	for(int rr = 0; rr < Q; rr++)
	{
		int type;
		scanf("%d", &type);
		if(type == 1)
		{
			int R1, C1, R2, C2;
			scanf("%d%d%d%d", &R1, &C1, &R2, &C2);
			if(R1 > (N + 1) / 2)
			{
				outside.erase(A[R1][C1]);
			}
			if(R2 > (N + 1) / 2)
			{
				outside.erase(A[R2][C2]);
			}
			swap(A[R1][C1], A[R2][C2]);
			if(R1 > (N + 1) / 2)
			{
				outside.insert(A[R1][C1]);
			}
			if(R2 > (N + 1) / 2)
			{
				outside.insert(A[R2][C2]);
			}
		}
		else if(type == 2)
		{
			int W;
			scanf("%d", &W);
			offset = (offset + N * M - W) % (N * M);
		}
		else
		{
			int R1, C1, R2, C2;
			scanf("%d%d%d%d", &R1, &C1, &R2, &C2);
			
			if(outside.empty())
			{
				printf("-1\n");
			}
			else
			{
				set<int>::iterator it = outside.lower_bound(offset);
				if(it == outside.end())
				{
					it = outside.begin();
				}
				
				printf("%d\n", (*it + (N * M) - offset) % (N * M));
			}
		}
	}
}
