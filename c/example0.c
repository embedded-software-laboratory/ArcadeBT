extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 0;
int global_y = 0;

// local variables

// cfas
int node0() {
  global_y = nd();
  sassert((global_y)==(0));
  return 0;
}

int main(void) {
  while (1) {
    node0();
  }
}