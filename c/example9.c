extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 0;
int global_y = 0;

// local variables

// cfas
int node29() {
  sassert((global_x)==(global_y));
  return 0;
}

int node30() {
  global_x = (global_x)+(1);
  return 0;
}

int node31() {
  global_y = (global_y)+(1);
  return 0;
}

int node33() {
  int status;
  status = node29();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node32();
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
    node33();
  }
}

