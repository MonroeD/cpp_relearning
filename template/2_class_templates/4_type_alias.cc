#include <vector>
#include <deque>

// 2.7 默认类模板参数
template<typename T, typename Cont = std::vector<T>>
class Stack {
	private:
		Cont elems;
	public:
		void push(const T& elem);
		const T& top() const;
};

// 每个成员函数的定义也应该包含两个模板参数
template<typename T, typename Cont>
void Stack<T, Cont>::push(const T& elem) {
	elems.push_back(elem);
};

template<typename T, typename Cont>
const T& Stack<T, Cont>::top() const {
	return elems.back();
}

// 2.8 类型别名(Type Aliases)

#if 0
typedef Stack<int> IntStack;
#else
using IntStack = Stack<int>; // c++11推荐的方式
#endif

// Alias Templates (别名模板)
template <typename T>
using DequeStack = Stack<T, std::deque<T>>;

// Alias Templates for Member Types (class成员的别名模板)
/*
struct MyType {
	using iterator = ...;
};

之后可以下面这样定义
template<typename T>
using MyTypeIterator = typename MyType<T>::iterator;
*/

int main() {
	{
	    Stack<int> ss;
			ss.push(13);
			auto xx = ss.top();
	}
	return 0;
}
