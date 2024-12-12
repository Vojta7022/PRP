#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

queue_t *create_queue(int capacity)
{
    queue_t *queue = my_malloc(sizeof(queue_t));
    queue->capacity = capacity;
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;
    queue->elems = my_malloc(capacity * sizeof(void *));
    return queue;
}

void delete_queue(queue_t *queue)
{
    free(queue->elems);
    queue->elems = NULL;
    free(queue);
}

bool push_to_queue(queue_t *queue, void *data)
{
    if (queue->size >= queue->capacity)
    {
        void **new_elems = my_malloc(queue->capacity*2 * sizeof(void *));
        for (int i = 0; i < queue->size; i++)
        {
            new_elems[i] = queue->elems[(queue->head + i) % queue->capacity];
        }
        queue->capacity *= 2;
        free(queue->elems);
        queue->elems = new_elems;
        queue->head = 0;
        queue->tail = queue->size;
    }
    queue->size++;
    queue->elems[queue->tail] = data;
    queue->tail = (queue->tail + 1) % queue->capacity;
    return true;
}

void *pop_from_queue(queue_t *queue)
{
    if (queue->size == 0)
    {
        return NULL;
    }
    void *elem = queue->elems[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;

    if (queue->size < queue->capacity / 3)
    {
        void **new_elems = my_malloc(queue->capacity / 3 * sizeof(void *));
        for (int i = 0; i < queue->size; i++)
        {
            new_elems[i] = queue->elems[(queue->head + i) % queue->capacity];
        }
        queue->capacity /= 3;
        free(queue->elems);
        queue->elems = new_elems;
        queue->head = 0;
        queue->tail = queue->size;
    }

    return elem;
}

void *get_from_queue(queue_t *queue, int idx)
{
    if (idx < 0 || idx >= queue->size)
    {
        return NULL;
    }
    return queue->elems[(queue->head + idx) % queue->capacity];
}

int get_queue_size(queue_t *queue)
{
    return queue->size;
}

void *my_malloc(size_t size)
{
    void *ret = malloc(size);
    if (!ret)
    {
        fprintf(stderr, "Error: Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}
