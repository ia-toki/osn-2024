#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;
long long n,d,a[600069],ca[600069];

int main()
{
	long long i,j,r,mn,mx,z=inf;
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
		for(j=i;j<=n*2;j++)
		{
			for(r=i;r<=j;r++)
			{
				ca[r]=a[r];
			}
			sort(ca+i,ca+j+1);
			bad=0;
			mn=inf;
			mx=-inf;
			for(r=i;r<=j;r++)
			{
				mn=min(mn,ca[r]);
				mx=max(mx,ca[r]);
				bad|=mx-mn+1>d||(r<j&&ca[r]>=ca[r+1]);
			}
			if(!bad)
			{
				z=min(z,d-(j-i+1));
			}
		}
	}
	printf("%lld\n",z);
}
