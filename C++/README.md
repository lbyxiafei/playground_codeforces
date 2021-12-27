[toc]
# C++ 
- [Advanced C++, Qian Bo](https://www.youtube.com/playlist?list=PLE28375D4AC946CC3)
  - 课程的前半部分是在追赶式的学习理解C++的底层，或者说最重要的实质：指针、引用，以及一些重要的使C++不同于其他语言的极其powerful的概念：const、virtual
  - 混杂了语法学习和头脑风暴的前半阶段
  - 过渡到后半程，好像有了连接的感觉：底层的强大的概念组合在一起产生了各种不同的东西，这就是c++的魅力吧：`clean`以及`re-use`
- [Modern C++, Qian Bo](https://www.youtube.com/playlist?list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH)
  - TODO
## 主题分类
- 按大专题类型进行展开
### 内存相关
#### 引用、指针
- reference
  - 为什么会有引用？
    - c++作为c语言的进阶版，必然会保留指针，但是为什么会有引用呢？
    - 很直观的原因是：语法糖
    - 作者给出的原因是：为了实现`operator overloading`
  - 引用是什么
    - 可以说，本质是个`const指针`，又叫指针常量，然而跟指针的用法截然不同
    - 也可以说，是object的别名，一块儿制定内存的别名，永远指向该内存区域
    - 同时，其本身的地址和size是`隐形`的，即，addr和sizeof返回的都是指向内容的addr和size
  - 引用的特点
    - 不能为空，创建时必须绑定有效内存区域
    - 无法重新绑定
    ```cpp
    int x=1, y=2;
    int &ref=x;
    ref=y;  // x=y,即x被赋值2
    ref=&y; // error:incompatible pointer to integer conversion assigning to 'int' from 'int *'
    ```
  - 引用的优势（相比指针）
    - 使用起来非常安全，绝无NPE的可能
    - 写法更为简洁（如果是指针，调用时需要取地址&，展开时需要取值*）
  - 结论：多用引用
- pointer
  - 可以为空，也可以自由绑定、解绑
    - 因而可能出现：野指针。即，p1，p2都指向同一object，如果p1被free了，p2就成了野指针
  ```cpp
  int t=3;
  // 拷贝：创建了一个新的内存空间，并把原值(t的值)copy到新的地址
  int x=t;
  assert(&x!=&t);
  // 无创建，无拷贝
  int &x=t;
  assert(&x==&t);
  // 创建新内存空间，内存空间存了另一个内存地址，所存的地址为原数据地址(t的地址)
  int *x=&t;
  assert(x==&t);
  ```
#### const
- 定义：A **compile time** constraint that an object can not be modified.
  - 然而也可以有例外，尽管看上去更像是quirk：
    ```cpp
    const int i=9;
    const_cast<int&>(i)=6; // 尽管可能会compile过，但是i的std::out依然是9
    ```
- const & pointer
  - 难点，根据const的不同位置，所定义的const对象也不同
    - Rule of thumb: 如果const出现在*的左侧，那么数据是const(If const is on the left of *, data is const; if const is on the right of the *, pointer is const.)
    ``` cpp
    const int *p1=&i; // data is const, pointer is not
    *p1=5; // error: assignment of read-only location * p1
    p1++; // this is okay

    int* const p2; // p2 is const, data it points to is not

    const int* const p3; // data and pointer are both const

    int const *p4=&i; // warning，等同下行
    const int *p4=&i;
    ```
- const & function
  - 难点，与上面类似，根据const在function中不同的位置，达到的效果不同
    - const param: 保护caller的data不被function改动
      ```cpp
      void setAge(const int& a){age=a;} 
      ```
    - const return: 保护callee的data不被后续caller的logic改动
      ```cpp
      const string& getName() {return name;} 
      ```
    - const function: 
      - 大前提：必须是class的scope之内的function
      - 作用：保护class的所有member不被改动（mutable除外）；同时在这个function内不能调用非const function
      ```cpp
      class B{
        vector<int> arr;
        mutable int cnt;
        int getItem(int index) const {
          cnt++; // 因为cnt是mutable，所以可以被改动
          return arr[index];
        }
      };
      ```
- logic constness and bitwise constness
  - TODO
#### stack, heap
- stack
  - Stored in computer RAM just like the heap.
  - Variables created on the stack will go `out of scope` and are `automatically deallocated`.
  - Much faster to allocate in comparison to variables on the heap.
  - Implemented with an actual stack data structure.
  - Stores local data, return addresses, used for parameter passing.
  - Can have a stack overflow when too much of the stack is used (mostly from infinite or too deep recursion, very large allocations).
  - Data created on the stack can be used without pointers.
  - You would use the stack if you know exactly how much data you need to allocate before compile time and it is not too big.
  - Usually has a maximum size already determined when your program starts.
- heap
  - Stored in computer RAM just like the stack.
  - In C++, variables on the heap must be destroyed manually and never fall out of scope. The data is freed with delete, delete[], or free.
  - Slower to allocate in comparison to variables on the stack.
  - Used on demand to allocate a block of data for use by the program.
  - Can have fragmentation when there are a lot of allocations and deallocations.
  - In C++ or C, data created on the heap will be pointed to by pointers and allocated with `new` or `malloc` respectively.
  - Can have allocation failures if too big of a buffer is requested to be allocated.
  - You would use the heap if you don't know exactly how much data you will need at run time or if you need to allocate a lot of data.
  - Responsible for memory leaks.
- static
  - Global variable
  - Only one copy for the entire program, no matter how many threads exist
### 多态
#### inheritance
- 首先，任何情况下Base class的private member均无法被Derived class继承
- 大体而言，共有三种关键字规范继承的种类：public, protected, private
  - public
    - `Base的public到了Derived还是public，Base的protected到了Derived还是protected`
      ```cpp
      class B:public D{};
      ```
  - protected
    - `Base的public到了Derived是protected，Base的protected到了Derived还是protected`
      ```cpp
      class B:protected D{};
      ```
  - private
    - `Base的public到了Derived是private，Base的protected到了Derived是private`
      ```cpp
      class B:private D{};
      ```
- 继承的二元性(`Duality` of inheritance)
  - Interface
    - pure virtual function
    - non-virtual public function
  - Implementation
    - protected function
    - non-virtual public function
> 讨论：'protected' function provides implementation only; in another word, 'protected' protect base function being overriden; in another word, derived class can only use it, not overriding it
  ```cpp
  /*
  output:
    Hello World!
    B bark
    D speak!
    D wisper
  */
  class B{
      private:
      protected:
      void wisper(){cout << "B wisper" << endl;}
      public:
      void bark(){ cout << "B bark" << endl; }
      virtual void speak(){ cout << "B speak" << endl; }
  };

  class D: public B{
      private:
      protected:
      void wisper(){cout << "D wisper" << endl;}
      public:
      void bark(){cout << "D bark!" << endl;}
      virtual void speak() { // 理论上这里derived class funcetion的virtual关键字可以去掉，效果不变，但没必要 
          cout << "D speak!" << endl;
          wisper();
      }
  };

  int main() {
      std::cout << "Hello World!\n";
      B *bd=new D;
      bd->bark();
      bd->speak(); // 如过D中没有wisper，那么会打印：B wisper
      //bd->wisper(); //error: wisper is a protected member of 'B'
  }
  ```
#### virtual
- 纯虚函数：`virtual void func=0;`
  - 其他语言中`抽象`函数的代替
  - 任何有纯虚函数的类成为抽象类，不能声称对象
- 一个基指针指向子对象，如果调用的函数是virtual，那么运行的就是子类的函数，否则，运行的依旧是基类
  - [Code参考](####inheritance)
#### composition(HAS-A) over inheritance(IS-A)
- Recommended：不要造Car-Family，去造车的部件的class(abstract)，而后造车的class，来inherite各种部件
  ```cpp
  class xCar:public Car{
    SteeringWheel *p_steerwheel=new SteeringWheel(123);
    Accelerator *p_ac=new Accelerator(345);
  };
  ```
### operator
- C++最具特色的强大功能之一：重载运算符
- 普遍形式：`T& operator?(T& lhs, T& rhs){}`
  - 问号代表运算符，三个T之间没有必然联系
  - 第一个T表示返回结果类型，第二个是`left hand side`，第三个是`right hand side`
  ```cpp
  vector<int>& operator*(vector<int>& A, vector<int>& B){
    for(int i=0; i<A.size(); i++) A[i]*=B[i];
    return A;
  }

  int main() {
    vector<int> A{1,2,3}, B{2,3,4};
    auto C=A*B;
    for(auto x:C) cout << x << ' '; // {2,6,12}
    cout << endl;
  }
  ```
#### 输入(>>)，输出(<<) operator
- 以stringstream为例：
  ```cpp
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

  int main(){
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

    return 0;
  }
  ```
#### type conversion operator
- `operator Type(){}`
  ```cpp
  class B{
      public:
      operator string() const {
          return "x";
      }
  };

  int main() {
      std::cout << "Hello World!\n";
      B b;
      cout << (string)b << endl; // x
      cout << string(b) << endl; // x
  }
  ```
#### functor/operator()
- One of the primary goal when overloading `operator()` is to create a functor. 
- A functor acts just like a function, but it has the advantages that it is stateful, meaning it can keep data reflecting its state between calls.
```cpp
struct Accumulator
{
    int counter = 0;
    int operator()(int i) { return counter += i; }
}
...
Accumulator acc;
cout << acc(10) << endl; //prints "10"
cout << acc(20) << endl; //prints "30"
```
#### User Defined Literals
- 工程向实用技巧，经典用处：度量衡的标注与转换
```cpp
int operator"" _bin(const char* chs, size_t sz){
  int res=0;
  for(int i=0; i<sz; i++){
    res<<=1;
    res+=chs[i]-'0';
  }
  return res;
}

int main() {
  cout << "1"_bin << endl;    // 1
  cout << "11"_bin << endl;   // 3
  cout << "110"_bin << endl;  // 6
}
```
#### operator new/delete
- 重载new/delete operator(new_handler)的一个重要的用途：帮助`debug memory leak`
## 三岁知识点
- 三岁知识点的收罗、整理
- 目标：融会贯通后开辟移动至主题专区
### Resource Acquisition Is Initialization
- RAII（Resource Acquisition Is Initialization）是由c++之父Bjarne Stroustrup提出的，中文翻译为资源获取即初始化，他说：使用局部对象来管理资源的技术称为资源获取即初始化；这里的资源主要是指操作系统中有限的东西如内存、网络套接字等等，局部对象是指存储在栈的对象，它的生命周期是由操作系统来管理的，**无需人工介入**
### explicit constructor
- 在constructor前面加上explicit关键字，可以保证compiler能检测到implicit conversion并throw
- 参考：[explicit constructor](https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean)
### rvalue & lvalue
#### rvalue/lvalue基本概念
- lvalue: `An object that occupies some identifiable location in memory.`
- rvalue: `Any object that is not a lvalue.`
- lvalue can be implicitly transferred to rvalue.
  ```cpp
  int i=1;
  int x=i; // i is lvalue, used as rvalue here
  ```
- rvalue should be explicitly used to create a lvalue
  ```cpp
  int v[5];
  *(v+3)=4; // v+3是一个rvalue，*(v+3)变成了lvalue
  ```
#### rvalue reference
- What is `rvalue reference`?
  ```cpp
  int a=5;    // a是lvalue
  int &b=a;   // b是lvalue reference
  int &&c     // c是rvalue reference
  ```
- Rvalue reference被用来：
  - `1.Moving semantics`
    ```cpp
    class boVector{
      int size;
      double *arr_;
    public:
      // Copy constructor:
      boVector(const boVector& rhs){
        size=rhs.size();
        arr_=new double[size];
        for(int i=0; i<size; i++){arr_[i]=rhs[i];}
      }
      // Move constructor:
      boVector(const boVector&& rhs){
        size=rhs.size();
        arr_=rhs.arr_;
        rhs.arr_=nullptr;
      }
      ~boVector(){delete arr_;}
    };
    ```
  - `2.Perfect forwarding`
    - `T&&`是universal reference，用法原理如下
      ```cpp
      template<typename T>
      void relay(T&& arg){
        foo(std::foward<T>(arg));
      }

      // Implementation of std::forward()
      template<typename T>
      T&& forward(typename remove_reference<T>::type& arg){
        return static_cast<T&&>(arg);
      }
      ```
    - `std::move()` vs `std::forward()`
      - move(): turn arg into an rvalue type
      - forward(): turn arg into type of T&&
### namespace & using
- using的两种用法：
  - using directively：`bring all namespace members into current scope`
    ```cpp
    using namespace std;
    ```
  - using declaratively: `bring a member from base class to current class's scope`
    - using can also be used to overcome `name hiding`
    ```cpp
    class B{
      public:
      void func(){cout << '!' << endl;}
      void output(int x){cout << x << endl;}
    };
    class D:private B{
      public:
      using B::func; // 这里using使得原本private的func函数（private继承）变成public
      using B::output; // 如果没有这一行，d.output(3)会出现name hiding的error
      void test(){func();} // 这里的func是D继承自B的private func
      void output(){cout << '?' << endl;}
    };
    int main() {
      D d;
      d.func();
      d.test();
      d.output(3);
    }
    ```
- anonymous namespace: 可以被同一文件内的其他member call
  ```cpp
  void f(int x){cout << '?' << endl;}
  namespace {
    void f(){cout << '!' << endl;} // 必须保证两个f()的param形式不同
    void g(){f();}
  }
  int main() {
    f();
    g();
  }
  ```
  
### compiler generated functions
- Copy constructor(`Dog d2(d1)`).
  ```cpp
  Dog(Dog& d){}
  ```
- Copy assignment operator(`Dog d2=d1`).
  ```cpp
  Dog& operator=(const Dog& d){}
  ```
- Default constructor (only if there is no constructor declared).
- Destructor.
  ```cpp
  ~Dog(){}
  ```
### casting - explicit type converstion
- Type conversion分两种：1. implicit type conversion, 2. explicit type conversion
- 这里的casting就是explicit type conversion
- reinterpret_cast针对地址进行cast，最为危险；剩下的static_cast相对比较危险
- C++ Style casting
  - static_cast
    ```cpp
    int i=9;
    float f=static_cast<float>(i);
    ```
  - dynamic_cast
    - pointer and reference only
    - downcast only(base=>derived)
  - const_cast
    - pointer and reference only
  - reinterpret_cast
    - pointer and reference only
- C Stype casting
  - 下面两种效果一样
    ```cpp
    short a=2000;
    int i=(int)a; // C like cast notion
    int j=int(a); // functional notion
    ```
### Koening lookup/ADL
- Argument Dependent Lookup
- Definition of class: `A class describes a set of data, along with the functions that operate on that data.`
  - 根据class的定义，以下的h()和operator<<()重载方程都属于class C，即使从scope的角度看实在class的外面
  ```cpp
  namespace A{
    class C{
      public:
      void f()=0;
      void g()=0;
    };
    void h(C);
    ostream& operator<<(ostream& os, const &C);
  }
  ```
### functional programming
- functional programming：一种全新的programming model
- template-lambda模板 function
  ```cpp
  //万物皆可template化
  template<typename func>
  void filter(func f, vector<int> arr){
    for(auto x:arr)
      if(f(x))
        cout << x << ' ';
    cout << endl;
  }
  ```
### user defined literals
- Restriction: 只能用以下几种形式的params
  - `char const*`
  - `unsigned long long`
  - `long double`
  - `char const*, std::size_t`
  - `wchar_t const*, std::size_t`
  - `char16_t const*, std::size_t`
  - `char32_t const*, std::size_t`
- Return value 可以是任意形式
  ```cpp
  // 这里的sz被系统自动写入
  int operator"" _bin(const char* chs, size_t sz){
    int res=0;
    for(int i=0; i<sz; i++){
      res<<=1;
      res+=chs[i]-'0';
    }
    return res;
  }

  cout << "110"_bin; // 6
  ```
## 语法
- STL的用法探索
- 高级先进的数据结构、library的语法和使用指南：pbds
- 与上面两章的侧重点（概念）稍有不同，更侧重实用
### 基础 
#### constexpr
- Force the computation to happen at compile time.
#### string
- 关于`string literal`，`char array`，`char*`和`string`的一些讨论
  - `string`作为mutable的存在，相对简单粗暴
  - `string literal`的定义方式:
    - `const char *a="abc";` 
    - `char *a="abc"` 这里特别注意：compile会过，但会有warning，并且会被强制转换成上面一行
      - 看似定义了char array，实际是string literal
  - char array的定义方式：
    - `char chs[]="abcdef";`
  - char*:
    - `char *ch;` 可以指向char array，也可以指向string literal
      - 如上所示，如果从定义出发，只能指代string literal
      - 要想指代char array，只有间接可能：
        ```cpp
        char *ch;
        char chs[]="char array";
        ch=chs;
        ```
- 一些实验性测试：
  ```cpp
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
  ```
- string的几种不同的定义方式
  - char: `string s(2,'a');` 
  - vector: `string s(arr);`
  - literal string: `string s("abc");`
- member functions:
  - `resize`：甚至可以起到right padding的作用：
    ```cpp
    string s("abc");
    s.resize(5,'!');
    assert("abc!!"==s);
    ```
#### constructor
- constructor的语法
  - Struct/ClassName(params): params(p_val) {...}
    ```cpp
    struct Catio {
      int age;
      string name;
      unordered_map<int,int> cache;
      Catio *brother, *sister;

      // 注意：与其他语言不同之处是多了“冒号”，冒号之后的区域叫：initialization_list section
      Catio() : cache(), brother(nullptr), sister(nullptr) {}
      // initialization_list section可以直接调用前面的constructor
      Catio(int _a, string _n) : Catio() {
        age = _a;
        name = _n;
      }
      // 注意：下面这个mixed：mem-init + constructor却不行
      // Error: a deligata delegating constructor cannot have other mem-initializers
      // Catio(string _n) : name(_n), Catio() {}

      // 也可以直接赋值
      Catio(int _a, string _n, Catio *_b, Catio *_s) : age(_a), name(_n), brother(_b), sister(_s) {}
    };
    ```
#### try/catch/exception
- TODO
### STL
#### non-member functions
##### `count`/`count_if`
  ```cpp
  vector<int> arr{1,2,3};
  assert(1==count(arr.begin(),arr.end(),1));
  assert(2==count_if(arr.begin(),arr.end(),[](int x){return x&1;}));
  ```
##### `for_each`
  ```cpp
  vector<int> arr{1,2,3};
  for_each(arr.begin(),arr.end(),[](int& x){x++;}); // {2,3,4}，注意这里x是引用类型
  ```
##### `transform`
- 单数组转换
  ```cpp
  vector<int> A{1,2,3}, B{4,5,6}, C{0,0,0};
  transform(A.begin(),A.end(),C.begin(),[](int x){return x+1;}); // C: {2,3,4}
  ```
- 双数组转换
  ```cpp
  vector<int> A{1,2,3}, B{4,5,6}, C{0,0,0};
  transform(A.begin(),A.end(),B.begin(),C.begin(),[](int x,int y){return x+y;}); // C: {5,7,9}
  ```
##### `accumulate`
- 累加（default）`int tot=accumulate(arr.begin(),arr.end(),0);`
- 累乘 `int prod=accumulate(arr.begin(),arr.end(),1,multiplies<int>())`
- 自定义/lambda
  - 举例：将数组用dash相连（string形式）
    ```cpp
    string& link(string& lhs, int& rhs){
      string t=lhs.size()?"-":"";
      lhs+=t+to_string(rhs);
      return lhs;
    }

    vector<int> arr{1,2,3};
    string s;
    auto res=accumulate(arr.begin(),arr.end(),s,link); // 1-2-3
    ```
##### `partial_sum`
- 使用方式和`accumulate`类似，99%的被用于生成`前缀和`：`partial_sum(arr.begin(),arr.end(),sarr.begin()+1);`
- 前缀积同理：`partial_sum(arr.begin(),arr.end(),sarr.begin()+1,multiplies<int>());`
- 自定义/lambda
  - 似乎只能是同样数据类型的数组之间转换
    ```cpp
    string& link(string& lhs, string& rhs){
      string t=lhs.size()?"-":"";
      lhs+=t+rhs;
      return lhs;
    }

    vector<string> arr{"1","2","3"}, S(arr.size()+1);
    partial_sum(arr.begin(),arr.end(),S.begin()+1,link); // {"","1","1-2","1-2-3"}
    ```
##### `merge`/`inplace_merge`
- 前提：需要merge的inputs必须是已经排好序的
- merge：`merge(A.begin(),A.end(),B.begin(),B.end(),C.begin());`
- inplace_merge：`inplace_merge(A.begin(),A.begin()+k,A.end());`
  - 将已排好序的[A,A+k)与[A+k,A+n)部分进行in place merge
  - 可以用来替代merge sort的后半部logic
##### `partition`/`stable_partition`
- partition：`auto iter=partition(arr.begin(),arr.end(),func);`
  - func自定义，例如可以是小于pivot返回true（quick sort前半部逻辑）
  - 可以用于替代quick sort的前半部logic
- stable_partition：`auto iter=stable_partition(arr.begin(),arr.end(),lessThan10);`
##### `rotate`/`rotate_copy`
- rotate: `rotate(arr.begin(),arr.begin()+k,arr.end());`
  - 把[arr,arr+k)与[arr+k,arr+n)进行翻转（param用法与inplace_merge的类似）
- rotate_copy: `rotate_copy(arr.begin(),arr.begin()+k,arr.end(),B.begin());`
##### `all_of`/`none_of`/`any_of`
- `all_of(arr.begin(),arr.end(),func);`：所有arr的元素都必须满足func，返回true
- `any_of(arr.begin(),arr.end(),func);`：任意arr的元素满足func，返回true
- `none_of(arr.begin(),arr.end(),func);`：所有arr的元素都不满足func，返回true
#### member functions
##### TODO
