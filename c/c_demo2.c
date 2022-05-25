/*
    SUCCESS = 1
    RUNNING = 2
    FAILURE = 3
*/

extern void __VERIFIER_error (void);
#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))

// variables
int x = 1;

int cfa1() {
    sassert( 1 <= x && x <= 2);
    if (x == 1) {
        x = 3;
        return 1;
    } else {
        return 3;
    }
}

int cfa2() {
    sassert( 2 <= x && x <= 3);
    if (x == 3) {
        x = 1;
        return 1;
    } else {
        return 3;
    }
}

int cfa3() {
    sassert( 3 <= x && x <= 3);
    if (x == 3) {
        x = 2;
        return 1;
    } else {
        return 3;
    }
}

int main (void) {


    // nodes



    // state
    int state = 0;
    int state_next;
    int last_status;

    while (1) {
        if (state == 0) {
            int children[3] = {1, 2, 3};
            int status;
            // call child 1
            status = cfa1();
            if (status == 2 || status == 3) {
                last_status = status;
                state_next = 0;
                continue;
            }
            status = cfa2();
            if (status == 2 || status == 3) {
                last_status = status;
                state_next = 0;
                continue;
            }
            status = cfa3();
            state_next = 0;
        }
        state = state_next;
    }
}