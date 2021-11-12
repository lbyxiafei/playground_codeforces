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
    string s;
    cin >> s;
    int a=0,b=0,c=0,res=-1;
    for(int l=0,r=0; r<n; r++){
      if(s[r]=='a') a++;
      else if(s[r]=='b') b++;
      else c++;

      while(l<=r && (b>a || c>a)){
        if(s[l]=='a') a--;
        else if(s[l]=='b') b--;
        else c--;
        l++;
      }
      if(a>b && a>c && r-l+1>=2){
        //cout << l << ' ' << r << endl;
        if(!~res) res=r-l+1;
        else res=min(res,r-l+1);
      }
    }
    cout << res << endl;
  }

  return 0;
}