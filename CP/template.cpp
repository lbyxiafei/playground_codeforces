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

#pragma region C++ Intro

void IntroUtils() {
  // 关于string literal，char array，char*的一些讨论
  // string作为mutable的存在，比较简单粗暴
  // string literal的定义方式:
  //  const char *a="abc"; 
  //  char *a="abc" // 这里特别注意：compile会过，但会有warning，并且会被强制转换成上面一行
  //                // 看似定义了char array，实际是string literal
  // char array的定义方式：
  //  char chs[]="abcdef";
  // 关于char指针:
  //  char *ch可以指向char array，也可以指向string literal
  //  如上所示，如果从定义出发，只能指代string literal
  //  要想指代char array，只有间接可能：
  //    char *ch;
  //    char chs[]="char array";
  //    ch=chs;

  // string，简单粗暴
  // 附带string到char array的朴素转换方式
  string s="string";
  swap(s[0],s[1]); 
  assert(s[0]=='t');
  char chs3[s.size()];
  forn(i,s.size()) chs3[i]=s[i]; // Now: "tsring"
  swap(*chs3,*(chs3+1));
  assert(*chs3=='s');
  // char array朴素定义
  char chs[7]={'s','t','r','i','n','g','\0'};
  char *b=chs;
  swap(*(b),*(b+1));
  assert(*b=='t');
  // char array更具一般化的定义
  // 附带和char指针的互动
  char chs2[8]="abcdefg";
  char *a=chs2;
  swap(*a, *(a+6));
  assert(*a=='g');
  swap(*chs2,*(chs2+6));
  assert(*chs2=='a');
  // wchar_t array的一般优化定义，以及与char指针的互动
  wchar_t chs4[]=L"abc";
  assert(*chs4==97); // 'a'->97
  swap(*(chs4),*(chs4+1));
  assert(*chs4==98);
  // wchar_t版本的string literal #1
  const wchar_t chs5[]=L"abc";
  //swap(*(chs5),*(chs5+1)); // error
  assert(*chs5==97);
  // wchar_t版本的string literal #2
  const wchar_t *cx=L"zabcde";
  //swap(*(cx),*(cx+1)); //error
  assert(*cx==122);

}
#pragma endregion

#pragma region STL
// transform(it1,it2,target,lambda)/变形：对source(s)数组进行自定义变形并写入target数组
// accumulate(it1,it2,num,functor)：累加/乘
// partial_sum(it1,it2,target,functor)：前缀和/积
// partition/stable_partition(it1,it2,lambda)：参考quick sort的partition
// merge(it1,it2,iit3,iit4,target)/inplace_merge(start,mid,end)：参考merge sort的辅助merge
// rotate/rotate_copy(it1,it2,it3,target)：以round robin的方式轮转/旋转数组
// all_of/none_of/any_of(it1,it2,lambda)：非常实用的f(it1,it2,lambda)的判定数组状态的语法
void STLVectorUtils() {
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
  int x = accumulate(A.begin(), A.end(), 0);
  cout << x << endl;
  // accumulate 累乘
  x = accumulate(A.begin(), A.end(), 1, multiplies<int>());
  cout << x << endl;

  // partial_sum: 前缀和
  vector<int> arr{1, 2, 3, 4}, sarr(arr.size() + 1);
  partial_sum(arr.begin(), arr.end(), sarr.begin() + 1);
  forn(i, sarr.size()) cout << sarr[i] << ' ';
  cout << endl;
  // partial_sum: 前缀积
  partial_sum(arr.begin(), arr.end(), sarr.begin() + 1, multiplies<int>());
  forn(i, sarr.size()) cout << sarr[i] << ' ';
  cout << endl;

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
  if(true){
    IntroUtils();
    STLVectorUtils();
  }
  return 0;
}