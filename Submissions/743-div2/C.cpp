#include <bits/stdc++.h>

using namespace std;

const int N=100010;

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int kk;
    cin >> kk;
    while(kk--){
        unordered_map<int,vector<int>> g;
        unordered_map<int,int> u2id,f;
        queue<int> q;

        int n;
        scanf("%d",&n);
        for(int i=1; i<=n; i++){
            int k;
            scanf("%d",&k);
            if(k==0) q.push(i),f[i]=1;
            for(int j=0; j<k; j++){
                int t;
                scanf("%d",&t);
                g[t].push_back(i);
                u2id[i]++;
            }
        }
        if(q.empty()){
            cout << -1 << endl;
            continue;
        }
        int res=1;
        while(q.size()){
            int u=q.front(); q.pop();
            for(auto nb:g[u]){
                if(nb<u)  f[nb]=max(f[nb],f[u]+1);
                else  f[nb]=max(f[nb],f[u]);
                res=max(res,f[nb]);
                u2id[nb]--;
                if(u2id[nb]==0){
                    q.push(nb);
                }
            }
        }
        bool flag=true;
        for(auto&& [u,c]:u2id){
            if(c){
                flag=false;
                break;
            }
            res=max(res,f[u]);
        }
        if(flag) cout << res << endl;
        else cout << -1 << endl;
    }

    return 0;
}