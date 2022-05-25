extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_w = 0;
int global_z = 0;
int global_fd = 0;
int global_f = 0;
int global_x = 0;
int global_y = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_164_next = 159;

// cfas
int node159() {
  global_x = 0;
  global_y = 0;
  global_w = 1;
  global_z = 0;
  return 0;
}

int node160() {
  global_f = nd();
  if (global_f) {
    return 2;
  } else {
    return 0;
  }
}

int node161() {
  if (global_w) {
    global_x = (global_x)+(1);
    global_w = !(global_w);
  } else {
  }
}

int node163() {
  int status;
  status = node160();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node161();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node162() {
  sassert((global_x)!=(global_y));
  return 0;
}

int node164() {
  int status;
  if (node_164_next == 159) {
    status = node159();
    if (status == 1) {
      node_164_next = 159;
      return 1;
    }
    if (status == 2) {
      node_164_next = 159;
      return 2;
    }
    node_164_next = 163;
  }

  if (node_164_next == 163) {
    status = node163();
    if (status == 1) {
      node_164_next = 163;
      return 1;
    }
    if (status == 2) {
      node_164_next = 159;
      return 2;
    }
    node_164_next = 162;
  }

  if (node_164_next == 162) {
    status = node162();
    if (status == 1) {
      node_164_next = 162;
      return 1;
    }
    if (status == 2) {
      node_164_next = 159;
      return 2;
    }
  }

  node_164_next = 159;
  return 0;
}

int main(void) {
  while (1) {
    node164();
  }
}

