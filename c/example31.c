extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_fd = 0;
int global_f = 0;
int global_i = 0;
int global_a = 0;
int global_b = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_146_next = 141;

// cfas
int node141() {
  global_i = 0;
  global_a = 0;
  global_b = 0;
  global_n = nd();
  if ((global_n)>=(0)) {
    return 0;
  } else {
    return 2;
  }
}

int node142() {
  if ((global_i)<(global_n)) {
    return 2;
  } else {
    return 0;
  }
}

int node143() {
  global_f = nd();
  if (global_f) {
    global_a = (global_a)+(1);
    global_b = (global_b)+(2);
  } else {
    global_a = (global_a)+(2);
    global_b = (global_b)+(1);
  }
}

int node145() {
  int status;
  status = node142();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node143();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node144() {
  sassert(((global_a)+(global_b))==((4)*(global_n)));
  return 0;
}

int node146() {
  int status;
  if (node_146_next == 141) {
    status = node141();
    if (status == 1) {
      node_146_next = 141;
      return 1;
    }
    if (status == 2) {
      node_146_next = 141;
      return 2;
    }
    node_146_next = 145;
  }

  if (node_146_next == 145) {
    status = node145();
    if (status == 1) {
      node_146_next = 145;
      return 1;
    }
    if (status == 2) {
      node_146_next = 141;
      return 2;
    }
    node_146_next = 144;
  }

  if (node_146_next == 144) {
    status = node144();
    if (status == 1) {
      node_146_next = 144;
      return 1;
    }
    if (status == 2) {
      node_146_next = 141;
      return 2;
    }
  }

  node_146_next = 141;
  return 0;
}

int main(void) {
  while (1) {
    node146();
  }
}

