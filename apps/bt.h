#ifndef BT
#define BT

typedef enum
{
    SUCCESS,
    RUNNING,
    FAILURE
} return_t;

typedef enum
{
    ACTION,
    SEQUENCE,
    SELECTOR,
    PARALLEL
} type_t;

typedef struct node_t
{
    type_t type;

    // compositional
    struct node_t *children;
    int size;

    // sequence & selector
    int memory; // bool
    int offset;

    // parallel
    int threshold;

    return_t (*func_ptr)(struct node_t *node);
} node_t;

return_t sequence_tick(struct node_t *node) {
    int offset = 0;
    if (node->memory) {
        offset = node->offset;
    }
    int i = 0;
    for (i = 0 + offset; i < node->size; i = i + 1) {
        return_t result = node->children[i].func_ptr(&node->children[i]);
        if (node->memory) {
            if (result == RUNNING) {
                node->offset = i;
                return RUNNING;
            }
            if (result == FAILURE) {
                node->offset = 0;
                return FAILURE;
            }
        } else {
            if (result == RUNNING || result == FAILURE) {
                return result;
            }
        }
    }
    if (node->memory) {
        node->offset = 0;
    }
    return SUCCESS;
}

return_t selector_tick(struct node_t *node) {
    int offset = 0;
    if (node->memory) {
        offset = node->offset;
    }
    int i = 0;
    for (i = 0 + offset; i < node->size; i = i + 1) {
        return_t result = node->children[i].func_ptr(&node->children[i]);
        if (node->memory) {
            if (result == RUNNING) {
                node->offset = i;
                return RUNNING;
            }
            if (result == SUCCESS) {
                node->offset = 0;
                return SUCCESS;
            }
        } else {
            if (result == RUNNING || result == SUCCESS) {
                return result;
            }
        }
    }
    if (node->memory) {
        node->offset = 0;
    }
    return FAILURE;
}

#endif // BT