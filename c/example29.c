extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_nd = 0;
int global_n = 0;
int global_w = 0;
int global_z = 0;
int global_x = 0;
int global_y = 0;

// local variables
node_134_next = 129;

// cfas
int node129() {
  global_w = 1;
  global_z = 0;
  global_x = 0;
  global_y = 0;
  return 0;
}

int node130() {
  global_n = nd();
  if (global_n) {
    return 2;
  } else {
    return 0;
  }
}

int node131() {
  global_n = nd();
  while (global_n) {
    if (((global_w)%(2))==(1)) {
      global_x = (global_x)+(1);
      if (((global_z)%(2))==(0)) {
        global_y = (global_y)+(1);
      } else {
      }
    } else {
      if (((global_z)%(2))==(0)) {
        global_y = (global_y)+(1);
      } else {
      }
    }
}
  global_z = (global_x)+(global_y);
  global_w = (global_z)+(1);
  return 1;
}

int node133() {
  int status;
  status = node130();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node131();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node132() {
  sassert((global_x)!=(global_y));
  return 0;
}

int node134() {
  int status;
  if (node_134_next == 129) {
    status = node129();
    if (status == 1) {
      node_134_next = 129;
      return 1;
    }
    if (status == 2) {
      node_134_next = 129;
      return 2;
    }
    node_134_next = 133;
  }

  if (node_134_next == 133) {
    status = node133();
    if (status == 1) {
      node_134_next = 133;
      return 1;
    }
    if (status == 2) {
      node_134_next = 129;
      return 2;
    }
    node_134_next = 132;
  }

  if (node_134_next == 132) {
    status = node132();
    if (status == 1) {
      node_134_next = 132;
      return 1;
    }
    if (status == 2) {
      node_134_next = 129;
      return 2;
    }
  }

  node_134_next = 129;
  return 0;
}

int main(void) {
  while (1) {
    node134();
  }
}

