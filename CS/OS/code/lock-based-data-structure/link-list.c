#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;


typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;


void list_init(list_t *L){
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

int list_insert(list_t *l, int key){
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (!new_node) {
        perror("malloc failed");
        return -1;
    }
    new_node->key = key;
    pthread_mutex_lock(&l->lock);
    new_node->next = l->head;
    l->head = new_node;
    pthread_mutex_unlock(&l->lock);
}

int list_lookup(list_t *l, int key){
    int rv = -1;
    pthread_mutex_lock(&l->lock);
    node_t * curr = l->head;
    while (curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    return rv;
}

