#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;
using namespace __gnu_pbds;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;
typedef tree<
    pair<int, int>,
    null_type,
    less<pair<int, int>>,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_multiset;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

int main() {
#ifdef _LBY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    forn(_, T) {
        int n, res=-1;
        cin >> n;
        unordered_map<int,int> v2i;
        forn(i,n){
            int x;
            cin >> x;
            if(v2i.count(x)){
                int j=v2i[x];
                res=max(res,1+min(i,j)+min(n-i-1,n-j-1));
            }
            v2i[x]=i;
        }
        cout << res << endl;
    }

    return 0;
}