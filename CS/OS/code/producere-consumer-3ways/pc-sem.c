#include "../thread/thread.h"
#include "../thread/thread-sync.h"
#include <semaphore.h>

/**
 * @brief 用於順序、計數型同步； join的實現
 *
 */


/**
 * @brief 并行計算圖，圖傳遞閉包（間接邊替代直接邊）之後的每一條邊都設置一個信號，則能保證拓撲序執行
 *
 */


sem_t fill, empty;

sem_t produced, consumed;

void Tproduce() {
  while (1) {
    P(&empty);
    printf("(");
    V(&fill);
  }
}

void Tconsume() {
  while (1) {
    P(&fill);
    printf(")");
    // 如果這裏也是critical section,  則需要鎖保護不被中斷執行。
    V(&empty);
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  SEM_INIT(&fill, 0);
  SEM_INIT(&empty, atoi(argv[1]));
  for (int i = 0; i < 8; i++) {
    create(Tproduce);
    create(Tconsume);
  }
}