#include <bits/stdc++.h>

using namespace std;

const int MXN = 23;

int N, M;
bitset<MXN + 69> a[MXN + 69], a2[MXN + 69];

inline void inp()
{
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++)
		{
			char ch;
			scanf(" %c",&ch);
			a[i][j] = ch - '0';
		}
	}
}

inline void accel(int t)
{
	printf("AKSELERASI %d\n", t);
	fflush(stdout);
	
	inp();
}

inline void expmt(int x, int y)
{
	printf("EKSPERIMEN %d %d\n", x, y);
	fflush(stdout);
	
	int z;
	scanf("%d", &z);
	
	a[x][y] = 0;
}

int main()
{
	scanf("%d%d", &N, &M);
	inp();
	
	int jump = 1;
	while(true)
	{
		for(int i = 1; i <= N; i++)
		{
			a2[i] = a[i];
		}
		accel(jump);
		
		for(int i = 1; i <= N; i++)
		{
			for(int j = 1; j <= M; j++)
			{
				if(!a2[i][j])
				{
					int x, y;
					x = (i + jump - 1) % N + 1;
					y = (j + jump - 1) % M + 1;
					
					if(a[x][j])
					{
						expmt(x, j);
					}
					if(a[i][y])
					{
						expmt(i, y);
					}
				}
			}
		}
		
		bool hasMicrobes = false;
		for(int i = 1; i <= N; i++)
		{
			hasMicrobes |= a[i].any();
		}
		if(!hasMicrobes)
		{
			break;
		}
		
		jump *= 2;
	}
}
