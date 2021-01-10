___understand auto type deduction___

`auto` is same with template type deduction, with exception that `auto` type deduction is template type deduction. Template type deduction involves template and function and parameters. but `auto` with none of those things. but still direct mapping between template type deduction and `auto` type deduction.    

in a variable declaration using `auto`, the type specifier takes the palce of Param(section 1) , so there are three cases for that, too:      
1.  The type specifier is a pointer or reference, but not a universal reference.    
2.  The type specifier is a universal reference.    
3.  The type specifier is neither a pointer nor a reference.    

```
// just for check case 2

auto x = 27; // int
const auto cx = x; // int
const auto& rx = x; // int

auto&& u1 = x; // int&
auto&& u2 = cx; // int&
auto&& u3 = 27; // int&&, but not int, there is different with template type deduction.
```
exception:    
int C++98 codes:    
```
int x1 = 27; // type is int, value is 27
int x2(27); // type is int, value is 27
```
but in C++11:     
```
int x3 = {27}; // type is std::initializer_list<int>
int x4{27}; // type is std::initailizer_list<int>


auto x5 = {1, 2, 3.0} // error!, can not deduce T for std::initializer_list<T>
```
Although all variables value are 27, but they do not have the same meaning as the ones they replace, the first two  statements do, indeed, declare a variable of tyep `int` with value 27. the second two, however, declare avariable of type `std::initializer_list<int>` containing a single element with value 27!     

std::initializer_list<T> is a template, need inistantializing. `auto` can not deducte, because the values in branced initilizer don't have a single type.   

following codes are rejected:   
```
auto x = {11, 23, 9}; // x's type is std::initilizer_list

template <typename T>
void f(T param);

f({11, 23, 9}); // error, can not deduce type for T
---------------------------------------------------------
// but if you do this, if can execute
template <typename T>
void f(std::initializer_list<T> init_list);
f({11, 23, 9}); // T deduced as int, and init_list's type is std::initializer_list<int>
```
so the difference between `auto` and template type deduction is that `auto` assumes that a braced initializer represents a std::initializer_list, but template type deduction does not.   
