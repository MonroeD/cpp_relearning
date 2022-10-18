#include <iostream>
#include <typeinfo>

// auto的推导和iterm1模板的推导一样，除了一个例外
/*
auto x = 27;
const auto cx = x;
const auto& rx = cx;

编译器的行为看起来就像是认为这里每个声明都有一个模板
template<typename T>
void func_for_x(T param);  // 理想化的模板用来推导x的类型
func_for_x(27);

template<typename T>
void func_for_cx(const T param); // 理想化的模板用来推导cx的类型
func_for_cx(x);

template<typename T>
void func_for_rx(const T& param); // 理想化的模板用来推导rx的类型
func_for_rx(x);
*/

template<typename T>
void func(T param) {
}

template<typename T>
void func(std::initializer_list<T> initList) {
}

auto funcfunc() {
  return {1, 2, 3}; // 错误，推导失败
}

int main() {
  // c++11的初始化
  {
    int x1 = 27;
    int x2(27);
    int x3 = {27};
    int x4{27};
  }

  // 换成auto
  {
    // 当auto声明的变量使用花括号进行初始化时，auto类型会推导出audo的类型为std::initializer_list
    auto x1 = 27;      // int
    auto x2(27);       // int
    auto x3 = {27};    // std::initializer_list<int>, 值是{27}
    auto x4{27};       // std::initializer_list<int>, 值是{27}
    std::cout << typeid(x4).name() << "\n";  // 查看变量类型
    
    // 如果一个类型不能被成功被推导（比如花括号里面包含的是不同类型的变量），编译器会拒接这样的代码！
    //auto x5 = {1, 2, 3.0}; 因为会根据1, 2推断出T -> int, 又会根据3.0推断出 T -> double
  }

  // auto类型推导和模板类型推导的唯一不同的地方:
  // 当auto声明的变量使用花括号进行初始化时，auto类型会推导出audo的类型为std::initializer_list
  {
    auto x = {11, 23, 9}; // x 是std::initializer_list
    //f{{11, 23, 9}}; // 错误，不能推导出T
    func({11, 23, 9}); // T -> int, initList -> std::initializer_list<int>
  }
  return 0;
}
