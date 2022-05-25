extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_crit = 0;
int global_x = 0;

// local variables
node_17_next = 14;

// cfas
int node14() {
  sassert(!(global_crit));
  global_crit = 1;
  return 0;
}

int node15() {
  if ((global_x)<(3)) {
    global_x = (global_x)+(1);
    return 1;
  } else {
    global_x = 0;
    return 0;
  }
}

int node16() {
  sassert(global_crit);
  global_crit = 0;
  return 0;
}

int node17() {
  int status;
  if (node_17_next == 14) {
    status = node14();
    if (status == 1) {
      node_17_next = 14;
      return 1;
    }
    if (status == 2) {
      node_17_next = 14;
      return 2;
    }
    node_17_next = 15;
  }

  if (node_17_next == 15) {
    status = node15();
    if (status == 1) {
      node_17_next = 15;
      return 1;
    }
    if (status == 2) {
      node_17_next = 14;
      return 2;
    }
    node_17_next = 16;
  }

  if (node_17_next == 16) {
    status = node16();
    if (status == 1) {
      node_17_next = 16;
      return 1;
    }
    if (status == 2) {
      node_17_next = 14;
      return 2;
    }
  }

  node_17_next = 14;
  return 0;
}

int main(void) {
  while (1) {
    node17();
  }
}

