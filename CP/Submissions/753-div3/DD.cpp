#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update> ordered_set;
typedef tree<
    pair<int,int>,
    null_type,
    less<pair<int,int>>,
    rb_tree_tag,
    tree_order_statistics_node_update> ordered_multiset;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=100010;

int tr[N];

int lowbit(int x){
    return x&-x;
}

int add(int idx, int x){
    for(int i=idx; i<N; i+=lowbit(i))
        tr[i]+=x;
}

int query(int idx){
    int res=0;
    for(int i=idx; i; i-=lowbit(i))
        res+=tr[i];
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
        map<int,int> U,D;
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin >> arr[i];
        string s;
        cin >> s;
        for(int i=0; i<n; i++){
            if(s[i]=='R'){
                if(arr[i]>n) continue;
                int x=max(1,arr[i]);
                U[x]++;
            }
            else{
                if(arr[i]<1) continue;
                int x=min(n,arr[i]);
                D[x]++;
            }
        }
        bool flag=true;
        for(int i=1; i<=n; i++){
            cout << i << ':' << endl;
            for(auto&& [k,v]:D) cout << k << "-" << v << '\t';
            cout << endl;
            for(auto&& [k,v]:U) cout << k << "-" << v << '\t';
            cout << endl;

            auto it=D.lower_bound(i);
            auto it2=U.lower_bound(i);
            if(D.count(i)){
                auto it=D.lower_bound(i);
                D[it->first]--;
                if(D[it->first]==0){
                    D.erase(it->first);
                }
            }
            else if(it2!=U.end()){
                U[it2->first]--;
                if(U[it2->first]==0){
                    U.erase(it2->first);
                }
            }
            else if(it2!=U.begin() && U.begin()->first<=i){
                while(it2->first>i) it2--;

                U[it2->first]--;
                if(U[it2->first]==0){
                    U.erase(it2->first);
                }
            }
            else if(it!=D.begin() && D.rbegin()->first>=i){
                while(it->first<i) it++;

            }
            else{
                flag=false;
                break;
            }


        }
        if(flag) puts("YES");
        else puts("NO");


    }
    

    return 0;
}