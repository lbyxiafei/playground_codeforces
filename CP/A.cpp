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

int res;
unordered_set<string> S;
void dfs(int a, int b, int c){
  string s=to_string(a)+','+to_string(b)+','+to_string(c);
  if(S.count(s)) return;
  S.insert(s);
  int t=abs(a+c-b*2);
  res=min(res,t);
  if(t==0) return;
  if(a+c>b*2){
    vector<int> arr{a,b,c};
    arr[0]--, arr[1]++;
    sort(arr.begin(),arr.end());
    if(abs(arr[0]+arr[2]-arr[1]*2)<=t) dfs(arr[0],arr[1],arr[2]);

    arr.clear();
    arr.push_back(a);
    arr.push_back(b);
    arr.push_back(c);
    arr[1]++,arr[2]--;
    sort(arr.begin(),arr.end());
    if(abs(arr[0]+arr[2]-arr[1]*2)<=t) dfs(arr[0],arr[1],arr[2]);
  }
  else{
    vector<int> arr{a,b,c};
    arr[0]++, arr[1]--;
    sort(arr.begin(),arr.end());
    if(abs(arr[0]+arr[2]-arr[1]*2)<=t) dfs(arr[0],arr[1],arr[2]);

    arr.clear();
    arr.push_back(a);
    arr.push_back(b);
    arr.push_back(c);
    arr[1]--,arr[2]++;
    sort(arr.begin(),arr.end());
    if(abs(arr[0]+arr[2]-arr[1]*2)<=t) dfs(arr[0],arr[1],arr[2]);
  }

}

int main() {
#ifdef _LBY
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int T;
  cin >> T;
  forn(_,T){
    vector<int> arr(3);
    cin >> arr[0] >> arr[1] >> arr[2];
    sort(arr.begin(),arr.end());
    res=abs(arr[0]+arr[2]-arr[1]*2);
    dfs(arr[0],arr[1],arr[2]);
    cout << res << endl;
  }

  return 0;
}