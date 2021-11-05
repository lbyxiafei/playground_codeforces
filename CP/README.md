### C++ 

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
- 
