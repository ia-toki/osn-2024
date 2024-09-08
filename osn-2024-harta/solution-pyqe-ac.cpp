#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 256;

inline vector<int> rndArray(int sz, int lo, int hi)
{
	vector<int> ret;
	for(int i = 0; i < sz; i++)
	{
		ret.push_back(rand() % (hi - lo + 1) + lo);
	}
	return ret;
}

inline vector<int> nonDecreasingArray(int sz, int lo, int hi)
{
	vector<int> ret = rndArray(sz, lo, hi);
	sort(ret.begin(), ret.end());
	return ret;
}

inline vector<int> increasingArray(int sz, int lo, int hi)
{
	vector<int> ret = nonDecreasingArray(sz, lo, hi - (sz - 1));
	for(int i = 0; i < sz; i++)
	{
		ret[i] += i;
	}
	return ret;
}

inline int qry(vector<int> pos)
{
	int sz = pos.size();
	printf("TANYA %d\n", sz);
	for(int i = 0; i < sz; i++)
	{
		printf("%d", pos[i]);
		if(i < sz - 1)
		{
			printf(" ");
		}
	}
	printf("\n");
	fflush(stdout);
	
	int d;
	scanf("%d", &d);
	return d;
}

int main()
{
	srand(time(NULL));
	
	bitset<N + 69> isValid;
	for(int i = 1; i <= N; i++)
	{
		isValid[i] = true;
	}
	
	int offset = 0;
	while(true)
	{
		vector<int> pos = increasingArray(N / 2, 1, N / 2);
		for(int i = 0; i < pos.size(); i++)
		{
			pos[i] = (pos[i] + offset - 1) % N + 1;
		}
		sort(pos.begin(), pos.end());
		offset += N / 4;
		
		int d = qry(pos);
		
		int dis[N + 69];
		for(int i = 1; i <= N; i++)
		{
			dis[i] = INF;
		}
		
		queue<int> q;
		for(int i = 0; i < pos.size(); i++)
		{
			int p = pos[i];
			q.push(p);
			dis[p] = 0;
		}
		
		while(!q.empty())
		{
			int p = q.front();
			q.pop();
			
			int nx = p % N + 1;
			if(dis[p] + 1 < dis[nx])
			{
				q.push(nx);
				dis[nx] = dis[p] + 1;
			}
			
			nx = (p + N - 2) % N + 1;
			if(dis[p] + 1 < dis[nx])
			{
				q.push(nx);
				dis[nx] = dis[p] + 1;
			}
		}
		
		for(int i = 1; i <= N; i++)
		{
			if(dis[i] != d)
			{
				isValid[i] = false;
			}
		}
			
		int c = 0;
		for(int i = 1; i <= N; i++)
		{
			if(isValid[i])
			{
				c++;
			}
		}
		if(c == 1)
		{
			break;
		}
	}
	
	for(int i = 1; i <= N; i++)
	{
		if(isValid[i])
		{
			printf("JAWAB %d\n", i);
			fflush(stdout);
			return 0;
		}
	}
}
