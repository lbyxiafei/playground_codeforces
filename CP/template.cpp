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

#pragma region STL
// accumulate(it1,it2,num,functor)：累加/乘
// partial_sum(it1,it2,target,functor)：前缀和/积
// partition/stable_partition(it1,it2,lambda)：参考quick sort的partition
// merge(it1,it2,iit3,iit4,target)/inplace_merge(start,mid,end)：参考merge sort的辅助merge
// rotate/rotate_copy(it1,it2,it3,target)：以round robin的方式轮转/旋转数组
// all_of/none_of/any_of(it1,it2,lambda)：非常实用的f(it1,it2,lambda)的判定数组状态的语法
void STLVectorUtils() {
 
  // partition：和quick sort的partition原理一样，但无法得知pivot idx最终位置
  auto lessThan10 = [](int x) {
    return x < 10;
  };
  arr = {11, 12, 13, 2, 1, 3};
  partition(arr.begin(), arr.end(), lessThan10);
  forn(i, arr.size()) cout << arr[i] << ' ';
  cout << endl;
  // stable_partition：partition基础上保持原数组相对顺序
  arr = {11, 12, 13, 2, 1, 3};
  stable_partition(arr.begin(), arr.end(), lessThan10);
  forn(i, arr.size()) cout << arr[i] << ' ';
  cout << endl;

  // merge：把排好序的2个source数组合并为target数组
  A = {1, 2, 3}, B = {4, 5, 6}, C.resize(A.size() + B.size());
  merge(A.begin(), A.end(),
        B.begin(), B.end(),
        C.begin());
  cout << "merge" << ':';
  forn(i, C.size()) cout << C[i] << ' ';
  cout << endl;
  // inplace_merge：标准的merge_sort辅助方程的stl写法
  A = {4, 5, 6, 1, 2, 3};
  inplace_merge(A.begin(), A.begin() + 3, A.end());
  cout << "inplace_merge" << ':';
  forn(i, A.size()) cout << A[i] << ' ';
  cout << endl;

  // rotate(it1,it2,it3)：it1,2,3是顺序，把it2轮转到it1的位置
  arr = {1, 2, 3, 4, 5};
  rotate(arr.begin(), arr.begin() + 3, arr.end());
  forn(i, arr.size()) cout << arr[i] << ' ';
  cout << endl;
  // roatate_copy(it1,it2,it3,target_it)
  arr = {1, 2, 3, 4, 5}, A.resize(arr.size());
  rotate_copy(arr.begin(), arr.begin() + 3, arr.end(),
              A.begin());
  forn(i, arr.size()) cout << arr[i] << ' ';
  cout << endl;
  forn(i, A.size()) cout << A[i] << ' ';
  cout << endl;

  // all_of, any_of, none_of
  arr = {1, 2, 3, 4, 5};
  bool flag = all_of(arr.begin(), arr.end(), [](int x) {
    return x == 5;  // 所有arr[i]为5，flag为true
  });
  cout << flag << endl;
  flag = any_of(arr.begin(), arr.end(), [](int x) {
    return x & 1;  // 如果有一个arr[i]为奇数，则flag为true
  });
  cout << flag << endl;
  flag = none_of(arr.begin(), arr.end(), [](int x) {
    return !~x;  // 没有任何arr[i]为-1,则flag为true
  });
  cout << flag << endl;
}
#pragma endregion

int main() {
#ifdef _LBY
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  return 0;
}