#include <array>
#include <cassert>
#include <string>
#include <iostream>

// 用auto作为非模板类型参数
// auto c++17
template<typename T, auto Maxsize>
class Stack {
	public:
		using size_type = decltype(Maxsize);
	private:
		std::array<T, Maxsize> elems;
		size_type numElements;
	public:
		Stack();
		void push(const T& elem);
		const T& top() const;
		bool empty() const {
			return numElements == 0;
		}
		size_type size() const {
			return numElements;
		}
		/* c++14 可以通过使用auto让编译器推断出具体的返回类型
		auto size() const {
			return numElements;
		}
	  */

};

template<typename T, auto Maxsize>
Stack<T, Maxsize>::Stack() 
: numElements(0) {
}

template<typename T, auto Maxsize>
void Stack<T, Maxsize>::push(const T& elem) {
	assert(numElements < Maxsize);
	elems[numElements++] = elem;
}

template<typename T, auto Maxsize>
const T& Stack<T, Maxsize>::top() const {
	assert(!elems.empty());
	return elems[numElements - 1];
}

int main() {
	Stack<int, 20u> int20Stack;
	Stack<std::string, 40> stringStack;

	auto size1 = int20Stack.size();
	auto size2 = stringStack.size();
	// c++17
#if __cplusplus >= 201703L
	if (!std::is_same_v<decltype(size1), decltype(size2)>) {
		std::cout << "c++17 size type differ" << "\n";
	}
#else
	if (!std::is_same<decltype(size1), decltype(size2)>::value) {
		std::cout << "c++11 size type differ" << "\n";
	}
#endif
}
