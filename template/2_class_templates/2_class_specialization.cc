#include <stdio.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <deque>

template <typename T>
class Stack {
	private:
		std::vector<T> elems;
	public:
		void push(const T& elem);
		const T& top() const;
};

// 2.5 模板特例化
// 所有出现T的地方都需要替换成特例化模板的类型

template<>
class Stack<std::string> {
	private:
		std::deque<std::string> elems;
	public:
		void push(const std::string& elem);
		const std::string& top() const;
};

void Stack<std::string>::push(const std::string& elem) {
	elems.push_back(elem);
}

int main() {
}
