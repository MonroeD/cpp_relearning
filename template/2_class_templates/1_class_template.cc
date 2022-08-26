#include <stdio.h>
#include <iostream>
#include <vector>
#include <cassert>

template <typename T>
class Stack {
	private:
		std::vector<T> elems;
	public:
		//Stack(const Stack&);              // (1)可以不带T
		//Stack& operator = (const Stack&);
		void push(const T& elem);
		//void pop();
		const T& top() const;

		// (5) 友元 TODO
		friend void print(const Stack<T>& s) {	
			for (const auto& val : s.elems) {
				std::cout << val << " ";
			}
			std::cout << std::endl;
		}
};

// (2) 但如果在外面就需要这样定义
template<typename T>
bool operator == (const Stack<T>& lhs, const Stack<T>& rhs) {
	return false; // 未实现
}

// (3) 成员函数的实现
template <typename T>
void Stack<T>::push(const T& elem) {
	elems.push_back(elem);
}

template <typename T>
const T& Stack<T>::top() const {
	assert(!elems.empty());
	return elems.back();
};

int main() {
	// 2.1
	{
	    Stack<int> s;
        // (4) 模板函数和模板成员函数只有在被调用的时候才会实例化
		// 意味着可以用nm工具看符号表会发现没有top函数
	    s.push(10); 
	}

	// 2.2 友元
	{
		Stack<int> s;
		s.push(10);
		s.push(20);
		print(s);
	}
	return 0;
}
