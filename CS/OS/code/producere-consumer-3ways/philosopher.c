#include "../thread/thread.h"
#include "../thread/thread-sync.h"
#include <semaphore.h>
#include <stdio.h>

#define N 5

sem_t table, avail[N];

void Tphilosopher(int id) {
  int lhs = (id + N - 1) % N;
  int rhs = id % N;
  while (1) {
    // Come to table
    P(&table);

    P(&avail[lhs]);
    printf("+ %d by T%d\n", lhs, id);
    P(&avail[rhs]);
    printf("+ %d by T%d\n", rhs, id);

    // Eat

    printf("- %d by T%d\n", lhs, id);
    printf("- %d by T%d\n", rhs, id);
    V(&avail[lhs]);
    V(&avail[rhs]);

    // Leave table
    V(&table);
  }
}

int left_forks(int p) {
  return p;
}

int right_forks(int p) {
  return (p + 1) % 5;
}

void get_forks(int id){
  if (id == 4) {
    sem_wait(&avail[right_forks(id)]);
    sem_wait(&avail[left_forks(id)]);
  } else {
    sem_wait(&avail[left_forks(id)]);
    sem_wait(&avail[right_forks(id)]);
  }
}

void put_forks(int id) {
  sem_post(&avail[left_forks(id)]);
  sem_post(&avail[right_forks(id)]);
}

void Tphilosopherv2(int id){
  while (1) {
    get_forks(id);
    printf("Eating by T%d\n", id);
    put_forks(id);
  }
}

int main() {
  SEM_INIT(&table, N - 1);
  for (int i = 0; i < N; i++) {
    SEM_INIT(&avail[i], 1);
  }
  for (int i = 0; i < N; i++) {
    create(Tphilosopherv2);
  }
}