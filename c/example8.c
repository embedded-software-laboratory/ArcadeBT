extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 0;

// local variables
node_28_next = 26;

// cfas
int node26() {
  sassert(((global_x)==(0))||((global_x)==(10)));
  if ((global_x)==(1)) {
    return 2;
  } else {
    if ((global_x)==(10)) {
      global_x = 0;
      return 0;
    } else {
      return 2;
    }
  }
}

int node27() {
  if ((global_x)<(10)) {
    global_x = (global_x)+(1);
    return 1;
  } else {
    return 0;
  }
}

int node28() {
  int status;
  if (node_28_next == 26) {
    status = node26();
    if (status == 1) {
      node_28_next = 26;
      return 1;
    }
    if (status == 0) {
      node_28_next = 26;
      return 0;
    }
    node_28_next = 27;
  }

  if (node_28_next == 27) {
    status = node27();
    if (status == 1) {
      node_28_next = 27;
      return 1;
    }
    if (status == 0) {
      node_28_next = 26;
      return 0;
    }
  }

  node_28_next = 26;
  return 2;
}

int main(void) {
  while (1) {
    node28();
  }
}

