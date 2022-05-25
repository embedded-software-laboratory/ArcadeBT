extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 1;

// local variables

// cfas
int node18() {
  sassert(((1)<=(global_x))&&((global_x)<=(3)));
  if ((global_x)==(1)) {
    global_x = 3;
    return 0;
  } else {
    return 2;
  }
}

int node19() {
  sassert(((2)<=(global_x))&&((global_x)<=(3)));
  if ((global_x)==(2)) {
    global_x = 1;
    return 0;
  } else {
    return 2;
  }
}

int node20() {
  sassert(((3)<=(global_x))&&((global_x)<=(3)));
  if ((global_x)==(3)) {
    global_x = 2;
    return 0;
  } else {
    return 2;
  }
}

int node21() {
  int status;
  status = node18();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node19();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node20();
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
    node21();
  }
}

