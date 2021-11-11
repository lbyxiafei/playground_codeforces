[toc]
### C++ 
- [Advanced C++, Qian Bo](https://www.youtube.com/playlist?list=PLE28375D4AC946CC3)
  - 课程的前半部分是在追赶式的学习理解C++的底层，或者说最重要的实质：指针、引用，以及一些重要的使C++不同于其他语言的极其powerful的概念：const、virtual
  - 混杂了语法学习和头脑风暴的前半阶段
  - 过渡到后半程，好像有了连接的感觉：底层的强大的概念组合在一起产生了各种不同的东西，这就是c++的魅力吧：clean以及re-use
  - 好好整理，继续学习

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
- A **compile time** constraint that an object anc not be modified.
  ```cpp
  const int i=9;
  const_cast<int&>(i)=6;

  int j;
  static_cast<const int&>(j)=7;


  const int *p1=&i; // data is const, pointer is not
  *p1=5; // error: assignment of read-only location * p1
  p1++; // this is okay

  int* const p2; // p2 is const, data it points to is not

  const int* const p3; // data and pointer are both const

  // Rule of thumb: if const is on the left of *, data is const;
  // If const is on the right of the *, pointer is const.
  int const *p4=&i; // warning，等同下行
  const int *p4=&i;

  ```
- const and Functions
  ```cpp
  void setAge(const int& a){age=a;} // Efficient: no need to copy the data, just pass the reference and protect the caller's data(by const)
  const string& getName() {return name;} // increase efficiency(ref is smaller in size than the copy of string) and protect callee's data(by const)
  void printDogName() const {cout << name << endl;} // 1. do not make any changes to member variables; 2. can only call another const functions inside the body.
  ```
- logic constness and bitwise constness
  ```cpp
  vector<int> arr;
  mutable int accessCounter; // 有用的syntax
  int getItem(int index) const {
    accessCounter++;
    return arr[index];
  }
  ```
#### Compiler generated functions
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
#### TBD
#### TBD