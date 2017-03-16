#include "aux.h"
#include "umix.h"
#include "mythreads.h"

#define NUMYIELDS	5

static int square, cube;	// global variables, shared by threads

void Main ()
{
	int i, t, t1, me;
	void printSquares (), printCubes ();

	MyInitThreads ();

	me = MyGetThread ();                    // thread 0
        t = MyCreateThread (printSquares, 1);  // thread 1
        Printf("        *just created %d\n", t);
        MyYieldThread(t);
	t = MyCreateThread (printCubes, 3);     // thread 2
        Printf("        *just created %d\n", t);
        t = MyCreateThread (printSquares, 4);  // thread 3
        Printf("        *just created %d\n", t);
	t = MyCreateThread (printCubes, 5);     // thread 4
        Printf("        *just created %d\n", t);
        t = MyCreateThread (printSquares, 6);  // thread 5
        Printf("        *just created %d\n", t);
	t = MyCreateThread (printCubes, 7);     // thread 6
        Printf("        *just created %d\n", t);
        t = MyCreateThread (printSquares, 8);  // thread 7
        Printf("        *just created %d\n", t);
	t = MyCreateThread (printCubes, 9);     // thread 8
        Printf("        *just created %d\n", t);
        t = MyCreateThread (printSquares, 0);  // thread 9
        Printf("        *just created %d\n", t);
        DPrintf("        *just created %d\n", t);

	for (i = 0; i < NUMYIELDS; i++) {
		MyYieldThread (t);
		Printf ("T%d: square = %d, cube = %d\n", me, square, cube);
	}

	t = MyCreateThread (printCubes, t);     // thread 10
        Printf("                                            *just created %d\n", t);
	
        MyExitThread ();
}

void printSquares (t)
	int t;				// thread to yield to
{
	int i;

	for (i = 0; i < NUMYIELDS; i++) {
		square = i * i;
		Printf ("T%d: %d squared = %d\n", MyGetThread (), i, square);
		MyYieldThread (t);
	}
}

void printCubes (t)
	int t;				// thread to yield to
{
	int i;

	for (i = 0; i < NUMYIELDS; i++) {
		cube = i * i * i;
		Printf ("T%d: %d cubed = %d\n", MyGetThread (), i, cube);
		MyYieldThread (t);
	}
}
