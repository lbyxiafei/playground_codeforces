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
        int n, l;
        cin >> n >> l;
        vector<int> cnt(l);
        forn(i,n) {
            int x;
            cin >> x;
            forn(j,l){
                int t=x>>j&1;
                if(t) cnt[j]++;
            }
        }
        int res=0;
        forn(j,l){
            if(cnt[j]>n-cnt[j]) res|=1<<j;
        }
        cout << res << endl;
    }

    return 0;
}