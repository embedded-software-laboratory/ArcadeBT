extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_a = 0;
int global_y = 0;
int global_nd = 0;
int global_n = 0;

// local variables

// cfas
int node85() {
  global_a = nd();
  global_y = 0;
  return 0;
}

int node86() {
  if ((global_a)!=(0)) {
    return 2;
  } else {
    return 0;
  }
}

int node87() {
  global_y = 1;
  return 0;
}

int node90() {
  int status;
  status = node86();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node87();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node88() {
  if ((global_y)==(0)) {
    return 2;
  } else {
    return 0;
  }
}

int node89() {
  sassert((global_a)==(0));
  return 0;
}

int node91() {
  int status;
  status = node88();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node89();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node92() {
  int status;
  status = node85();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node90();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node91();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  return 0;
}

int main(void) {
  while (1) {
    node92();
  }
}

