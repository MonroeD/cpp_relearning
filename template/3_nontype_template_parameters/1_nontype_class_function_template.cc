#include <stdio.h>

// 3.1 类模板的非类型参数
/*
template <typename T, std::size_t Maxsize>
class Stack {
	...
};
*/

// 3.2 函数模板的非类型参数
template<int Val, typename T>
T addVaule(T x) {
	return x + Val;
}

// or
#if __cplusplus >= 201703L
// 'auto' not allowed in template parameter until C++17
template <auto Val, typename T = decltype(Val)>
T foo() {
	return Val;
}
#endif

template <typename T, T val = T{}>
T bar() {
	return val;
}

int main(void) {
	{
#if __cplusplus >= 201703L
	  foo<10>();
#endif
	}

	{
		bar<int32_t, 1>();
	}
	return 0;
}
