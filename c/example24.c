extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_nd = 0;
int global_n = 0;
int global_old = 0;
int global_new = 0;
int global_lock = 0;

// local variables
node_104_next = 99;

// cfas
int node99() {
  global_old = 0;
  global_lock = 0;
  global_new = (global_old)+(1);
  return 0;
}

int node100() {
  if ((global_new)!=(global_old)) {
    return 2;
  } else {
    return 0;
  }
}

int node101() {
  global_lock = 1;
  global_old = global_new;
  global_n = nd();
  if (global_n) {
    global_lock = 0;
    global_new = (global_new)+(1);
  } else {
  }
}

int node103() {
  int status;
  status = node100();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node101();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node102() {
  sassert((global_lock)!=(0));
  return 0;
}

int node104() {
  int status;
  if (node_104_next == 99) {
    status = node99();
    if (status == 1) {
      node_104_next = 99;
      return 1;
    }
    if (status == 2) {
      node_104_next = 99;
      return 2;
    }
    node_104_next = 103;
  }

  if (node_104_next == 103) {
    status = node103();
    if (status == 1) {
      node_104_next = 103;
      return 1;
    }
    if (status == 2) {
      node_104_next = 99;
      return 2;
    }
    node_104_next = 102;
  }

  if (node_104_next == 102) {
    status = node102();
    if (status == 1) {
      node_104_next = 102;
      return 1;
    }
    if (status == 2) {
      node_104_next = 99;
      return 2;
    }
  }

  node_104_next = 99;
  return 0;
}

int main(void) {
  while (1) {
    node104();
  }
}

