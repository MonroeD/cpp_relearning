#include <stdio.h>
#include <string>

// 3.3 非类型模板参数的限制
/*通常它们只能是整形变量(包含枚举)
 * 指向objects/functions/members的指针，
 * objects或者functions的左值引用
 * 或者std::nullptr_t
 * */

//
// 浮点型数值或者class类型的对象都不能作为非类型参数模板使用
/*
template <double VAT>  
double process(double v) {
	return v * VAT;
}

template <std::string name>
class MyClass {
};
*/

// 非类型模板参数可以是任何编译器表达式
template<int I, bool B>
void func() {
}

int main() {
	func<sizeof(int) + 4, sizeof(int) == 4>();
  // 在表达式使用了 > , 就需要将表达式放在括号里，否则识别错误
	func<sizeof(int) + 4, (sizeof(int) > 4)>();
	return 0;
}
