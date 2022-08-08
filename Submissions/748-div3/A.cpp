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
        int a, b, c;
        cin >> a >> b >> c;
        int tot=a+b+c;
        int t=max(b,c);
        t=a>t?0:max(t+1-a,0);
        cout << t << ' ';
        t=max(a,c);
        t=b>t?0:max(t+1-b,0);
        cout << t << ' ';
        t=max(a,b);
        t=c>t?0:max(t+1-c,0);
        cout << t << endl;
    }

    return 0;
}