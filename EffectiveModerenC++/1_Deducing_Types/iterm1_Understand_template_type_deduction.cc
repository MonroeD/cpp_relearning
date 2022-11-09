#include <iostream>
#include <cstddef>
#include <type_traits>

/*
template<typename T>
void func(ParamType param) {
}

ParamType有三种情况
1. ParamType是一个指针或引用，但不是通用引用
2. ParamType是一个通用引用
3. ParamType既不是指针也不是引用
f(expr),在编译期间，编译器使用了expr进行了两个类型推导，一个是T，一个是ParamType，这两个通常是不一样的，因为ParamType包括了const和引用的修饰
 * */

/* 1. 如果expr是一个引用，忽略引用部分
 * 2. 然后剩下的部分决定T，然后T与形参匹配得出最终的ParamType
 * */
template<typename T>
void func_v1(T& param) {
}

template<typename T>
void func_v1_const(const T& param) {
}

/* 1. 如果expr是左值，T和ParamType都会被推导为左值引用, 这是模板类型推导中唯一一种T和ParamType被推导为引用的情况
 *    虽然ParamType被声明为右值引用类型，但最后推导的结果它是左值引用
 * 2. 如果expr是右值，就情况一的推导规则
 * */
template<typename T>
void func_v2(T&& param) {
}

template<typename T>
void func_v2_const(const T&& param) {
}

/* 1. 如果expr的类型是一个引用，忽略这个引用部分
 * 2. 如果忽略引用之后的expr是一个const，就再忽略const，如果它是volatile，也会被忽略(volatile不常用, 常用于驱动开发)
 * */
template<typename T>
void func_v3(T param) {   // 以传值的方式处理param
  std::cout << std::is_const<decltype(param)>::value << "\n"; // 会打印0
}

/*
 * TODO func_v3_const应该的确是一个const参数，但是nm查看的函数声明却不是const，这有点让人吃惊！！！
 * */
template<typename T>
void func_v3_const(const T param) {
  std::cout << std::is_const<decltype(param)>::value << "\n"; // 会打印1
}

// 有趣的是，对模板函数声明为一个指向数组的引用使得我们可以在模板函数中推导出数组的大小
//在编译期间返回一个数组大小的常量值，数组形参没有名字，因为我们只关心数字的大小
template<typename T, std::size_t N>
constexpr std::size_t array_size(T (&)[N]) noexcept {
  return N;
}
 

void some_func(int x, double y) {
}

template<typename T>
void func_v4(T param) {
}

template<typename T>
void func_v5(T& param) {
}

int main() {

  // 情况一：ParamType是一个指针或引用但不是通用引用
  {
    int x = 27;
    const int cx = x;
    const int& rx = cx;
    int* px = &x;

    func_v1(x);   // T是int, param是int&
    func_v1(cx);  // T是const int, param是const int&
    func_v1(rx);  // T是const int, param是const int&
    func_v1(px);  // T是int*, param是int*&

    /* (1) 当他们传递一个const对象给一个引用类型的参数时，他们传递的对象保留了常量性
     * 这也是为什么向T&传递const对象是安全的，对象T的常量性会被保留为T的一部分
     *
     * (2) 注意即使rx的类型是一个引用，T也会被推导为一个非引用, 也就是上面的1.所描述的
     */

    {
      func_v1_const(x);  // T是int, param是const int&
      func_v1_const(cx); // T是int, param是const int&
      func_v1_const(rx); // T是int, param是const int&
      func_v1_const(px); // T是int*, param是const int*&
    }
  }

  // 情况二：ParamType是一个通用引用
  {
    // T&&就是通用引用
    int x = 27;
    const int cx = x;
    const int& rx = cx;
    int* p = &x;

    func_v2(x);   // x是左值，所以T是int&, param也是int&
    func_v2(cx);  // cx是左值，T是const int&, param也是const int&
    func_v2(rx);  // rx是左值，所以T也是const int&, param也是const int&
    func_v2(27); // 27是右值，所以T是int, param类型就是int&&
    func_v2(p);    // p是左值，所以T是int*, param类型是int*&
    
    {
      func_v2_const(27); // 只有27这个可以编译过
    }
  }

  // 情况三: ParamType既不是指针也不是引用
  {
    int x = 27;
    const int cx = x;
    const int& rx = cx;

    func_v3(x);   // T和param都是int
    func_v3(cx);  // T和param都是int
    func_v3(rx);  // T和param都是int

    {
      func_v3_const(x); // T是int, param是const int
      func_v3_const(cx); // T是int, param是const int
      func_v3_const(rx); // T是int, param是const int
    }
    
    /* 注意到即使cx和rx表示const值，param也不是const, 这是有意义的。param是一个拷贝自cx和rx且独立存在的完整对象
     * ，具有常量性的cx和rx不可修改并不代表param也是一样。这个也就是为什么expr的常量性或易变性在类型推导时会被忽略，
     * 因为expr不可修改并不意味着他的拷贝也不能被修改
     * */

    // 右边的const代表ptr是一个常量，不能再指向其他值了
    const char* const ptr = "hello world\n";
    // 其const会被忽略，因此param也是const char*
    func_v3(ptr);
  }

   // 数组实参
  {
    const char name[] = "Effective.Modern.C++\n";
    // 由于数组形参会视作指针形参，所以传给形参的一个数组类型会推导为一个指针类型
    func_v3(name);
    // 虽然函数不能接受一个真正的数组(TODO)，但是可以接受指向数组的引用, 语法有毒
    func_v1(name); // func_v1<char const [22]>(char const (&) [22])
                   //
    int keys[] = {1, 3, 5, 6};
    int values[array_size(keys)];
  }

  // 函数实参
  {
    // c++中不止数组会退化成指针，函数类型也会退化成一个函数指针
    func_v4(some_func);  // param被推导为指向函数的指针，类型是void(*)(int, double)
    func_v5(some_func);  // param被推导为指向函数的指针，类型是void(&)(int, double)
  }

  return 0;
}
