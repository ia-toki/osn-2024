#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

bool cmp(pair<int, int> p1, pair<int, int> p2)
{
	if(p1.fr != p2.fr)
	{
		return p1.fr < p2.fr;
	}
	else
	{
		return p1.sc < p2.sc;
	}
}

int main()
{
	int N;
	scanf("%d", &N);
	
	pair<int, int> ranges[N + 69];
	for(int i = 1; i <= N; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		ranges[i] = {l, r};
	}
	
	int M;
	scanf("%d", &M);
	
	int A[M + 69];
	for(int i = 1; i <= M; i++)
	{
		scanf("%d", A + i);
	}
	
	sort(ranges + 1, ranges + N + 1, cmp);
	vector<int> lList, rList;
	int maxR = 0;
	for(int i = 1; i <= N; i++)
	{
		int l, r;
		l = ranges[i].fr;
		r = ranges[i].sc;
		
		if(r > maxR)
		{
			lList.push_back(l);
			rList.push_back(r);
			maxR = r;
		}
	}
	
	int ans, mn, mx;
	ans = 0;
	mn = 0;
	mx = lList.size();
	for(int i = 1; i <= M; i++)
	{
		int curMin, curMax;
		curMin = lower_bound(rList.begin(), rList.end(), A[i]) - rList.begin();
		curMax = upper_bound(lList.begin(), lList.end(), A[i]) - lList.begin() - 1;
		if(curMin > curMax)
		{
			printf("-1\n");
			return 0;
		}
		
		mn = max(mn, curMin);
		mx = min(mx, curMax);
		if(mn > mx)
		{
			ans++;
			mn = curMin;
			mx = curMax;
		}
	}
	
	printf("%d\n", ans);
}
