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
        int n;
        cin >> n;
        vector<int> arr;
        for(int i=0; i<n; i++){
            int x;
            cin >> x;
            arr.push_back(x);
        }
        sort(arr.begin(),arr.end());
        arr.erase(unique(arr.begin(),arr.end()),arr.end());
        if(arr.size()<=1){
            cout << -1 << endl;
            continue;
        }
        else if(arr.size()==2){
            cout << arr[1]-arr[0] << endl;
            continue;
        }

        int res=arr[1]-arr[0];
        for(int i=1; i<arr.size(); i++) res=gcd(res,arr[i]-arr[i-1]);
        cout << res << endl;
    }


    return 0;
}