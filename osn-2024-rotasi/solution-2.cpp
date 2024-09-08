#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long N, K, jumElemen, minJumElemen;
    cin >> N >> K;
    vector<int> A(N);
    for (int i=0; i<N; i++) cin>>A[i];
    
    if (K==1){
        minJumElemen=0;
    }else if (K==2){
        int L, R;
        minJumElemen=1;
        for (int i=0; i<N; i++){
            L=A[i];
            R=A[(i+1)%N];
            if (abs(L-R)==1){
                minJumElemen=0;
                break;
            }
        }
    }else if (K==3){
        long long P, Q, R, minX, maxX;
        minJumElemen=2;
        for (int i=0; i<N; i++){
			P=A[i]; 
			minX=P; 
			maxX=P;
			
			Q=A[(i+1)%N]; 
			minX=minX>Q?Q:minX;
			maxX=maxX<Q?Q:maxX;
			
			R=A[(i+2)%N];
			minX=minX>R?R:minX;
			maxX=maxX<R?R:maxX;
			
			if (maxX-minX==2){
				jumElemen=0;
			}else if (maxX-minX==1){
				jumElemen=1;
			}else if(maxX==minX){
				jumElemen=2;
			}else if(maxX-minX>2){
				if ((abs(P-Q)==1)||(abs(P-R)==1)||(abs(Q-R)==1)){
					jumElemen=1;
				}else{
					jumElemen=2;
				}
			}
			
			if (minJumElemen>jumElemen) minJumElemen=jumElemen;
			
        }
    }
    
    cout<<minJumElemen<<endl;

    return 0;
}