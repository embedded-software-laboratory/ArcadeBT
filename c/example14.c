extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_r1 = 0;
int global_r2 = 0;
int global_x = 1;
int global_y = 1;

// local variables

// cfas
int node48() {
  sassert((global_x)>=(global_y));
  global_r2 = nd();
  if (global_r2) {
    global_x = (global_x)+(1);
    global_y = (global_y)+(1);
  } else {
  }
}

int node49() {
  global_x = (global_x)+(1);
  return 0;
}

int node50() {
  int status;
  status = node48();
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    return 2;
  }

  status = node49();
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
    node50();
  }
}

