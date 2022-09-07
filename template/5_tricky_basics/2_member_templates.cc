#include <stdio.h>
#include <string>
#include <iostream>
#include <deque>
#include <vector>

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
			elems.push_back(elem);
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
    // TODO 不加可以么
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

// 5.5.1 template的使用
// 再调用成员模板的时候需要显示地指定其模板参数的类型，
// 这时候就需要使用template来确保符号< 会被理解为参数列表的开始，
// 而不是一个比较符

// 这里需要加.template，类似的还有->template 和 ::template
template<unsigned long N>
void printBitset(const std::bitset<N>& bs) {
  std::cout << bs.template to_string<char,
  std::char_traits<char>,
  std::allocator<char>>();
}

// 5.5.2 泛型lambdas和成员模板

#if __cpluscplus >= 201402L
auto f = [] (auto x, auto y) {
  return x + y;
};

// 编译器会默认为它构造下面一个类（如何通过nm工具查看呢）
class SomeCompilerSpecificName {
  public:
    SomeCompilerSpecificName();
    template<typename T1, typename T2>
    auto operator() (T1 x, T2 y) const {
      return x + y;
    }
};
#endif

// 同时也可以将内部的容器类型参数化
template<typename T, typename Cont = std::deque<T>>
class StackV2 {
  private:
    Cont elems;
   public:
		void push(const T& elem) {
			elems.push_back(elem);
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
    template<typename T2, typename Cont2>
    StackV2& operator= (const StackV2<T2, Cont2>&);

    template<typename, typename> friend class StackV2;
};

template<typename T, typename Cont>
template<typename T2, typename Cont2>
StackV2<T, Cont>& StackV2<T, Cont>::operator= (const StackV2<T2, Cont2>& op2) {
  elems.clear();
  elems.insert(elems.begin(),
      op2.elems.begin(),
      op2.elems.end());
  return *this;
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

  {
#if __cpluscplus >= 201402L
    f(3, 5.6);
#endif
  }

  {
    StackV2<int, std::deque<int>> vStack;
    vStack.push(42);
  }
	return 0;
}

