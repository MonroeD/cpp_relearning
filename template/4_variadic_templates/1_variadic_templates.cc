#include <stdio.h>
#include <string>
#include <iostream>

// 4.1 变参模板


// 4.1.1
// Types -> 模板参数包(template parameter pack)
// args -> 函数参数包(function parameter pack)
void print() {}
template<typename T, typename... Types>
void print(T firstArg, Types... args) {
	std::cout << firstArg << '\n';
	print(args...);
}

// 4.1.2 变参模板和非变参模板的重载
// 当两个函数模板的区别只在于尾部的参数包的时候，会优先选择没有尾部参数包的那一个函数模板
template<typename T>
void print_1(T arg) {
	std::cout << arg << '\n';
}

template<typename T, typename... Args>
void print_1(T firstArg, Args... args) {
	print_1(firstArg);
	print_1(args...);
}

// 4.1.3 sizeof... 运算符 (参数包中所包含的参数的数目)
void print_2() {}
template<typename T, typename... Types>
void print_2(T firstArg, Types... args) {
	std::cout << firstArg << '\n';
	std::cout << "remaining types " << sizeof...(Types) << '\n';
	std::cout << "remaining args " << sizeof...(args) << '\n';
	print_2(args...);
}

int main() {
	{
		std::string s("world");
		print(7.5, "hello", s);
		std::cout << '\n';
	}
	{
		std::string s("world");
		print_1(7.5, "hello", s);
		std::cout << '\n';
	}
	{
		std::string s("world");
		print_2(7.5, "hello", s, s);
	}
	return 0;
}
