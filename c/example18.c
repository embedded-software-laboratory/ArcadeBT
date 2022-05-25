extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_i = 0;
int global_v = 0;
int global_s = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_72_next = 67;

// cfas
int node67() {
  global_n = nd();
  global_i = 0;
  global_s = 0;
  global_v = 0;
  if (((global_n)==(0))||((global_n)<(0))) {
    return 2;
  } else {
    return 0;
  }
}

int node68() {
  if ((global_i)<(global_n)) {
    return 0;
  } else {
    return 2;
  }
}

int node69() {
  global_v = nd();
  if ((global_v)<(0)) {
    return 1;
  } else {
    global_s = (global_s)+(global_v);
    global_i = (global_i)+(1);
    if ((global_i)==(global_n)) {
      return 0;
    } else {
      return 1;
    }
  }
}

int node71() {
  int status;
  status = node68();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node69();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  return 0;
}

int node70() {
  sassert(((global_v)<=(global_s))&&((global_s)>=(0)));
  return 0;
}

int node72() {
  int status;
  if (node_72_next == 67) {
    status = node67();
    if (status == 1) {
      node_72_next = 67;
      return 1;
    }
    if (status == 2) {
      node_72_next = 67;
      return 2;
    }
    node_72_next = 71;
  }

  if (node_72_next == 71) {
    status = node71();
    if (status == 1) {
      node_72_next = 71;
      return 1;
    }
    if (status == 2) {
      node_72_next = 67;
      return 2;
    }
    node_72_next = 70;
  }

  if (node_72_next == 70) {
    status = node70();
    if (status == 1) {
      node_72_next = 70;
      return 1;
    }
    if (status == 2) {
      node_72_next = 67;
      return 2;
    }
  }

  node_72_next = 67;
  return 0;
}

int main(void) {
  while (1) {
    node72();
  }
}

