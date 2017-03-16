#include "aux.h"
#include "umix.h"
#include "mythreads.h"

#define NUMYIELDS	5

static int square, cube, sum;	// global variables, shared by threads

void Main ()
{
	int i, t, me, r;
	void printSquares (), printCubes (), printSum();

    MyInitThreads ();

    me = MyGetThread ();

    t = MyCreateThread(printSum, me);

    t = MyCreateThread (printSquares, t);
	
    t = MyCreateThread (printCubes, t);


    for (i = 0; i < NUMYIELDS; i++) {
		
        r = MyYieldThread (t);
		
        Printf("**Thread %d resumed by thread %d\n", MyGetThread(), r);

        Printf ("T%d: square = %d, cube = %d\n", me, square, cube);

    }

    MyExitThread ();
}

void printSum (int t){

    int i;
    int r;

    for(i = 0; i < NUMYIELDS; i++){
    
        sum = square + cube;

        Printf("T%d: %d + %d = %d\n", MyGetThread(), square, cube, sum);

        r = MyYieldThread(t);

        Printf("**Thread %d resumed by thread %d\n", MyGetThread(), r);
    }
}

void printSquares (t)
	int t;				// thread to yield to
{
    int i;
    int r;

    for (i = 0; i < NUMYIELDS; i++) {
        
        square = i * i;

        Printf ("T%d: %d squared = %d\n", MyGetThread (), i, square);
        
        r = MyYieldThread (t);

        Printf("**Thread %d resumed by thread %d\n", MyGetThread(), r);
    }
}

void printCubes (t)
	int t;				// thread to yield to
{
    int i;
    int r;


    for (i = 0; i < NUMYIELDS; i++) {
		
        cube = i * i * i;
        
        Printf ("T%d: %d cubed = %d\n", MyGetThread (), i, cube);

        r = MyYieldThread (t);
        
        Printf("**Thread %d resumed by thread %d\n", MyGetThread(), r);
    }
}
