#include <stdio.h>
#include <string>
#include <iostream>
#include <deque>
#include <array>

// 5.6 变量模板
// 从c++14开始，可以用变量模板（之前只有函数模板和类模板）

// (1)
template<typename T>
constexpr T pi{3.1415926535897932385};

// 也可以用在不同单元(testcase TODO)

// (2) 也可以有默认模板类型
template<typename T = long double>
constexpr T pipi{3.1415926535897932385};

// (3) 也可以用非类型参数对变量模板进行参数化
template<int N>
std::array<int, N> arr{}; // array with N elements, zero-initialized
                          
// auto 得c++17
template<auto N>
constexpr decltype(N) dval = N; // type of dval depends on passed value

// (4) 用于数据成员的变量模板
template<typename T>
class MyClass {
  public:
    static constexpr int max = 1000;
};

#if 1
// 那么就可以为MyClass<>不同的特例化本本定义不同的值
template<typename T>
int myMax = MyClass<T>::max;
// 特例化
template<>
int myMax<std::string> = 2000;
// 使用
auto i = myMax<int>;
#else
// c++14之前, get到c++14这个特性的优点了
// 特例化
template<>
class MyClass<std::string> {
  public:
    static constexpr int max = 2000;
};
// 使用
auto i = MyClass<int>::max;
#endif

/*
// 这就意味着一个标准库
namespace std {
  template<typename T>
  class numeric_limits {
    public:
      static constexpr bool is_signed = false;
  };
}
template<typename T>
constexpr bool isSigned = std::numeric_limits<T>::is_signed;

// 可以这样用
isSigned<char>
//代替
std::numeric_limits<char>::is_signed;
*/

/*
// 类型萃取, 标准库用变量模板做一些事
std::is_const_v<T> // since c++17
std::is_const<T>::value // since c++11
// 标准库做了饿如下定义
namespace std {
  template<typename T>
    constexpr bool is_const_v = is_const<T>::value;
}
*/

int main() {
  {
    std::cout << pi<double> << '\n';
    std::cout << pi<float> << '\n';
  }

  {
    std::cout << pipi<> << '\n';
    std::cout << pipi<float> << '\n';
  }

  {
    std::cout << dval<'c'> << '\n'; // N has value 'c' of type char
    arr<10>[0] = 42;
  }
  return 0;
}
