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
node_170_next = 165;

// cfas
int node165() {
  global_i = 0;
  global_sum = 0;
  global_n = nd();
  if ((global_n)>=(0)) {
    return 0;
  } else {
    return 2;
  }
}

int node166() {
  if ((global_i)<=(global_n)) {
    return 2;
  } else {
    return 0;
  }
}

int node167() {
  global_sum = (global_sum)+(global_i);
  return 1;
}

int node169() {
  int status;
  status = node166();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node167();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node168() {
  sassert((global_sum)==(((global_n)*((global_n)-(1)))/(2)));
  return 0;
}

int node170() {
  int status;
  if (node_170_next == 165) {
    status = node165();
    if (status == 1) {
      node_170_next = 165;
      return 1;
    }
    if (status == 2) {
      node_170_next = 165;
      return 2;
    }
    node_170_next = 169;
  }

  if (node_170_next == 169) {
    status = node169();
    if (status == 1) {
      node_170_next = 169;
      return 1;
    }
    if (status == 2) {
      node_170_next = 165;
      return 2;
    }
    node_170_next = 168;
  }

  if (node_170_next == 168) {
    status = node168();
    if (status == 1) {
      node_170_next = 168;
      return 1;
    }
    if (status == 2) {
      node_170_next = 165;
      return 2;
    }
  }

  node_170_next = 165;
  return 0;
}

int main(void) {
  while (1) {
    node170();
  }
}

