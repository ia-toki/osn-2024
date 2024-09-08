#include <bits/stdc++.h>

using namespace std;

struct Operation
{
	string type;
	int idx;
	char color;
};

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	
	int S[N + 1][M + 1];
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++)
		{
			char ch;
			scanf(" %c", &ch);
			if(ch == '.')
			{
				S[i][j] = 0;
			}
			else
			{
				S[i][j] = 1;
			}
		}
	}
	
	int freqRow[N + 1][2], freqCol[M + 1][2];
	for(int i = 1; i <= N; i++)
	{
		for(int ii = 0; ii < 2; ii++)
		{
			freqRow[i][ii] = 0;
		}
	}
	for(int i = 1; i <= M; i++)
	{
		for(int ii = 0; ii < 2; ii++)
		{
			freqCol[i][ii] = 0;
		}
	}
	
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++)
		{
			freqRow[i][S[i][j]]++;
			freqCol[j][S[i][j]]++;
		}
	}
	
	bool vis[N + 1][M + 1], visRow[N + 1], visCol[M + 1];
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++)
		{
			vis[i][j] = false;
		}
	}
	for(int i = 1; i <= N; i++)
	{
		visRow[i] = false;
	}
	for(int i = 1; i <= M; i++)
	{
		visCol[i] = false;
	}
	
	queue<Operation> q;
	for(int i = 1; i <= N; i++)
	{
		for(int ii = 0; ii < 2; ii++)
		{
			if(freqRow[i][!ii] == 0 && !visRow[i])
			{
				q.push({"BARIS", i, !ii ? '.' : '#'});
				visRow[i] = true;
			}
		}
	}
	for(int i = 1; i <= M; i++)
	{
		for(int ii = 0; ii < 2; ii++)
		{
			if(freqCol[i][!ii] == 0 && !visCol[i])
			{
				q.push({"KOLOM", i, !ii ? '.' : '#'});
				visCol[i] = true;
			}
		}
	}
	
	vector<Operation> ans;
	while(!q.empty())
	{
		Operation op = q.front();
		q.pop();
		
		ans.push_back(op);
		
		if(op.type == "BARIS")
		{
			for(int i = 1; i <= M; i++)
			{
				if(!vis[op.idx][i])
				{
					int w = S[op.idx][i];
					
					freqRow[op.idx][w]--;
					freqCol[i][w]--;
					if(freqCol[i][w] == 0 && !visCol[i])
					{
						q.push({"KOLOM", i, !!w ? '.' : '#'});
						visCol[i] = true;
					}
				}
			}
		}
		else
		{
			for(int i = 1; i <= N; i++)
			{
				if(!vis[i][op.idx])
				{
					int w = S[i][op.idx];
					
					freqCol[op.idx][w]--;
					freqRow[i][w]--;
					if(freqRow[i][w] == 0 && !visRow[i])
					{
						q.push({"BARIS", i, !!w ? '.' : '#'});
						visRow[i] = true;
					}
				}
			}
		}
	}
	
	reverse(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size());
	for(int i = 0; i < ans.size(); i++)
	{
		Operation op = ans[i];
		printf("%s %d %c\n", op.type.c_str(), op.idx, op.color);
	}
}
