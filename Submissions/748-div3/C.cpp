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

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n >> k;
        map<int,int> freq;
        for(int i=0; i<k; i++){
            int x;
            cin >> x;
            freq[x]++;
        }
        int idx=0, res=0;
        for(auto it=freq.rbegin(); it!=freq.rend(); it++){
            //cout << it->first << ':' << it->second << endl;
            int x=it->first, cnt=it->second;
            for(int i=0; i<cnt; i++){
                if(idx>=x) break;
                int d=n-x;
                res++;
                idx+=d;
            }
            if(idx>=x) break;
        }
        cout << res << endl;
    }

    return 0;
}