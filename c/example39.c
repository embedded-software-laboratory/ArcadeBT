extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_b = 0;
int global_fd = 0;
int global_f = 0;
int global_k = 100;
int global_i = 0;
int global_j = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_194_next = 189;

// cfas
int node189() {
  global_j = nd();
  global_i = global_j;
  global_n = 0;
  global_b = nd();
  return 0;
}

int node190() {
  if ((global_n)<((2)*(global_k))) {
    return 2;
  } else {
    return 0;
  }
}

int node191() {
  if (global_b) {
    global_i = (global_i)+(1);
  } else {
    global_j = (global_j)+(1);
  }
}

int node193() {
  int status;
  status = node190();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node191();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node192() {
  sassert((global_i)==(global_j));
  return 0;
}

int node194() {
  int status;
  if (node_194_next == 189) {
    status = node189();
    if (status == 1) {
      node_194_next = 189;
      return 1;
    }
    if (status == 2) {
      node_194_next = 189;
      return 2;
    }
    node_194_next = 193;
  }

  if (node_194_next == 193) {
    status = node193();
    if (status == 1) {
      node_194_next = 193;
      return 1;
    }
    if (status == 2) {
      node_194_next = 189;
      return 2;
    }
    node_194_next = 192;
  }

  if (node_194_next == 192) {
    status = node192();
    if (status == 1) {
      node_194_next = 192;
      return 1;
    }
    if (status == 2) {
      node_194_next = 189;
      return 2;
    }
  }

  node_194_next = 189;
  return 0;
}

int main(void) {
  while (1) {
    node194();
  }
}

