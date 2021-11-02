#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

int qmi(int a, int k, int p){
    int res=1;
    while(k){
        if(k&1) res=(LL)res*a%p;
        a=(LL)a*a%p;
        k>>=1;
    }
    return res;
}

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int T;
    cin >> T;
    while(T--){
        int n,k;
        cin >> n >> k;
        int N=1e9, tx=1;
        vector<int> arr;
        while(tx<N){
            arr.push_back(tx);
            tx<<=1;
        }
        arr.push_back(tx);
        //for(auto x:arr) cout << x << ' ';
        //cout << endl;
        vector<int> res;
        while(k){
          int l=0, r=arr.size()-1;
          while(l<r){
              int mid=l+r+1>>1;
              if(arr[mid]<=k) l=mid;
              else r=mid-1;
          }
          res.push_back(l);
          k-=arr[l];
        }

        int mod=1e9+7;
        //cout << k << endl;
        //for(auto x:res) cout << x << ' ';
        //cout << endl;
        //cout << qmi(105,105,mod);
        
        int t=0;
        for(auto x:res){
            t=(t+qmi(n,x,mod))%mod;
        }
        cout << t << endl;



    }

    return 0;
}