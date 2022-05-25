extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_r1 = 0;
int global_r2 = 0;
int global_x = 1;
int global_y = 1;
int global_count = 0;

// local variables

// cfas
int node42() {
  sassert((global_x)<=(11));
  global_r2 = nd();
  global_count = (global_count)+(1);
  if (((global_count)<=(10))&&(global_r2)) {
    return 0;
  } else {
    return 2;
  }
}

int node43() {
  global_x = (global_x)+(1);
  global_y = (global_y)+(1);
  return 0;
}

int node44() {
  int status;
  status = node42();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node43();
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
    node44();
  }
}

