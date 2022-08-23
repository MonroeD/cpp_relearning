#include <stdio.h>
#include <iostream>
#include <type_traits>

// c++14
#if __cplusplus >= 201402L
template <typename T1, typename T2>
auto max(T1 a, T2 b) {
	return b < a ? a : b;
}

// common_type
//template <typename T1, typename T2>
//std::common_type_t<T1, T2> max(T1 a, T2 b) {
//	return b < a ? a : b;
//}
#else
// c++11 trailing return type 尾置返回类型

// (1) 第一版
// template <typename T1, typename T2>
// auto max(T1 a, T2 b) -> decltype(b < a ? a : b) {
// 	return b < a ? a : b;
// }

// (2) 实际上用true就够了
//template <typename T1, typename T2>
//auto max(T1 a, T2 b) -> decltype(true ? a : b) {
//	return b < a ? a : b;
//}

// (3) T可能是引用类型，返回类型也就判断尾引用类型了
// 所以应该返回的是decay后的T(但其实目前测试貌似没这个问题。。。)
//template <typename T1, typename T2>
//auto max(T1 a, T2 b) -> typename std::decay<decltype(true ? a : b)>::type {
//	return b < a ? a : b;
//}

// (4) 用common_type
template <typename T1, typename T2>
auto max(T1 a, T2 b) -> typename std::common_type<T1, T2>::type {
	return b < a ? a : b;
}
#endif

int main() {
	{
		// 1.3.1 返回类型的判断
		auto x = max(1, 1.5);
		std::cout << x << std::endl;
	}
	{
		// 小知识点
		int i = 42;
		int& j = i;
		auto a = j; // auto变量其类型总是退化之后的类型, auto这里就相当于int
		a = 50;
		std::cout << i << std::endl; // 还是42
	}
	{
		// common_type, std::common_type<>的结果也是decay的
		std::cout << max(4, 7.2) << std::endl;
		std::cout << max(7, 4.2) << std::endl;
	}

	return 0;
}
