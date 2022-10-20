#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

int main(void) {
  {
    // (1) auto 避免初始化
    int x; // 未初始化
    //auto y; // 会报错
    auto y = 0;
  }

  {
#if 0
    // (2) auto 省略冗长的声明类型
    ...
    typename std::iterator<It>::value_type t = b;
    auto t = b;
    ...
#endif
  }

  {
#if 0
    // (3) 直接产生闭包，lambda表达式
    // 使用std::function比auto会消耗更多的内存，并且通过具体的实现可得知std::function调用一个闭包会比auto对象要慢
    auto f = [] {
    };
#endif
  }

  {
    // (4) 类型依赖问题
    std::vector<int> v;
    unsigned sz = v.size();
    // 在 windows-32bit std::vector<int>::size_type and unsigned -> 32bit
    // 在 windows-64bit std::vector<int>::size_type 是64 bit , unsigned -> 32bit
    
    // 因为用auto解决更好
    auto szz = v.size();
  }

  {
    // TODO
    std::unordered_map<std::string, int> m = {{"ni", 1}, {"hao", 2}};
    //for (std::pair<std::string, int>& p : m) {
    for (auto& p : m) {
      p.second = 100;
    }
    for (const std::pair<std::string, int>& p : m) {
      std::cout << p.first << " : " << p.second << "\n";
    }
  }

  // 最后，使用auto是建议，不是必须

  return 0;
}
