extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_flag = 0;
int global_nd = 0;
int global_n = 0;
int global_x = 0;
int global_y = 0;
int global_i = 0;
int global_j = 0;

// local variables
node_122_next = 117;

// cfas
int node117() {
  global_x = 0;
  global_y = 0;
  global_j = 0;
  global_i = 0;
  global_flag = nd();
  return 0;
}

int node118() {
  global_n = nd();
  if (global_n) {
    return 2;
  } else {
    return 0;
  }
}

int node119() {
  global_x = (global_x)+(1);
  global_y = (global_y)+(1);
  global_i = (global_x)+(global_i);
  global_j = (global_y)+(global_j);
  if (global_flag) {
    global_j = (global_j)+(1);
  } else {
  }
}

int node121() {
  int status;
  status = node118();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node119();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node120() {
  sassert((global_j)>=(global_i));
  return 0;
}

int node122() {
  int status;
  if (node_122_next == 117) {
    status = node117();
    if (status == 1) {
      node_122_next = 117;
      return 1;
    }
    if (status == 2) {
      node_122_next = 117;
      return 2;
    }
    node_122_next = 121;
  }

  if (node_122_next == 121) {
    status = node121();
    if (status == 1) {
      node_122_next = 121;
      return 1;
    }
    if (status == 2) {
      node_122_next = 117;
      return 2;
    }
    node_122_next = 120;
  }

  if (node_122_next == 120) {
    status = node120();
    if (status == 1) {
      node_122_next = 120;
      return 1;
    }
    if (status == 2) {
      node_122_next = 117;
      return 2;
    }
  }

  node_122_next = 117;
  return 0;
}

int main(void) {
  while (1) {
    node122();
  }
}

