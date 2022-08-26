#include <vector>
#include <stdio.h>
#include <string>

template<typename T>
class Stack {
	private:
		std::vector<T> elems;
	public:
		Stack() = default;

		// (1)
		//Stack(const T& elem)
		//: elems({elem}) {
		//};

		// (2) 去掉引用
		//Stack(const T elem)
		//: elems({elem}) {
		//};

		// (3) 最好将临时变量elem move到stack中，避免不必要的拷贝
		Stack(T elem) 
		: elems ({std::move(elem)}){
		}

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

Stack(const char*) -> Stack<std::string>;

int main() {
	// 2.9 类模板的类型推导
	// 直到c++17前，使用类模板都必须显示指出所有的模板参数的类型(除非他们有默认值)
#if __cplusplus >= 201703L
	Stack xx = 0; // 推导成Stack<in>
#else
	Stack<int> xx = 0;
#endif

#if __cplusplus >= 201703L
	// 对字符串常量参数的类型判断
	Stack stringStack = "bottom";
	// 如果构造函数是按照引用传递的时候，参数类型不会被decay
	// 也就是说一个裸的数组类型不会被转换成裸指针，这样就相当于
	// Stack<const char[7]>, 是会编译失败的（因为目前的实现，char[7]有些不支持）
	// 也不能继续push一个不同维度的字符串常量了
	
	// 所以基于上诉考虑，我们将构造函数声明成按值传递参数的形式(见上)
#endif

	{
	    //Stack stringStack = {"bottom"}; // 得加双引号才行
	}
}

// 推断指引 Deduction Guides

