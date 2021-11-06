### C++ 

#### 引用、指针
- https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable-in?page=1&tab=votes#tab-top
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
#### stack, heap and new keyword
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
