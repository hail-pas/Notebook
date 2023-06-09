#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <stdlib.h>

#define NUMCPUS 8

typedef struct __counter_t {
    long global;
    pthread_mutex_t glock;
    int local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int threshold;
} counter_t;

counter_t c = {};

enum {
  T_FREE = 0,
  T_LIVE,
  T_DEAD,
};

typedef struct __thread_t {
    int id, status;
    pthread_t thread;
    void* (*fn)(void *);
    void *args, *ret;
} thread_t;

#define THREADPOOLLENGTH 64

thread_t tpool[THREADPOOLLENGTH], *tptr = tpool;

void* wrapper(void *arg){
    thread_t *thread = (thread_t *)arg;
    return thread->fn(thread->args);
}

int create(void* (*fn)(void *), void *args){
    if (tptr - tpool > THREADPOOLLENGTH) {
        perror("thread pool full");
        return -1;
    }
    *tptr = (thread_t){
        .id = (int)(tptr - tpool + 1),
        .status = T_LIVE,
        .fn = fn,
        .args = args,
        .ret = NULL,
    };
    pthread_create(&tptr->thread, NULL, wrapper, tptr);
    ++tptr;
    return 0;
}

void join(){
    for (int i = 0; i < THREADPOOLLENGTH; i++) {
        thread_t *t = &tpool[i];
        if (t->status == T_LIVE) {
            pthread_join(t->thread, NULL);
            t->status = T_DEAD;
        }
    }
}

__attribute__((destructor)) void cleanup() { join(); }

void init(counter_t *c, int threshold){
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);

    for (int i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(counter_t *c, int thread_id, int value){
    pthread_mutex_lock(&c->llock[thread_id]);
    c->local[thread_id] += value;
    if (c->local[thread_id] > c->threshold) {
        pthread_mutex_lock(&c->glock);
        c->global += c->local[thread_id];
        pthread_mutex_unlock(&c->glock);
        c->local[thread_id] = 0;
    }
    pthread_mutex_unlock(&c->llock[thread_id]);
}

void* add(void *thread_id_ptr){
    // uint64_t tid;
    // pthread_threadid_np(NULL, &tid);
    int thread_id = *((int *)thread_id_ptr);
    for (int i = 0; i < 10000000; i++) {
        update(&c, thread_id, 500);
    }
    if (c.local[thread_id] > 0) {
        pthread_mutex_lock(&c.glock);
        c.global += c.local[thread_id];
        pthread_mutex_unlock(&c.glock);
    }
    return NULL;
}

enum T{
    T0 = 0,
    T1,
    T2,
    T3,
    T4,
    T5,
    T6,
    T7
};

int main(int argc, char *argv[]) {
    init(&c, 20000);
    enum T ts[NUMCPUS] = {
        T0,
        T1,
        T2,
        T3,
        T4,
        T5,
        T6,
        T7
    };
    for (int i = 0; i < 8; i++) {
        create(add, (void *)(&ts[i]));
    }
    join();
    printf("%ld", c.global);
    return 0;
}


