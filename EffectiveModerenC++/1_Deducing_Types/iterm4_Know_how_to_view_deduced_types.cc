#include <stdio.h>
#include <iostream>

template<typename T>
class TD;           // Type Displayer

int main(void) {
#if 0
  {
    // (1) 根据编译器报错的提示来查看decltype(x) / decltype(y)的类型
    const int a = 42;
    auto x = a;
    auto y = &a;
    TD<decltype(x)> xType;
    TD<decltype(y)> yType;
  }
#endif

  {
    // (2) 运行时输出
    const int a = 42;
    auto x = a;
    auto y = &a;
    std::cout << typeid(x).name() << "\n";    // i 
    std::cout << typeid(y).name() << "\n";    // PKi PK -> const to konst(const)
  }

  {
    // (3) typeid有时候也有问题
  }
  return 0;
}
