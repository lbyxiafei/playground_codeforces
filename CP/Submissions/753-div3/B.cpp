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
        LL x, n;
        cin >> x >> n;
        LL t=n%4;
        LL d=n-t+1;
        for(int i=0; i<t; i++,d++){
            if(x&1) x+=d;
            else x-=d;
        }
        cout << x << endl;
    }

    //int x=0, d=1;
    //cout << x << ':';
    //for(int i=0; i<30; i++,d++){
    //    if(x&1) x+=d;
    //    else x-=d;
    //    cout << x << ' ';
    //}
    //cout << endl;

    //x=1, d=1;
    //cout << x << ':';
    //for(int i=0; i<30; i++,d++){
    //    if(x&1) x+=d;
    //    else x-=d;
    //    cout << x << ' ';
    //}
    //cout << endl;


    return 0;
}