#include <pthread.h>
#include "./link-list.c"

#define BUCKETS (101)

typedef struct __hash_t {
    list_t lists[BUCKETS];
} hash_t;

void hash_init(hash_t * h){
    int i;
    for (i = 0 ; i < BUCKETS; i++) {
        list_init(&h->lists[i]);
    }
}

int hash_insert(hash_t *h, int key) {
    return list_insert(&h->lists[key % BUCKETS], key);
}

int hash_lookup(hash_t *h, int key) {
    return list_lookup(&h->lists[key % BUCKETS], key);
}
