#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;
long long n,d,a[300069],ca[300069];

int main()
{
	long long rr,i,j,r,k,z=inf;
	bool bad;
	
	scanf("%lld%lld",&n,&d);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
	}
	for(rr=0;rr<n;rr++)
	{
		for(i=1;i<=n;i++)
		{
			for(j=i;j<=n;j++)
			{
				for(r=i;r<=j;r++)
				{
					ca[r]=a[r];
				}
				sort(ca+i,ca+j+1);
				bad=0;
				for(r=i;r<=j;r++)
				{
					bad|=ca[r]<i||ca[r]>i+d-1||(r<j&&ca[r]>=ca[r+1]);
				}
				if(!bad)
				{
					z=min(z,d-(j-i+1));
				}
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
