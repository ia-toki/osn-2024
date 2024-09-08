#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;
long long n,d,a[600069];
map<long long,bool> vtd;

int main()
{
	long long i,j,mn,mx,z=inf;
	bool bad;
	
	scanf("%lld%lld",&n,&d);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
	}
	for(i=n+1;i<=n*2;i++)
	{
		a[i]=a[i-n];
	}
	for(i=1;i<=n*2;i++)
	{
		bad=0;
		mn=inf;
		mx=-inf;
		vtd.clear();
		for(j=i;j<=n*2;j++)
		{
			mn=min(mn,a[j]);
			mx=max(mx,a[j]);
			bad|=mx-mn+1>d||vtd[a[j]];
			vtd[a[j]]=1;
			if(!bad)
			{
				z=min(z,d-(j-i+1));
			}
		}
	}
	printf("%lld\n",z);
}
