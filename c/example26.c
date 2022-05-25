extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_116_next = 111;

// cfas
int node111() {
  global_x = 0;
  return 0;
}

int node112() {
  global_n = nd();
  if ((global_x)<(global_n)) {
    return 2;
  } else {
    return 0;
  }
}

int node113() {
  global_x = (global_x)+(2);
  return 1;
}

int node115() {
  int status;
  status = node112();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node113();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node114() {
  if ((global_x)==(1)) {
    sassert(0);
  } else {
  }
}

int node116() {
  int status;
  if (node_116_next == 111) {
    status = node111();
    if (status == 1) {
      node_116_next = 111;
      return 1;
    }
    if (status == 2) {
      node_116_next = 111;
      return 2;
    }
    node_116_next = 115;
  }

  if (node_116_next == 115) {
    status = node115();
    if (status == 1) {
      node_116_next = 115;
      return 1;
    }
    if (status == 2) {
      node_116_next = 111;
      return 2;
    }
    node_116_next = 114;
  }

  if (node_116_next == 114) {
    status = node114();
    if (status == 1) {
      node_116_next = 114;
      return 1;
    }
    if (status == 2) {
      node_116_next = 111;
      return 2;
    }
  }

  node_116_next = 111;
  return 0;
}

int main(void) {
  while (1) {
    node116();
  }
}

