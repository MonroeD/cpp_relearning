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
// auto 遵循item2->item1的标准，会忽略掉const/reference，因此返回的就会int, 而不是int&，而我们想要的是int&
// 因此需要通过decltype(auto)来获取返回int&
/*
 * 可通过int& i = authAndAccess_v1(vector, i); 编译会报错来验证上面我说的话
 * */
template<typename Container, typename Index>
auto authAndAccess_v1(Container& c, Index i) {
  //authenticateUser();
  int j = 10;
  return c[i];
}


// (3) decltype(auto)
// auto说明这个符号会被推导，decltype说明decltype的规则将会引导到这个推导中
// c[i]会返回真正的c[i]类型, 即是int&
template<typename Container, typename Index>
decltype(auto) authAndAccess_v2(Container& c, Index i) {
  //authenticateUser();
  int j = 10;
  return c[i];
}
/*
 * 但是获取这个引用的时候需要注意，比如说
 * auto x = authAndAccess_v2(c, i); // 这里的x就不是引用
 * auto& x = authAndAccess_v2(c, i); // x是引用
 * 具体上诉auto的使用可以见item2
 * 这点可以通过std::is_lvalue_reference<decltype(x)>::value来验证；
 * 或者通过去修改x的值来验证
 * */

// (4) 最完美的实现
/* 上述的实现不能绑定右值，比如说调用authAndAccess_v2(std::vector<int>{1, 2}, 0); 编译就会出错
 * */
// c++14版本
template<typename Container, typename Index>
decltype(auto) authAndAccess_v3(Container&& c, Index i) {
  //authenticateUser();
  return std::forward<Container>(c)[i];
}

// c++11版本
template<typename Container, typename Index>
auto authAndAccess_v3_11(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i]){
  //authenticateUser();
  return std::forward<Container>(c)[i];
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
