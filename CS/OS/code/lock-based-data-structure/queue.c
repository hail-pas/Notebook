#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;


typedef struct __queue_t {
    node_t *head, *tail;
    pthread_mutex_t head_lock, tail_lock;
} queue_t;

int queue_init(queue_t *q){
    node_t *dummy = malloc(sizeof(node_t));
    dummy->next = NULL;
    q->head = q->tail = dummy;
    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);
}

void enqueue(queue_t *q, int value){
    node_t *temp = malloc(sizeof(node_t));
    temp->key = value;
    temp->next = NULL;
    pthread_mutex_lock(&q->tail_lock);
    q->tail->next = temp;
    q->tail = temp;
    pthread_mutex_lock(&q->tail_lock);
}

int dequeue(queue_t * q, int * value) {
    pthread_mutex_lock(&q->head_lock);
    node_t *temp = q->head;
    node_t *new_head = temp->next;
    if (new_head == NULL) {
        pthread_mutex_unlock(&q->head_lock);
        return -1;
    }
    *value = temp->key;
    q->head = new_head;
    pthread_mutex_unlock(&q->head_lock);
    free(temp);
    return 0;
}
