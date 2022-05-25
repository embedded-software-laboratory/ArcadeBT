extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 0;
int global_y = 0;

// local variables

// cfas
int node34() {
  sassert((global_x)==(global_y));
  return 0;
}

int node35() {
  global_x = (global_x)+(1);
  return 0;
}

int node36() {
  global_y = (global_y)+(1);
  return 0;
}

int node38() {
  int status;
  status = node34();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node37();
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
    node38();
  }
}

