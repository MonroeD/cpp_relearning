#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void func(int x) {
  printf("func(int)\n");
}

void func(void* x) {
  printf("func(void*)\n");
}

int main() {
  {
    // (1)
    // func(NULL); // 编译失败
    func(nullptr);
  }
  return 0;
}
