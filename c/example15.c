extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_r1 = 0;
int global_r2 = 0;
int global_p = 1;
int global_count = 0;

// local variables

// cfas
int node51() {
  sassert((global_p)<=(12));
  global_r2 = nd();
  global_count = (global_count)+(1);
  if (((global_count)<=(6))&&(global_r2)) {
    return 0;
  } else {
    global_p = (global_p)+(2);
    return 2;
  }
}

int node52() {
  global_p = (global_p)+(1);
  return 0;
}

int node53() {
  int status;
  status = node51();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node52();
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
    node53();
  }
}

