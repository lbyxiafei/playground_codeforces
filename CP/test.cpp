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

template <typename T>
T add(T a, T b) {
  return a + b;
}

class LiVec {
};

bool check(int x) {
  string s = to_string(x);
  vector<int> f(10);
  for (char ch : s)
    f[ch - '0']++;
  for (int i = 0; i < 10; i++)
    if (f[i] && f[i] != i)
      return false;
  return true;
}

int main() {
#ifdef _LBY
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  set<int> S{10, 20};
  auto it = S.lower_bound(15);
  cout << '!';
  cout << distance(S.begin(), it);
  cout << '!';

  return 0;
}