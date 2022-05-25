extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_w = 0;
int global_z = 0;
int global_fd = 0;
int global_f = 0;
int global_x = 0;
int global_y = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_158_next = 153;

// cfas
int node153() {
  global_x = 0;
  global_y = 0;
  global_w = 1;
  global_z = 0;
  return 0;
}

int node154() {
  global_f = nd();
  if (global_f) {
    return 2;
  } else {
    return 0;
  }
}

int node155() {
  if (global_w) {
    global_x = (global_x)+(1);
    global_w = !(global_w);
  } else {
  }
}

int node157() {
  int status;
  status = node154();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node155();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node156() {
  sassert((global_x)==(global_y));
  return 0;
}

int node158() {
  int status;
  if (node_158_next == 153) {
    status = node153();
    if (status == 1) {
      node_158_next = 153;
      return 1;
    }
    if (status == 2) {
      node_158_next = 153;
      return 2;
    }
    node_158_next = 157;
  }

  if (node_158_next == 157) {
    status = node157();
    if (status == 1) {
      node_158_next = 157;
      return 1;
    }
    if (status == 2) {
      node_158_next = 153;
      return 2;
    }
    node_158_next = 156;
  }

  if (node_158_next == 156) {
    status = node156();
    if (status == 1) {
      node_158_next = 156;
      return 1;
    }
    if (status == 2) {
      node_158_next = 153;
      return 2;
    }
  }

  node_158_next = 153;
  return 0;
}

int main(void) {
  while (1) {
    node158();
  }
}

