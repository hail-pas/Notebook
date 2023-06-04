// 互斥鎖
// 上鎖成功也需要進入系統内核
// slow path不會浪費cpu資源；fast path 也慢
#include "thread.h"
#include "thread-sync.h"

mutex_t lock = MUTEX_INIT();

long sum = 0;

void Tsum() {
  mutex_lock(&lock);
  sum++;
  mutex_unlock(&lock);
}

int main() {
  create(Tsum);
  create(Tsum);
  join();
  printf("sum = %ld\n", sum);
}
