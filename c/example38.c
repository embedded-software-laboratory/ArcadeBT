extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_i = 0;
int global_c = 0;

// local variables
node_188_next = 183;

// cfas
int node183() {
  global_i = 0;
  global_c = 0;
  return 0;
}

int node184() {
  if ((global_i)<(1000)) {
    return 2;
  } else {
    return 0;
  }
}

int node185() {
  global_c = (global_c)+(global_i);
  global_i = (global_i)+(1);
  return 1;
}

int node187() {
  int status;
  status = node184();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node185();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node186() {
  sassert((global_c)<(0));
  return 0;
}

int node188() {
  int status;
  if (node_188_next == 183) {
    status = node183();
    if (status == 1) {
      node_188_next = 183;
      return 1;
    }
    if (status == 2) {
      node_188_next = 183;
      return 2;
    }
    node_188_next = 187;
  }

  if (node_188_next == 187) {
    status = node187();
    if (status == 1) {
      node_188_next = 187;
      return 1;
    }
    if (status == 2) {
      node_188_next = 183;
      return 2;
    }
    node_188_next = 186;
  }

  if (node_188_next == 186) {
    status = node186();
    if (status == 1) {
      node_188_next = 186;
      return 1;
    }
    if (status == 2) {
      node_188_next = 183;
      return 2;
    }
  }

  node_188_next = 183;
  return 0;
}

int main(void) {
  while (1) {
    node188();
  }
}

