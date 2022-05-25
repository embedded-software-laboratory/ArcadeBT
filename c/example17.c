extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_init = 0;
int global_k = 1;
int global_i = 1;
int global_j = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_64_next = 58;

// cfas
int node57() {
  if (!(global_init)) {
    global_n = nd();
    global_init = 1;
  } else {
  }
}

int node58() {
  if ((global_i)<(global_n)) {
    return 0;
  } else {
    return 2;
  }
}

int node59() {
  global_j = 0;
  return 0;
}

int node60() {
  if ((global_j)<(global_i)) {
    return 0;
  } else {
    return 2;
  }
}

int node61() {
  global_k = (global_k)+((global_i)-(global_j));
  global_j = (global_j)+(1);
  if ((global_i)==(global_j)) {
    return 0;
  } else {
    return 1;
  }
}

int node63() {
  int status;
  status = node60();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node61();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  return 0;
}

int node64() {
  int status;
  if (node_64_next == 58) {
    status = node58();
    if (status == 1) {
      node_64_next = 58;
      return 1;
    }
    if (status == 2) {
      node_64_next = 58;
      return 2;
    }
    node_64_next = 59;
  }

  if (node_64_next == 59) {
    status = node59();
    if (status == 1) {
      node_64_next = 59;
      return 1;
    }
    if (status == 2) {
      node_64_next = 58;
      return 2;
    }
    node_64_next = 63;
  }

  if (node_64_next == 63) {
    status = node63();
    if (status == 1) {
      node_64_next = 63;
      return 1;
    }
    if (status == 2) {
      node_64_next = 58;
      return 2;
    }
  }

  node_64_next = 58;
  return 0;
}

int node62() {
  sassert((global_k)>=(global_n));
  return 0;
}

int node65() {
  int status;
  status = node64();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node62();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node66() {
  int status;
  status = node57();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node65();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  return 0;
}

int main(void) {
  while (1) {
    node66();
  }
}

