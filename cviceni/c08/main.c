#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define ERROR_MALLOC 100

#define ERROR_POP -1

typedef struct node_t {
    int value;
    struct node_t *next;
} node_t;

typedef struct queue_t {
    size_t size;
    node_t *head;
} queue_t;

bool push(queue_t *q, int value);
int pop(queue_t *q);
bool is_empty(queue_t *q);

int main(int argc, char *argv[]) {
    int ret = EXIT_SUCCESS;

    node_t n1 = {0, NULL};
    node_t n2 = {1, NULL};

    n1.next = &n2;

    return ret;
}

bool is_empty(queue_t *q) {
    return q->size == 0;
    // return q->head == NULL;
}

bool push(queue_t *q, int value) {
    bool ret = true;

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node)
    {
        if (is_empty(q))
        {
            q->head = new_node;
        }
        else
        {
            node_t *tmp = q->head;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new_node;
        }
        q->size++;
    }
    else
    {
        fprintf(stderr, "Error: Failed to allocate memory!\n");
        ret = false;
    }
    
    return ret;
}

int pop(queue_t *q) {
    int ret = ERROR_POP;

    if (is_empty(q)) {
        q->head
    }
}
