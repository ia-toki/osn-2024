#include <iostream>
#include <bits/stdc++.h>
#include <iterator>
#include <set>
using namespace std;

int N, K;

bool isUnik(vector<int> a){
    sort(a.begin(), a.end());
    auto it = unique(a.begin(), a.end());
    return (it == a.end());
}

int main(){
    int minJumElemen=600001;
    
    cin >> N >> K;
    vector<int> A(N*2);
    for (int i=0; i<N; i++) {
		cin>>A[i];
		A[i+N]=A[i];
	}
    
    int l=0, r=0, tipe; 
    bool valid;
    vector<int> subA;
    
    subA.push_back(A[r]);
    while ((l<N)&&(r<N*2)){
        valid=true;
        if (r>=l){
            bool kondisi1=isUnik(subA);
            if (kondisi1==false){
                valid=false;
                tipe=1;
            }else{
                int maxElemen=*max_element(subA.begin(), subA.end());
                int minElemen=*min_element(subA.begin(), subA.end());
                bool kondisi2=(maxElemen-minElemen)<K;
                if (kondisi2==false){
			        valid=false;
			        tipe=2;
			    }
            }
        }
        
		if (valid){
			minJumElemen=min(minJumElemen, K-(r-l+1));
			subA.push_back(A[r+1]);
	        r++;
		}else{
		    subA.erase(subA.begin());
			l++;
		}
    }
    
    cout<<minJumElemen<<endl;

    return 0;
}