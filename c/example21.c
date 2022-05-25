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
int node77() {
  global_a = nd();
  global_y = 0;
  return 0;
}

int node78() {
  if ((global_a)!=(0)) {
    return 2;
  } else {
    return 0;
  }
}

int node79() {
  global_y = 1;
  return 0;
}

int node82() {
  int status;
  status = node78();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node79();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node80() {
  if ((global_y)==(0)) {
    return 2;
  } else {
    return 0;
  }
}

int node81() {
  sassert((global_a)!=(0));
  return 0;
}

int node83() {
  int status;
  status = node80();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node81();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node84() {
  int status;
  status = node77();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node82();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node83();
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
    node84();
  }
}

