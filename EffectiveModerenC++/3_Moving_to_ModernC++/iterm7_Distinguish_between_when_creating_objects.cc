#include <iostream>
#include <atomic>
#include <string>

/*
// (1) 在构造函数调用中，只要不包含std::initializer_list参数，那么花括号和小括号初始化都会产生一样的结果
class Widget {
public:
  Widget(int i, bool b); // 构造函数1
  Widget(int i, double d); // 构造函数2
};

Widget w1(10, true); // 调用构造函数1
Widget w1{10, true}; // 同上
Widget w1(10, 5.0); // 调用构造函数2
Widget w1{10, 5.0}; // 同上
                     
// (2)
class Widget {
public:
  Widget(int i, bool b); // 构造函数1
  Widget(int i, double d); // 构造函数2
  Widget(std::initializer_list<long double> i); // 构造函数3
};

Widget w1(10, true); // 调用构造函数1
Widget w1{10, true}; // 调用构造函数3(10, true会转化为long double)
Widget w1(10, 5.0); // 调用构造函数2
Widget w1{10, 5.0}; // 调用构造3（10 5.0会转化为long double）
                     
!!! 编译器热衷于把括号初始化与使std::initializer_list构造函数匹配，热综程度甚至超过了最佳匹配
// (3) 甚至于普通的构造函数和移动构造函数都会被std::initializer_list劫持掉
class Widget {
public:
  Widget(int i, bool b); // 构造函数1
  Widget(int i, double d); // 构造函数2
  Widget(std::initializer_list<long double> i); // 构造函数3
};
*/

class Widget2 {
public:
  Widget2(int i, bool b) {printf("Widget2(int i, double b)\n");}; // 构造函数1
  Widget2(int i, double d) {printf("Widget2(int i, double d)\n");}; // 构造函数2
  Widget2(std::initializer_list<long double> i) {printf("Widget2 std::initializer_list<long double>\n");}; // 构造函数3
};

// (3) 甚至于普通的构造函数和移动构造函数都会被std::initializer_list劫持掉
class Widget3 {
public:
  Widget3(int i, bool b) {printf("Widget3(int i, double b)\n");}; // 构造函数1
  Widget3(int i, double d) {printf("Widget3(int i, double d)\n");}; // 构造函数3
  Widget3(std::initializer_list<long double> i) {printf("Widget3 std::initializer_list<long double>\n");}; // 构造函数3
};

// (4) 只有当没办法把括号初始化中实参的类型转换为std::initializer_list时，编译器才会回到正常的函数决议的候选者
class Widget4 {
public:
  Widget4(int i, bool b) {printf("Widget4(int i, double b)\n");}; // 构造函数1
  Widget4(int i, double d) {printf("Widget4(int i, double d)\n");}; // 构造函数3
  Widget4(std::initializer_list<std::string> i) {printf("Widget4 std::initializer_list<long double>\n");}; // 构造函数3
};
                                                                                                           
// (5) 默认构造函数
class Widget5 {
public:
  Widget5() {printf("Widget5()\n");}
  Widget5(std::initializer_list<int> il) {printf("Widget5(std::initializer_list)\n");}
};

int main() {
  {
    Widget2 w1(10, true); // 构造函数1
    Widget2 w2{10, true}; // 调用构造函数3(10, true会转化为long double)
    Widget2 w3(10, 5.0); // 调用构造函数2
    Widget2 w4{10, 5.0}; // 调用构造3（10 5.0会转化为long double）
  }

  {
    Widget3 w1(10, true);
    Widget3 w2(w1);  // 使用小括号，调用拷贝构造函数
    Widget3 w3{w1}; // 使用花括号，调用std::initializer_list构造函数
    Widget3 w7(std::move(w1)); // 使用小括号，调用移动构造函数
    Widget3 w8{std::move(w1)}; // 使用花括号，调用std::initializer_list构造函数
  }

  {
    Widget4 w1(10, true); // 使用小括号，调用第一个构造函数
    Widget4 w2{10, true}; // 使用花括号，调用第一个构造函数，因为没有办法把int和bool转换成std::string
    Widget4 w3(10, 5.0);  // 使用小括号，调用第二个构造函数
    Widget4 w4{10, true}; // 使用花括号，调用第二个构造函数
  }

  {
    Widget5 w1;   // 调用默认构造函数
    Widget5 w2{};  // 同上, !!! 注意这个情况
    //Widget5 w3(); // 最令人头疼的解析! 声明一个函数, 这里编译器会警告的
    Widget5 w4({}); // 调用std::initializer_list
    Widget5 w5{{}}; // 调用std::initializer_list
  }
  return 0;
}
