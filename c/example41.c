extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_fd = 0;
int global_f = 0;
int global_x = 0;
int global_y = 1;
int global_i = 1;
int global_t = 1;
int global_nd = 0;
int global_n = 0;

// local variables
node_206_next = 201;

// cfas
int node201() {
  global_x = nd();
  global_y = nd();
  global_i = 0;
  global_t = global_y;
  if ((global_x)==(global_y)) {
    return 2;
  } else {
    return 0;
  }
}

int node202() {
  global_f = nd();
  if (global_f) {
    return 2;
  } else {
    return 0;
  }
}

int node203() {
  if ((global_x)>(0)) {
    global_y = (global_y)+(global_x);
  } else {
  }
}

int node205() {
  int status;
  status = node202();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node203();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node204() {
  sassert((global_y)<(global_t));
  return 0;
}

int node206() {
  int status;
  if (node_206_next == 201) {
    status = node201();
    if (status == 1) {
      node_206_next = 201;
      return 1;
    }
    if (status == 2) {
      node_206_next = 201;
      return 2;
    }
    node_206_next = 205;
  }

  if (node_206_next == 205) {
    status = node205();
    if (status == 1) {
      node_206_next = 205;
      return 1;
    }
    if (status == 2) {
      node_206_next = 201;
      return 2;
    }
    node_206_next = 204;
  }

  if (node_206_next == 204) {
    status = node204();
    if (status == 1) {
      node_206_next = 204;
      return 1;
    }
    if (status == 2) {
      node_206_next = 201;
      return 2;
    }
  }

  node_206_next = 201;
  return 0;
}

int main(void) {
  while (1) {
    node206();
  }
}

