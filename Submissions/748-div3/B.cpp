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

int calc(LL n, int a, int b){
    int res=0, x=a, cnt=0;
    while(n){
        //cout << n%10 << ',' << x << endl;
        if(n%10==x){
            cnt++;
            if(x==a) {
                if(cnt==1) x=b;
                if(cnt==2 && a==0 && b==0){
                    return res;
                }
            }
            else return res;
        }
        else res++;
        n/=10;
    }

    return 1e9;
}

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int T;
    cin >> T;
    while(T--){
        LL n; 
        int res=1e9;
        cin >> n;
        if(n%25==0) {
            cout << 0 << endl;
            continue;
        }
        res=min(res,calc(n,0,0));
        res=min(res,calc(n,0,5));
        res=min(res,calc(n,5,2));
        res=min(res,calc(n,5,7));
        cout << res << endl;
    }

    return 0;
}