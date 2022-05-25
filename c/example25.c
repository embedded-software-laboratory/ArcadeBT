extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_nd = 0;
int global_n = 0;
int global_i = 0;
int global_j = 0;
int global_z = 0;
int global_x = 0;
int global_y = 0;
int global_w = 0;

// local variables
node_110_next = 105;

// cfas
int node105() {
  global_i = 1;
  global_j = 0;
  global_z = (global_i)-(global_j);
  global_x = 0;
  global_y = 0;
  global_w = 0;
  return 0;
}

int node106() {
  global_n = nd();
  if (global_n) {
    return 2;
  } else {
    return 0;
  }
}

int node107() {
  global_z = (((global_z)+(global_x))+(global_y))+(global_w);
  global_y = (global_y)+(1);
  if (((global_z)%(2))==(1)) {
    global_x = (global_x)+(1);
  } else {
  }
}

int node109() {
  int status;
  status = node106();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node107();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node108() {
  sassert((global_x)==(global_y));
  return 0;
}

int node110() {
  int status;
  if (node_110_next == 105) {
    status = node105();
    if (status == 1) {
      node_110_next = 105;
      return 1;
    }
    if (status == 2) {
      node_110_next = 105;
      return 2;
    }
    node_110_next = 109;
  }

  if (node_110_next == 109) {
    status = node109();
    if (status == 1) {
      node_110_next = 109;
      return 1;
    }
    if (status == 2) {
      node_110_next = 105;
      return 2;
    }
    node_110_next = 108;
  }

  if (node_110_next == 108) {
    status = node108();
    if (status == 1) {
      node_110_next = 108;
      return 1;
    }
    if (status == 2) {
      node_110_next = 105;
      return 2;
    }
  }

  node_110_next = 105;
  return 0;
}

int main(void) {
  while (1) {
    node110();
  }
}

