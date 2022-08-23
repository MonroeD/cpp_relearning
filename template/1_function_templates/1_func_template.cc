#include <stdio.h>
#include <iostream>

template <typename T>
void void_func(T* a) {
	std::cout << a << std::endl;
}

template <typename T>
T my_max(T a, T b) {
	return a > b ? a : b;
}

template <typename T>
void default_func(T a = "") {
}

template <typename T = std::string>
void right_default_func(T a = "") {
}

int main() {
	{
		// (1) void作为模板参数也是有效的
	    int a = 10;
	    void* p = &a;
	    void_func(p);
	}

	{
		// (2) 如果调用参数是按引用传递的，任何类型装换都是不可以的
		// (2) 调用参数是按值传递的，那么只能退化(decay)，const和volatile限制符会被忽略，引用会转换成被引用的类型
		// raw array and function 被转换为相应的指针
		const int c = 42;
		int i = 1;
		my_max(i, c); // T -> int c中的const被decay掉
		my_max(c, c); // T -> int
		int& ir = i;
		my_max(i, ir); // T -> int, ir中的引用被decay掉了
		int arr[4];
		my_max(&i, arr); // T -> int*
	}

	{
		// (3) 默认参数的类型判断
		default_func(1); // OK T -> int
		//default_func(); // ERROR 无法判断T的类型
		right_default_func(); // OK 给模板参数声明一个默认参数
	}
	return 0;
}
