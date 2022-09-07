#include <stdio.h>
#include <string>
#include <iostream>
#include <deque>
#include <array>
#include <vector>

// 5.7模板参数模板
// 对于之前的stack模板，必须同时指定
/*
Stack<int, std::vector<int>> vStack;
如果使用参数模板可以
Stack<int, std::vector> vStack;
*/

// TODO wrong
template<typename T,
template<typename Elem> class Cont = std::deque>
class Stack {
  private:
    Cont<T> elems;
  public:
    void push(const T& elem);
    void pop();
    const T& top() const;
};

int main() {
  Stack<int, std::vector> vStack;
  return 0;
}
