extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_crit = 0;
int global_x = 0;

// local variables

// cfas
int node10() {
  sassert(!(global_crit));
  global_crit = 1;
  return 0;
}

int node11() {
  if ((global_x)<(3)) {
    global_x = (global_x)+(1);
    return 1;
  } else {
    global_x = 0;
    return 0;
  }
}

int node12() {
  sassert(global_crit);
  global_crit = 0;
  return 0;
}

int node13() {
  int status;
  status = node10();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node11();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node12();
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
    node13();
  }
}

