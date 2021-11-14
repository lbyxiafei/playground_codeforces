[toc]
# C++ 
- [Advanced C++, Qian Bo](https://www.youtube.com/playlist?list=PLE28375D4AC946CC3)
  - 课程的前半部分是在追赶式的学习理解C++的底层，或者说最重要的实质：指针、引用，以及一些重要的使C++不同于其他语言的极其powerful的概念：const、virtual
  - 混杂了语法学习和头脑风暴的前半阶段
  - 过渡到后半程，好像有了连接的感觉：底层的强大的概念组合在一起产生了各种不同的东西，这就是c++的魅力吧：`clean`以及`re-use`
## 主题分类
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
    virtual void speak() { 
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
#### composition(HAS-A) over inheritance(IS-A)
### operator
#### type conversion
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
#### operator new/delete
## 三岁知识点
### Resource Acquisition Is Initialization
- RAII（Resource Acquisition Is Initialization）是由c++之父Bjarne Stroustrup提出的，中文翻译为资源获取即初始化，他说：使用局部对象来管理资源的技术称为资源获取即初始化；这里的资源主要是指操作系统中有限的东西如内存、网络套接字等等，局部对象是指存储在栈的对象，它的生命周期是由操作系统来管理的，**无需人工介入**
### explicit constructor
- 在constructor前面加上explicit关键字，可以保证compiler能检测到implicit conversion并throw
- 参考：[explicit constructor](https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean)
### rvalue & lvalue
### namespace & using
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
