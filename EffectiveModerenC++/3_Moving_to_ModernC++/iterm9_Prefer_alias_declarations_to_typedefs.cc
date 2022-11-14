#include <stdio.h>
#include <list>
// (1) 声明一个函数指针时别名说明更容易被理解
/*
typedef void (*FP)(int, const std::string&); // typedef
using FP = void (*)(int, const std::string&); // using
*/

// (2) 模板，特别的，别名声明可以被模板化但是typedef不能
// 比如说链表使用自定义的内存分配器，MyAlloc
template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;
MyAllocList lw;

// 而使用typedef，就只能利用struct来
template<typename T>
struct MyAllocList {
  typename std::list<T, MyAlloc<T>>::type; // 注意这里必须得加typename
};
MyAllocList::type lw; // 由于MyAllocList::type是一个依赖类型，因此需要加上typename

// (3) type_traits的一些工具也是用typedef实现的(为什么不用using呢，哈哈哈，不说了)
// 至到c++14才想明白
// 因此如果在一个模板内部使用这些参数的时候，需要在它们前面加上typename
std::remove_const<T>::type       // c++11
std::remove_const_t<T>::type     // c++14

std::add_reference<T>::type     // c++11
std::add_reference_t<T>::type   // c++14

// 因此如果我们只能用c++11的话，可以如下定义
template<class T>
using remove_const_t = typename remove_const<T>::type;

template<class T>
using remove_reference_t = typename remove_reference<T>::type;
