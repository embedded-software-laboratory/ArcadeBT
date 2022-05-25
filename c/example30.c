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
node_140_next = 135;

// cfas
int node135() {
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

int node136() {
  if ((global_i)<(global_n)) {
    return 2;
  } else {
    return 0;
  }
}

int node137() {
  global_f = nd();
  if (global_f) {
    global_a = (global_a)+(1);
    global_b = (global_b)+(2);
  } else {
    global_a = (global_a)+(2);
    global_b = (global_b)+(1);
  }
}

int node139() {
  int status;
  status = node136();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node137();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node138() {
  sassert(((global_a)+(global_b))==((3)*(global_n)));
  return 0;
}

int node140() {
  int status;
  if (node_140_next == 135) {
    status = node135();
    if (status == 1) {
      node_140_next = 135;
      return 1;
    }
    if (status == 2) {
      node_140_next = 135;
      return 2;
    }
    node_140_next = 139;
  }

  if (node_140_next == 139) {
    status = node139();
    if (status == 1) {
      node_140_next = 139;
      return 1;
    }
    if (status == 2) {
      node_140_next = 135;
      return 2;
    }
    node_140_next = 138;
  }

  if (node_140_next == 138) {
    status = node138();
    if (status == 1) {
      node_140_next = 138;
      return 1;
    }
    if (status == 2) {
      node_140_next = 135;
      return 2;
    }
  }

  node_140_next = 135;
  return 0;
}

int main(void) {
  while (1) {
    node140();
  }
}

