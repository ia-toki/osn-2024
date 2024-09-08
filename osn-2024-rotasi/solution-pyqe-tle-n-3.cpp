#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;
long long n,d,nv=0,a[300069],vi[300069];

int main()
{
	long long rr,i,j,k,z=inf;
	
	scanf("%lld%lld",&n,&d);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
	}
	for(rr=0;rr<n;rr++)
	{
		for(i=1;i<=n;i++)
		{
			nv++;
			for(j=i;j<=min(n,i+d-1);j++)
			{
				if(a[j]<i||a[j]>i+d-1||vi[a[j]]>=nv)
				{
					break;
				}
				vi[a[j]]=nv;
				z=min(z,d-(j-i+1));
			}
		}
		k=a[1];
		for(i=1;i<=n-1;i++)
		{
			a[i]=a[i+1];
		}
		a[n]=k;
	}
	printf("%lld\n",z);
}
