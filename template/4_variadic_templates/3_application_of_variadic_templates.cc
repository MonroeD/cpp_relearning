#include <stdio.h>
#include <string>
#include <iostream>

// 4.3 变参模板的使用
// 一个重要作用是转发任意类型和数量的参数
// 通常使用移动语义对参数进行完美转发(perfectly forwarded)
auto sp = std::make_shared<>(std::complex<float>)(4.2, 7.2);
std::thread t(foo, 42, "hello");
std::vector<Custom> v;
v.emplace_back("Tim", "John", 1962);

namespace std {

	// shared_ptr
	template<typename T, typename... Args> shared_pte<T>
	make_shared(Args&&... args)

	// thread
	class Thread {
		public:
			template<typename F, typename... Args>
			explicit thread(F&& f, Args&&... args);
			...
	};

	// vector
	class vector {
		public:
			template<typename... Args>
			reference emplace_back(Args&&... args);
			...
	};
}


// 如果参数按值传递，参数会被拷贝；
// 如果按照引用传递，参数会是实参的引用，且类型不会退化
// args are copied with decayed types
template<typename... Args> void foo(Args... args);

// args are nodecayed references to passed objects
template<typename... Args> void foo(const Args&... args);

// 4.4 变参表达式... TODO
int main() {
	return 0;
}
