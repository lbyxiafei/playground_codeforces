#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define forn(i, n) for (int i = 0; i < n; i++)

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
vector<int> operator+(const vector<int> &A, const vector<int> &B) {
  vector<int> C(A.size());
  forn(i, A.size()) C[i] = A[i] + B[i];
  return C;
}

// stringstream的常见应用
// stringstream重载运算符应用
// ofstream简单应用
struct Cat {
  string name;
  int age;
};

// ostream(可以是stringstream，也可以是cout，等)和Cat之间的<<关系
// cout << c;
ostream &operator<<(ostream &sm, Cat &c) {
  sm << "Cat's name: " << c.name << ", age: " << c.age << endl;
  return sm;
}

// istream(可以是stringstream，cout，等)和cat之间的>>关系
// cin >> c.age >> c.name; // 如果是cin，那么手动输入age和name，ss的话可以预存
istream &operator>>(istream &sm, Cat &c) {
  sm >> c.name >> c.age;
  return sm;
}

void StreamUtils() {
  stringstream ss;
  int x = 15;
  // stringstream 当做缓存用以暂存数据不同形式
  ss << x << " Hex: " << hex << x << " Oct: " << oct << x;
  cout << ss.str() << endl;
  ss.str(string());  //清空ss，或者：ss.str("")也可以

  // 重载iostream对Cat的io运算符
  Cat c1{"BoLuo", 1}, c2;
  cout << c1;
  ss << "BenLei" << ' ' << 2;
  ss >> c2;
  cout << c2;

  // ofstream的简单应用
  ofstream ofs("output.txt", ios_base::app);
  ofs << "sup" << endl;
}

// transform(it1,it2,target,lambda)/变形：对source(s)数组进行自定义变形并写入target数组
// accumulate(it1,it2,num,functor)：累加/乘
// partial_sum(it1,it2,target,functor)：前缀和/积
// partition/stable_partition(it1,it2,lambda)：参考quick sort的partition
// merge(it1,it2,iit3,iit4,target)/inplace_merge(start,mid,end)：参考merge sort的辅助merge
// rotate/rotate_copy(it1,it2,it3,target)：以round robin的方式轮转/旋转数组
// all_of/none_of/any_of(it1,it2,lambda)：非常实用的f(it1,it2,lambda)的判定数组状态的语法
void VectorUtils() {
  vector<int> A{1, 2, 3, 4}, B(A.size()), C(A.size());
  // transform #1: 对原数组(A)进行变形，写入目标数组
  transform(A.begin(), A.end(),
            B.begin(),
            [](int x) {
              return -x;
            });
  forn(i, B.size()) cout << B[i] << ' ';
  cout << endl;
  // transform #2: 对两个原数组(A+B)进行相关变形，写入目标数组
  transform(A.begin(), A.end(),
            B.begin(),
            C.begin(),
            [](int x, int y) {
              return x + y;
            });
  forn(i, C.size()) cout << C[i] << ' ';
  cout << endl;

  // accumulate 累加
  int x=accumulate(A.begin(),A.end(),0);
  cout << x << endl;
  // accumulate 累乘
  x=accumulate(A.begin(),A.end(),1,multiplies<int>());
  cout << x << endl;

  // partial_sum: 前缀和
  vector<int> arr{1,2,3,4}, sarr(arr.size()+1);
  partial_sum(arr.begin(),arr.end(),sarr.begin()+1);
  forn(i,sarr.size()) cout << sarr[i] << ' ';
  cout << endl;
  // partial_sum: 前缀积
  partial_sum(arr.begin(),arr.end(),sarr.begin()+1,multiplies<int>());
  forn(i,sarr.size()) cout << sarr[i] << ' ';
  cout << endl;

  // partition：和quick sort的partition原理一样，但无法得知pivot idx最终位置
  auto lessThan10=[](int x){
    return x<10;
  };
  arr={11,12,13,2,1,3};
  partition(arr.begin(),arr.end(),lessThan10);
  forn(i,arr.size()) cout << arr[i] << ' ';
  cout << endl;
  // stable_partition：partition基础上保持原数组相对顺序
  arr={11,12,13,2,1,3};
  stable_partition(arr.begin(),arr.end(),lessThan10);
  forn(i,arr.size()) cout << arr[i] << ' ';
  cout << endl;

  // merge：把排好序的2个source数组合并为target数组
  A={1,2,3}, B={4,5,6}, C.resize(A.size()+B.size());
  merge(A.begin(),A.end(),
        B.begin(),B.end(),
        C.begin());
  cout << "merge" << ':';
  forn(i,C.size()) cout << C[i] << ' ';
  cout << endl;
  // inplace_merge：标准的merge_sort辅助方程的stl写法
  A={4,5,6,1,2,3};
  inplace_merge(A.begin(),A.begin()+3,A.end());
  cout << "inplace_merge" << ':';
  forn(i,A.size()) cout << A[i] << ' ';
  cout << endl;

  // rotate(it1,it2,it3)：it1,2,3是顺序，把it2轮转到it1的位置
  arr={1,2,3,4,5};
  rotate(arr.begin(),arr.begin()+3,arr.end());
  forn(i,arr.size()) cout << arr[i] << ' ';
  cout << endl;
  // roatate_copy(it1,it2,it3,target_it)
  arr={1,2,3,4,5}, A.resize(arr.size());
  rotate_copy(arr.begin(),arr.begin()+3,arr.end(),
              A.begin());
  forn(i,arr.size()) cout << arr[i] << ' ';
  cout << endl;
  forn(i,A.size()) cout << A[i] << ' ';
  cout << endl;

  // all_of, any_of, none_of
  arr={1,2,3,4,5};
  bool flag=all_of(arr.begin(),arr.end(),[](int x){
    return x==5; // 所有arr[i]为5，flag为true
  });
  cout << flag << endl;
  flag=any_of(arr.begin(),arr.end(),[](int x){
    return x&1; // 如果有一个arr[i]为奇数，则flag为true
  });
  cout << flag << endl;
  flag=none_of(arr.begin(),arr.end(),[](int x){
    return !~x; // 没有任何arr[i]为-1,则flag为true
  });
  cout << flag << endl;
}
#pragma endregion

#pragma region Algorithms
// TODO(game theory): 简单理论，稍作展开
void GameTheory() {
  cout << "TODO";
  return;
}
#pragma endregion

int main() {
#ifdef _LBY
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  VectorUtils();
  // StreamUtils();

  // ordered_set S;
  // vector<int> nums{1, 3, 2, 2, 4, 4, 8, 6, 7, 3};
  // for (int i = 0; i < nums.size(); i++) {
  //   S.insert(nums[i]);
  //   cout << nums[i] << ':' << S.order_of_key(nums[i]) << endl;
  // }
  // for (auto x : S) cout << x << ' ';
  // cout << endl
  //      << *S.find_by_order(0) << ',' << *S.lower_bound(5) << endl;

  return 0;
}