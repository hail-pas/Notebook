#include "thread.h"

#define N 100000000

long sum = 0;

void Tsum() {
  for (int i = 0; i < N; i++) {
    // sum++; // MULTI THREAD SHARE MEMORY PROBLEM
    // asm volatile ( // 依然会有问题，多处理器执行
    //     "incq %0"
    //     : "+m"(sum)
    // );
    // asm volatile ( // lock incq 没问题
    //     "lock incq %0"
    //     : "+m"(sum)
    // );
    sum += 1;
  }
}

int main() {
  create(Tsum);
  create(Tsum);
  join();
  printf("sum = %ld\n", sum);
}