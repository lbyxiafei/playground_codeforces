#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define forn(i,n) for(int i=0; i<n; i++)

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


#pragma region STL
// 重载运算符/重新定义vector加号
//  vector<int> A{1,2,3}, B{2,3,4};
//  auto arr=A+B;
//  for(auto x:arr) cout << x << ' ';
//  cout << endl;
vector<int> operator+(const vector<int> &A, const vector<int> &B){
  vector<int> C(A.size());
  forn(i,A.size()) C[i]=A[i]+B[i];
  return C;
}

// Vector: transform
void VectorUtils(){
  vector<int> A{1,2,3,4}, B(A.size());
  // transform:
  transform(A.begin(),A.end(),
            B.begin(),
            [](int x){
              return x+1;
            });
  forn(i,B.size()) cout << B[i] << ' ';
  cout << endl;

}

#pragma endregion

#pragma region Algorithms
#pragma endregion

int main() {
#ifdef _LBY
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  VectorUtils();


  //ordered_set S;
  //vector<int> nums{1, 3, 2, 2, 4, 4, 8, 6, 7, 3};
  //for (int i = 0; i < nums.size(); i++) {
  //  S.insert(nums[i]);
  //  cout << nums[i] << ':' << S.order_of_key(nums[i]) << endl;
  //}
  //for (auto x : S) cout << x << ' ';
  //cout << endl
  //     << *S.find_by_order(0) << ',' << *S.lower_bound(5) << endl;

  return 0;
}