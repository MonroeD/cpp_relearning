#include <stdio.h>
#include <string>
#include <iostream>
#include <deque>

// 5.5 成员模板 是个好的考题

// 当两个stack类型相同的时候才可以相互赋值
//Stack<int> s1, s2;
//Stack<float> s3;
//s2 = s1; // right
//s3 = s1; // wrong

// 但是只要将赋值运算符定义成模板，就可以将两个元素类型可以做成转换的stack相互赋值

template<typename T>
class Stack {
	private:
		std::deque<T> elems;
	public:
		void push(const T& elem) {
			elems.push(elem);
		}

		void pop() {
			elems.pop_front();
		}

		const T& top() const {
			return elems.front();
		}

		bool empty() const {
			return elems.empty();
		}

		// assign stack of elements of type T2
		template<typename T2>
		Stack& operator = (const Stack<T2>&);

		// to get access to private members of Stack<T2> for any type T2
		template<typename> friend class Stack;
};

// 这个语法
template<typename T>
template<typename T2>
Stack<T>& Stack<T>::operator= (const Stack<T2>& op2) {
#if 1
	Stack<T2> tmp(op2);
	elems.clear();
	while (!tmp.empty()) {
		elems.push_front(tmp.top());
		tmp.pop();
	}
	return *this;
#else
	elems.clear();
	elems.insert(elems.begin(),
			op2.elems.begin(),
			op2.elems.end());
	return *this;
#endif
}

// 成员函数模板的特例化

class BoolString {
	private:
		std::string value;
	public:
		BoolString(const std::string& s) : value(s) {};

		template<typename T = std::string>
		T get() const {
			return value;
		}
};

template<>
inline bool BoolString::get<bool>() const {
	return value == "true" || value == "1" || value == "on";
}

int main() {
	{
	  Stack<int> s1;
	  Stack<float> s2;
	  s2 = s1;

	  Stack<std::string> s3;
	  // s2 = s3; // 会进行类型检查
	}

	{
		BoolString s1("hello");
		std::cout << s1.get() << '\n';
		std::cout << s1.get<bool>() << '\n';
	}
	return 0;
}

