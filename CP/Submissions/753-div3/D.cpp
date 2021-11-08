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
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

int main() {
#ifdef _LBY
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int T;
  cin >> T;
  forn(_,T){
    int n;
    cin >> n;
    vector<int> arr(n);
    forn(i,n) cin >> arr[i];
    string s;
    cin >> s;
    vector<int> L,R;
    forn(i,n) (s[i]=='B'?L:R).push_back(arr[i]);
    sort(L.begin(),L.end());
    sort(R.begin(),R.end(),greater<>());
    bool flag=true;
    forn(i,L.size())
      if(L[i]<i+1)
        flag=false;
    forn(i,R.size())
      if(R[i]>n-i)
        flag=false;
    if(flag) puts("Yes");
    else puts("No");
  }

  return 0;
}