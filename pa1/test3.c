#include <stdio.h>
#include "aux.h"
#include "umix.h"

//void handoff (int p);

void Main ()
{
    int p2 = Fork();
    if (Getpid() == 1) {
        int p3 = Fork();
        if (Getpid() == 1) {
            Printf("I am %d, I just forked %d and %d\n", Getpid(), p2, p3);
            Printf("I am %d, about to yield to 2\n", Getpid());
            int r1 = Yield(1);
            Printf("I am %d, resumed by %d\n", Getpid(), r1);
        }
    }
    if (Getpid() == 2) {
        Printf("I am %d, about to yield to 3\n", Getpid());
        int r2 = Yield(2);
        Printf("I am %d, resumed by %d\n", Getpid(), r2);
    }
    if (Getpid() == 3) {
        Printf("I am %d, about to yield to 1\n", Getpid());
        int r3 = Yield(3);
        Printf("I am %d, resumed by %d\n", Getpid(), r3);
    }
    Printf("%d exiting\n", Getpid());
}

