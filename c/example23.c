extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_i = 0;
int global_j = 0;
int global_x = 0;
int global_y = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_98_next = 93;

// cfas
int node93() {
  global_i = nd();
  global_j = nd();
  if (((global_i)>(0))&&((global_j)>(0))) {
    global_x = global_i;
    global_y = global_j;
    return 0;
  } else {
    return 2;
  }
}

int node94() {
  if ((global_x)!=(0)) {
    return 2;
  } else {
    return 0;
  }
}

int node95() {
  global_x = (global_x)-(1);
  global_y = (global_y)-(1);
  return 1;
}

int node97() {
  int status;
  status = node94();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node95();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node96() {
  if ((global_i)==(global_j)) {
    sassert((global_y)==(0));
  } else {
  }
}

int node98() {
  int status;
  if (node_98_next == 93) {
    status = node93();
    if (status == 1) {
      node_98_next = 93;
      return 1;
    }
    if (status == 2) {
      node_98_next = 93;
      return 2;
    }
    node_98_next = 97;
  }

  if (node_98_next == 97) {
    status = node97();
    if (status == 1) {
      node_98_next = 97;
      return 1;
    }
    if (status == 2) {
      node_98_next = 93;
      return 2;
    }
    node_98_next = 96;
  }

  if (node_98_next == 96) {
    status = node96();
    if (status == 1) {
      node_98_next = 96;
      return 1;
    }
    if (status == 2) {
      node_98_next = 93;
      return 2;
    }
  }

  node_98_next = 93;
  return 0;
}

int main(void) {
  while (1) {
    node98();
  }
}

