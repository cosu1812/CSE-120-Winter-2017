#include <stdio.h>
#include "aux.h"
#include "umix.h"

void handoff (int p);

void Main ()
{
    int p2 = Fork();
    if (Getpid() == 1) {
        int p3 = Fork();
        if (Getpid() == 1) {
            Printf("I am %d, I just forked %d and %d\n", Getpid(), p2, p3);
            Printf("I am %d, about to yield to 2\n", Getpid());
            int r1 = Yield(2);
            Printf("I am %d, resumed by %d\n", Getpid(), r1);
        }
    }
    if (Getpid() == 2) {
        Printf("I am %d, about to yield to 3\n", Getpid());
        int r2 = Yield(3);
        Printf("I am %d, resumed by %d\n", Getpid(), r2);
    }
    if (Getpid() == 3) {
        Printf("I am %d, about to yield to 1\n", Getpid());
        int r3 = Yield(1);
        Printf("I am %d, resumed by %d\n", Getpid(), r3);
    }
    Printf("%d exiting\n", Getpid());
}
/*The correct order is:
I am 1, I just forked 2 and 3
I am 1, about to yield to 2
I am 2, about to yield to 3
I am 3, about to yield to 1
I am 1, resumed by 3
1 exiting
I am 2, resumed by 1
2 exiting
I am 3, resumed by 2
3 exiting*/
