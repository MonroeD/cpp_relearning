#include <iostream>

// (1) 参数永远是左值，即使它的类型是一个右值引用
// void f(Widget&& w) 参数w是一个左值，即使它的类型是一个Widget的右值引用
int main() {
  return 0;
}
