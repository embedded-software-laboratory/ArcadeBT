extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 1;

// local variables

// cfas
int node22() {
  sassert(((1)<=(global_x))&&((global_x)<=(2)));
  if ((global_x)==(1)) {
    global_x = 3;
    return 0;
  } else {
    return 2;
  }
}

int node23() {
  sassert(((2)<=(global_x))&&((global_x)<=(3)));
  if ((global_x)==(2)) {
    global_x = 1;
    return 0;
  } else {
    return 2;
  }
}

int node24() {
  sassert(((3)<=(global_x))&&((global_x)<=(3)));
  if ((global_x)==(3)) {
    return 0;
  } else {
    return 2;
  }
}

int node25() {
  int status;
  status = node22();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node23();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node24();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int main(void) {
  while (1) {
    node25();
  }
}

