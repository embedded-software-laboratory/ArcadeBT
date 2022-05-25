extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 0;
int global_i = 0;
int global_nd = 0;
int global_n = 0;

// local variables

// cfas
int node74() {
  global_x = nd();
  if ((global_x)>(0)) {
    return 0;
  } else {
    return 2;
  }
}

int node75() {
  global_i = global_x;
  while ((global_i)<(global_x)) {
    sassert((global_i)!=(0));
    global_i = (global_i)+(1);
}
  return 0;
}

int node76() {
  int status;
  status = node74();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node75();
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
    node76();
  }
}

