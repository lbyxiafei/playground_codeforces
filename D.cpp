#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

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
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin >> arr[i];
        priority_queue<PII> q;
        for(int i=0; i<n; i++) {
            if(!arr[i]) continue;
            q.push({arr[i],i+1});
        }
        int tot=0;
        vector<vector<int>> res;
        while(q.size()>1){
            auto a=q.top(); q.pop();
            auto b=q.top(); q.pop();
            tot++;
            int x=min(a.second, b.second), y=max(a.second,b.second);
            res.push_back({x,y});
            if(a.first>1) q.push({a.first-1,a.second});
            if(b.first>1) q.push({b.first-1,b.second});
        }
        cout << tot << endl;
        for(auto&& e:res){
            cout << e[0] << ' ' << e[1] << endl;
        }
    }

    return 0;
}