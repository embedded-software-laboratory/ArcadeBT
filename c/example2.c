extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 0;

// local variables

// cfas
int node4() {
  sassert(((global_x)>=(0))&&((global_x)<=(10)));
  if ((global_x)<=(10)) {
    return 0;
  } else {
    return 2;
  }
}

int node5() {
  global_x = (global_x)+(1);
  return 0;
}

int node6() {
  int status;
  status = node4();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node5();
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
    node6();
  }
}

