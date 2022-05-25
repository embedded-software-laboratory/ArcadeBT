extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_nd = 0;
int global_n = 0;
int global_w = 0;
int global_z = 0;
int global_x = 0;
int global_y = 0;

// local variables
node_128_next = 123;

// cfas
int node123() {
  global_w = 1;
  global_z = 0;
  global_x = 0;
  global_y = 0;
  return 0;
}

int node124() {
  global_n = nd();
  if (global_n) {
    return 2;
  } else {
    return 0;
  }
}

int node125() {
  global_n = nd();
  while (global_n) {
    if (((global_w)%(2))==(1)) {
      global_x = (global_x)+(1);
      if (((global_z)%(2))==(0)) {
        global_y = (global_y)+(1);
      } else {
      }
    } else {
      if (((global_z)%(2))==(0)) {
        global_y = (global_y)+(1);
      } else {
      }
    }
}
  global_z = (global_x)+(global_y);
  global_w = (global_z)+(1);
  return 1;
}

int node127() {
  int status;
  status = node124();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node125();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node126() {
  sassert((global_x)==(global_y));
  return 0;
}

int node128() {
  int status;
  if (node_128_next == 123) {
    status = node123();
    if (status == 1) {
      node_128_next = 123;
      return 1;
    }
    if (status == 2) {
      node_128_next = 123;
      return 2;
    }
    node_128_next = 127;
  }

  if (node_128_next == 127) {
    status = node127();
    if (status == 1) {
      node_128_next = 127;
      return 1;
    }
    if (status == 2) {
      node_128_next = 123;
      return 2;
    }
    node_128_next = 126;
  }

  if (node_128_next == 126) {
    status = node126();
    if (status == 1) {
      node_128_next = 126;
      return 1;
    }
    if (status == 2) {
      node_128_next = 123;
      return 2;
    }
  }

  node_128_next = 123;
  return 0;
}

int main(void) {
  while (1) {
    node128();
  }
}

