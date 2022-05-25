extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_fd = 0;
int global_f = 0;
int global_i = 0;
int global_sum = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_176_next = 171;

// cfas
int node171() {
  global_i = 0;
  global_sum = 0;
  global_n = nd();
  if ((global_n)>=(0)) {
    return 0;
  } else {
    return 2;
  }
}

int node172() {
  if ((global_i)<=((global_n)+(1))) {
    return 2;
  } else {
    return 0;
  }
}

int node173() {
  global_sum = (global_sum)+(global_i);
  return 1;
}

int node175() {
  int status;
  status = node172();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node173();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node174() {
  sassert((global_sum)==(((global_n)*((global_n)-(1)))/(2)));
  return 0;
}

int node176() {
  int status;
  if (node_176_next == 171) {
    status = node171();
    if (status == 1) {
      node_176_next = 171;
      return 1;
    }
    if (status == 2) {
      node_176_next = 171;
      return 2;
    }
    node_176_next = 175;
  }

  if (node_176_next == 175) {
    status = node175();
    if (status == 1) {
      node_176_next = 175;
      return 1;
    }
    if (status == 2) {
      node_176_next = 171;
      return 2;
    }
    node_176_next = 174;
  }

  if (node_176_next == 174) {
    status = node174();
    if (status == 1) {
      node_176_next = 174;
      return 1;
    }
    if (status == 2) {
      node_176_next = 171;
      return 2;
    }
  }

  node_176_next = 171;
  return 0;
}

int main(void) {
  while (1) {
    node176();
  }
}

