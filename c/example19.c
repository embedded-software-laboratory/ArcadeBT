extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_x = 0;

// local variables

// cfas
int node73() {
  sassert(((global_x)%(2))==(0));
  global_x = (global_x)+(2);
  return 2;
}

int main(void) {
  while (1) {
    node73();
  }
}

