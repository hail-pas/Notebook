#include "thread.h"
#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>

#define N 100000000

long sum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


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
    int rc = pthread_mutex_lock(&lock);
    assert(rc == 0);
    sum += 1;
    pthread_mutex_unlock(&lock);
  }
}

int main() {
  create(Tsum);
  create(Tsum);
  join();
  printf("sum = %ld\n", sum);
}