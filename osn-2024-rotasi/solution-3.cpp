#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int N, K;

bool isUnik(vector<int> arr){
    int n = arr.size();
    unordered_set<int> s;
    for (int i = 0; i < n; i++) {
        s.insert(arr[i]);
    }
    return (s.size() == arr.size());
}

int main(){
    int minJumElemen=600001;
    
    cin >> N >> K;
    vector<int> A(N*2);
    for (int i=0; i<N; i++) {
		cin>>A[i];
		A[i+N]=A[i];
	}
    
    for (int l=0; l<N; l++){
        for (int r=l+1; r<=l+N; r++){
            auto start = A.begin() + l;
            auto end = A.begin() + r;
            
            vector<int> subA(r-l);
            copy(start, end, subA.begin());
            
            bool kondisi1=isUnik(subA);
            if (kondisi1==false) {
                break;
            }
            
            int maxElemen=*max_element(subA.begin(), subA.end());
            int minElemen=*min_element(subA.begin(), subA.end());
            bool kondisi2=(maxElemen-minElemen)<K;
            if (kondisi2==false) {
                break;
            }
            
            minJumElemen=min(minJumElemen, K-(r-l));
        }
    }
    
    cout<<minJumElemen<<endl;

    return 0;
}