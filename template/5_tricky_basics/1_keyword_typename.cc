#include <stdio.h>
#include <string>
#include <iostream>

// 5.1 typename 关键字
// 用来澄清模板内部的一个标志符代表的是某种类型，而不是数据成员
template<typename T>
class MyClass {
	public:
		...
		void foo() {
			// 用来表明SubType是定义在class T中的一个类型
			// 如果不加，SubType会被认为成一个成员
			typename T::SubType* ptr;
		}
};

// 5.2 零初始化
// 对于内置类型，最好显示的调用其默认构造函数将它们初始化成0
template<typename T>
void foo() {
	T x{}; // x is zero (or false) if T is a built-in type
				 // {} c++11的语法
}

template<typename T>
class MyClass {
	private:
		T x{};
};

template<typename T>
void foo(T p = T{}) {
}

/*
 * 错误的
template<typename T>
void foo(T p{}) {
}
*/

// 5.3 使用this->
// 作为经验，当使用定义与基类中的、依赖于模板参数的成员时，用
// this->或者Base<T>::来修饰
template<typename T>
class Base {
	public:
		void bar();
};

// Derived 中的bar不会被解析成Base中的bar()，因为会错误，
// 要么用this，要么用Base<T>::bar();
template<typename T>
class Derived : Base<T> {
	public:
		void foo() {
			// bar(); // ERROR calls extern bar() or error
			this->bar();
		}
};

// 5.4 使用裸数组或者字符串常量的模板 TODO
int main() {
	return 0;
}
