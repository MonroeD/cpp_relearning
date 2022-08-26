#include <stdio.h>
#include <iostream>
#include <string>
#include <deque>
#include <vector>

template<typename T>
class Stack {
	private:
		std::vector<T> elems;
	public:
		void push(const T& elem);
		const T& top() const;
};

template<typename T>
void Stack<T>::push(const T& elem) {
	elems.push_back(elem);
}

template<typename T>
const T& Stack<T>::top() const {
	assert(!elems.empty());
	return elems.back();
};

// 2.5 模板类的特例化
// 注意特例化和实例化的区别和语法
// 特例化是template<> func<T> {...}
// 实例化是template func<T>();
template<>
class Stack<std::string> {
	private:
		std::deque<std::string> elems; // 说明了特例化可以有很大不同
	public:
		void push(const std::string&);
		const std::string& top() const;
};

void Stack<std::string>::push(const std::string& elem) {
	elems.push_back(elem);
}

const std::string& Stack<std::string>::top() const{
	// TODO 判断empty
	return elems.back();
}

// 2.6 部分特例化
// 特例化的接口可以不同, 貌似2.5节特例化的也可以接口不同
template <typename T>
class Stack<T*> {
	private:
		std::vector<T*> elems;
	public:
		void push(T*);
		T* top() const;
};

template<typename T>
void Stack<T*>::push(T* elem) {
	elems.push_back(elem);
}

template<typename T>
T* Stack<T*>::top() const {
	return elems.back();
}

// 多模板参数的部分特例化
/*
template<typename T1, typename T2>
class MyClass {
	...
};

// 如下特例化
template<typename T>
class MyClass<T, T> {
	...
};

template<typename T>
class MyClass<T, int> {
	...
};

template<typename T1, typename T2>
class MyClass<T1*, T2*> {
};
等等
*/

int main() {
	{
	   Stack<std::string> ss;
	   ss.push("hello world\n");
	   ss.top();
	}
	return 0;
}
