#include "../thread/thread.h"
#include "../thread/thread-sync.h"

// 睡眠喚醒解決自旋
// 互斥鎖 + 條件 + 手動喚醒

int n, count = 0;
mutex_t lk = MUTEX_INIT();
cond_t cv = COND_INIT();

#define CAN_PRODUCE (count < n)
#define CAN_CONSUME (count > 0)

void Tproduce() {
  while (1) {
    mutex_lock(&lk);
    while (!CAN_PRODUCE) {  // if 會導致即使條件不滿足依然往下執行
    // WAIT_UNTIL(cond) with (mutex) { work(); }
    /**
        lock(MUTEX)
        while(!COND){
            wait(CV, MUTEX);
        }
        unlock(MUTEX)
     *
     */
      cond_wait(&cv, &lk);
    }
    printf("("); count++;
    cond_broadcast(&cv);
    mutex_unlock(&lk);
  }
}

void Tconsume() {
  while (1) {
    mutex_lock(&lk);
    while (!CAN_CONSUME) {
      cond_wait(&cv, &lk);
    }
    printf(")"); count--;
    cond_broadcast(&cv);
    mutex_unlock(&lk);
  }
}


int main(int argc, char *argv[]) {
  assert(argc == 3);
  n = atoi(argv[1]);
  int T = atoi(argv[2]);
  setbuf(stdout, NULL);
  for (int i = 0; i < T; i++) {
    create(Tproduce);
    create(Tconsume);
  }
}