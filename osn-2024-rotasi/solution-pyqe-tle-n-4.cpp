#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;
long long n,d,nv=0,a[300069],vi[300069];

int main()
{
	long long rr,i,j,r,k,z=inf;
	
	scanf("%lld%lld",&n,&d);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
	}
	for(rr=0;rr<n;rr++)
	{
		for(i=1;i<=n;i++)
		{
			for(j=i;j<=min(n,i+d-1);j++)
			{
				nv++;
				for(r=i;r<=j;r++)
				{
					if(a[r]<i||a[r]>i+d-1||vi[a[r]]>=nv)
					{
						break;
					}
					vi[a[r]]=nv;
				}
				if(r>j)
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
