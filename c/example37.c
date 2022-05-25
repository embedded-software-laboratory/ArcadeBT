extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_i = 0;
int global_c = 0;

// local variables
node_182_next = 177;

// cfas
int node177() {
  global_i = 0;
  global_c = 0;
  return 0;
}

int node178() {
  if ((global_i)<(1000)) {
    return 2;
  } else {
    return 0;
  }
}

int node179() {
  global_c = (global_c)+(global_i);
  global_i = (global_i)+(1);
  return 1;
}

int node181() {
  int status;
  status = node178();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node179();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node180() {
  sassert((global_c)>=(0));
  return 0;
}

int node182() {
  int status;
  if (node_182_next == 177) {
    status = node177();
    if (status == 1) {
      node_182_next = 177;
      return 1;
    }
    if (status == 2) {
      node_182_next = 177;
      return 2;
    }
    node_182_next = 181;
  }

  if (node_182_next == 181) {
    status = node181();
    if (status == 1) {
      node_182_next = 181;
      return 1;
    }
    if (status == 2) {
      node_182_next = 177;
      return 2;
    }
    node_182_next = 180;
  }

  if (node_182_next == 180) {
    status = node180();
    if (status == 1) {
      node_182_next = 180;
      return 1;
    }
    if (status == 2) {
      node_182_next = 177;
      return 2;
    }
  }

  node_182_next = 177;
  return 0;
}

int main(void) {
  while (1) {
    node182();
  }
}

