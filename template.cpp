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

    ordered_set S;
    vector<int>nums{1,3,2,2,4,4,8,6,7,3};
    for(int i=0; i<nums.size(); i++){
        S.insert(nums[i]);
        cout << nums[i] << ':' << S.order_of_key(nums[i]) << endl;
    }
    for(auto x:S) cout << x << ' ';
    cout << endl << *S.find_by_order(0) << ',' << *S.lower_bound(5) << endl;

    return 0;
}