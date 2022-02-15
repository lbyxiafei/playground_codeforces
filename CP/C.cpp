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

    int n, len, m;
    cin >> n >> len >> m;
    vector<int> road(n), speed(n);
    forn(i,n) cin >> road[i];
    forn(i,n) cin >> speed[i];
    road.push_back(len);
    vector<int> arr, sarr(n+1);
    forn(i,n){
        arr.push_back(speed[i]*(road[i+1]-road[i]));
        sarr[i+1]=sarr[i]+arr.back();
    }
    int maxx=0;
    vector<vector<int>> dp(n,vector<int>(m+1));
    for(int r=0; r<n; r++){
        vector<int> tmp;
        for(int l=r-1; l>=0 && r-l<=m; l--){
            int d=0;
            for(int k=1; k<=r-l; k++){
                d+=road[l+2-k]-road[l+1-k];
                int t=sarr[r+1]-sarr[l]-speed[l]*d;
                dp[r][k]=max(dp[r][k], dp[l][m-k]+t);
                maxx=max(maxx, dp[r][k]);
                cout << r << '-' << k << ':' << maxx << endl;
            }
        }
    }
    cout << sarr[n]-maxx << endl;



    return 0;
}