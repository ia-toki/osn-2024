#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;
long long n,d,nv=0,a[600069],vi[600079];

int main()
{
	long long i,j,mn,mx,z=inf;
	
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
		mn=inf;
		mx=-inf;
		nv++;
		for(j=i;j<=min(n*2,i+d-1);j++)
		{
			mn=min(mn,a[j]);
			mx=max(mx,a[j]);
			if(mx-mn+1>d||vi[a[j]]>=nv)
			{
				break;
			}
			vi[a[j]]=nv;
			z=min(z,d-(j-i+1));
		}
	}
	printf("%lld\n",z);
}
