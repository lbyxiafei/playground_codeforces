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
    vector<vector<int>> arr;
    auto calc=[&](){
      int l=0, r=n-1;
      vector<int> A, B;
      while(l<r){
        while(l<n && s[l]=='0') l++;
        while(r>=0 && s[r]=='1') r--;
        if(l<r){
          A.push_back(l);
          B.push_back(r);
          swap(s[l],s[r]);
        }
      }
      if(A.size()){
        vector<int> t(A);
        reverse(B.begin(),B.end());
        forn(i,B.size()) t.push_back(B[i]);
        arr.push_back(t);
        return true;
      }
      return false;
    };
    while(calc());
    cout << arr.size() << endl;
    forn(i,arr.size()){
      cout << arr[i].size() << ' ';
      forn(j,arr[i].size()) cout << 1+arr[i][j] << ' ';
      cout << endl;
    }
  }

  return 0;
}