#include <stdio.h>
#include <iostream>

int max(int a, int b) {
	printf("max(int, int)\n");
	return b < a ? a : b;
}

template<typename T>
T max(T a, T b) {
	printf("template_max<>\n");
	return b < a ? a : b;
}

/* summary
 * (1) 按值传递还是按引用传递 -> 按值传递更好
 * (2) 为什么不用inline(TODO)
 * (3) 
 * */

int main () {
	// 1.5模板函数重载
	{
	    ::max(7, 42); // 非模板的函数
	    ::max<>(7, 42);
	    ::max(7.0, 42.0);
	    ::max('a', 'b');
	    ::max<double>(7, 42);
	    ::max('a', 42.7); // 非模板的函数
	}
	{
		// 为指针和C字符串重载max模板
	}
	return 0;
}
