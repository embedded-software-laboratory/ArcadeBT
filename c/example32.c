extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

extern int nd(void);

// global variables
int global_fd = 0;
int global_f = 0;
int global_x = 0;
int global_y = 0;
int global_nd = 0;
int global_n = 0;

// local variables
node_152_next = 147;

// cfas
int node147() {
  global_x = 0;
  global_y = 0;
  return 0;
}

int node148() {
  global_f = nd();
  if (global_f) {
    return 2;
  } else {
    return 0;
  }
}

int node149() {
  global_f = nd();
  if (global_f) {
    global_x = (global_x)+(1);
    global_y = (global_y)+(100);
  } else {
    global_f = nd();
    if (global_f) {
      if ((global_x)>=(4)) {
        global_x = (global_x)+(1);
        global_y = (global_y)+(1);
        global_y = (global_y)+(1);
        if ((global_x)<(0)) {
          global_y = (global_y)-(1);
        } else {
        }
      } else {
        if ((global_x)<(0)) {
          global_y = (global_y)-(1);
        } else {
        }
      }
    } else {
    }
  }
}

int node151() {
  int status;
  status = node148();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  status = node149();
  if (status == 1) {
    return 1;
  }
  if (status == 0) {
    return 0;
  }

  return 2;
}

int node150() {
  sassert(((global_x)<(4))||((global_y)>(2)));
  return 0;
}

int node152() {
  int status;
  if (node_152_next == 147) {
    status = node147();
    if (status == 1) {
      node_152_next = 147;
      return 1;
    }
    if (status == 2) {
      node_152_next = 147;
      return 2;
    }
    node_152_next = 151;
  }

  if (node_152_next == 151) {
    status = node151();
    if (status == 1) {
      node_152_next = 151;
      return 1;
    }
    if (status == 2) {
      node_152_next = 147;
      return 2;
    }
    node_152_next = 150;
  }

  if (node_152_next == 150) {
    status = node150();
    if (status == 1) {
      node_152_next = 150;
      return 1;
    }
    if (status == 2) {
      node_152_next = 147;
      return 2;
    }
  }

  node_152_next = 147;
  return 0;
}

int main(void) {
  while (1) {
    node152();
  }
}

