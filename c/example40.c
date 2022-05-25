extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_fd = 0;
int global_f = 0;
int global_x = 0;
int global_y = 1;
int global_i = 1;
int global_t = 1;
int global_nd = 0;
int global_n = 0;

// local variables
node_200_next = 195;

// cfas
int node195() {
  global_x = nd();
  global_y = nd();
  global_i = 0;
  global_t = global_y;
  if ((global_x)==(global_y)) {
    return 2;
  } else {
    return 0;
  }
}

int node196() {
  global_f = nd();
  if (global_f) {
    return 2;
  } else {
    return 0;
  }
}

int node197() {
  if ((global_x)>(0)) {
    global_y = (global_y)+(global_x);
  } else {
  }
}

int node199() {
  int status;
  status = node196();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node197();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node198() {
  sassert((global_y)>=(global_t));
  return 0;
}

int node200() {
  int status;
  if (node_200_next == 195) {
    status = node195();
    if (status == 1) {
      node_200_next = 195;
      return 1;
    }
    if (status == 2) {
      node_200_next = 195;
      return 2;
    }
    node_200_next = 199;
  }

  if (node_200_next == 199) {
    status = node199();
    if (status == 1) {
      node_200_next = 199;
      return 1;
    }
    if (status == 2) {
      node_200_next = 195;
      return 2;
    }
    node_200_next = 198;
  }

  if (node_200_next == 198) {
    status = node198();
    if (status == 1) {
      node_200_next = 198;
      return 1;
    }
    if (status == 2) {
      node_200_next = 195;
      return 2;
    }
  }

  node_200_next = 195;
  return 0;
}

int main(void) {
  while (1) {
    node200();
  }
}

