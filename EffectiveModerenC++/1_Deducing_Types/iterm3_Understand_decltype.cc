#include <iostream>
#include <deque>

class Widget {
  int x;
};

// decltype，给它一个名字或者表达式decltype就会告诉你名字或者表达式的类型
const int i = 0;           // decltype(i) -> const int
bool f(const Widget& w);   // decltype(w) -> const Widget&
                           // decltype(f) -> bool(const Widget&)

struct Point {
  int x;                   // decltype(Point::x) -> int
  int y;                   // decltype(Point::y) -> int
};

template<typename T>
class Vector {
  T& operator[] (std::size_t index);
};

Vector<int> v;            // decltype(v) -> Vector<int>
                          // decltype(v[0]) -> int&

// 在c++11中，decltype最主要的用途就是用于函数模板返回类型，而这个返回类型依赖形参
// (1) auto不会做任何类型推导，相反的，他只暗示使用了c++11的尾置返回类型语法
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i) -> decltype(c[i]) {
  //authenticateUser();
  //int j = 10;
  return c[i];
}

// (2) c++11允许自动推导单一语句的lambda的表达式的返回类型，c++14扩展到允许自动推导左右的lambda表达式和函数，甚至它们内含多条语句
// c++14版本
template<typename Container, typename Index>
auto authAndAccess_v1(Container& c, Index i) {
  //authenticateUser();
  int j = 10;
  return c[i];
}


// (3) decltype(auto) TODO, 见书上的解释吧
// c[i]会返回真正的c[i]类型
template<typename Container, typename Index>
decltype(auto) authAndAccess_v2(Container& c, Index i) {
  //authenticateUser();
  int j = 10;
  return c[i];
}

// 总结
// (1) decltype总是不加修改的产生变量或者表达式的类型
// (2) 对于T类型的左值表达式，decltype总是产出T的引用即T& TODO
// (3) 对于c++14支持decltype(auto), 就像auto一样，推导出类型，但是使用自己独特的规则进行推导
int main() {
  {
    std::deque<int> d;
    d.resize(6);
    //authAndAccess_v1(d, 5) = 10;  // 会编译失败
    authAndAccess_v2(d, 5) = 10;
  }

  // (4) decltype(auto) 推导出原本的类型
  {
    Widget w;
    const Widget& cw = w;
    auto myWidget1 = cw;    // auto类型推导，myWidget1 -> Widget
    auto myWidget2 = cw;    // decltype类型推导，myWidget2 -> const Widget&
  }
  return 0;
}
