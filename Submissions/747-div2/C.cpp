#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

void calc(unordered_set<int>& res, int n){
    for(int i=2; i*i<=n; i++){
        if(n%i==0){
            res.insert(i);
            n/=i;
        }
    }
    if(n>1) res.insert(n);
}

vector<int> get(int n){
    vector<int> res;
    vector<bool> st(n,false);
    for(int i=2; i<=n; i++){
        if(!st[i]) res.push_back(i);
        for(int j=0; i*res[j]<=n; j++){
            st[i*res[j]]=true;
            if(i%res[j]==0) break;
        }
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
        int n;
        cin >> n;
        char ch;
        cin >> ch;
        string s;
        cin >> s;
        vector<int> arr;
        for(int i=1; i<=n; i++)
            if(s[i-1]!=ch)
                arr.push_back(i);
        if(arr.empty()){
            cout << 0 << endl;
            continue;
        }
        if(arr.back()!=n){
            cout << 1 << endl;
            cout << n << endl;
            continue;
        }
        if(arr.size()==1){
            cout << 1 << endl;
            cout << n-1 << endl;
            continue;
        }

        unordered_set<int> S;
        for(auto x:arr)
            calc(S,x);
        auto primes=get(n);
        int t=-1;
        for(auto x:primes)
            if(!S.count(x))
                t=x;
        if(~t){
            cout << 1 << endl;
            cout << t << endl;
            continue;
        }

        cout << 2 << endl;
        cout << n-1 << ' ' << n << endl;

        //auto T=get(100);
        //for(auto x:T) cout << x << ' ';
        //cout << endl;
        

    }

    return 0;
}