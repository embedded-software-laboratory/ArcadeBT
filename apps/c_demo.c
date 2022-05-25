#include <stdio.h>
#include "bt.h"



// return_t action1_tick(struct node_t *node) {
//     printf("tick action 1\n");
//     return SUCCESS;
// }

// return_t action2_tick(struct node_t *node) {
//     printf("tick action 2\n");
//     return RUNNING;
// }

// int main() {
//     printf("start\n");

//     struct node_t action1;
//     action1.type = ACTION;
//     action1.func_ptr = &action1_tick;

//     struct node_t action2;
//     action2.type = ACTION;
//     action2.func_ptr = &action2_tick;

//     struct node_t sequence;
//     sequence.type = SEQUENCE;
//     sequence.func_ptr = &sequence_tick;
//     sequence.memory = 1;
//     struct node_t children[2] = {action1, action2};
//     sequence.children = children;
//     sequence.size = 2;

//     int i = 0;
//     for (i = 0; i < 2; ++i) {
//         sequence.func_ptr(&sequence);
//     }


//     printf("ende\n");
// }


int global_x = 0;

return_t cfa1(struct node_t *node) {
//   sassert(((global_x)==(0))||((global_x)==(10)));
  if ((global_x)==(1)) {
    return FAILURE;
  } else {
    if ((global_x)==(10)) {
      global_x = 0;
      return SUCCESS;
    } else {
      return FAILURE;
    }
  }
}

return_t cfa2(struct node_t *node) {
  if ((global_x)<(10)) {
    global_x = (global_x)+(1);
    return RUNNING;
  } else {
    return SUCCESS;
  }
}


int main(void) {
  struct node_t node1;
  node1.type = ACTION;
  node1.func_ptr = &cfa1;

  struct node_t node2;
  node2.type = ACTION;
  node2.func_ptr = &cfa2;

  struct node_t node0;
  node0.type = SELECTOR;
  node0.func_ptr = &sequence_tick;
  node0.memory = 1;
  struct node_t node0_children[2] = {node1, node2};
  node0.children = node0_children;
  node0.size = 2;

  while (1) {
    node0.func_ptr(&node0);
  }
}