#include "aux.h"
#include "umix.h"
#include "mythreads.h"

#define NUMYIELDS 5

static int square, cube;  // global variables, shared by threads

void Main ()
{
  int i, t, me;
  void printSquares (), printCubes (), printCubes1 (),
                              printCubes2 (), printCubes3 ();
  MyInitThreads ();
  me = MyGetThread ();
  t = MyCreateThread (printCubes3, t); //1
  t = MyCreateThread (printCubes3, t); //2
  t = MyCreateThread (printCubes3, t); //3
  t = MyCreateThread (printCubes3, t); //4
  t = MyCreateThread (printCubes3, t); //5
  t = MyCreateThread (printCubes3, t); //6
  t = MyCreateThread (printCubes3, t); //7
  t = MyCreateThread (printCubes3, t); //8
  t = MyCreateThread (printCubes3, t); //9
  Printf ("T%d: square = %d, cube = %d\n", me, square, cube);
  MyExitThread ();
}

void printSquares (t)
  int t;        // thread to yield to
{
  int i;
  Printf("Exiting %d\n", MyGetThread());
  MyExitThread();
}

void printCubes (t)
  int t;        // thread to yield to
{
  int i;
  t = MyCreateThread(printSquares, t);
  Printf("In printCubes...Created thread %d\n", t);
  Printf("In printCubes...Exiting %d\n", MyGetThread());
  MyExitThread();
}

void printCubes1 (t)
  int t;        // thread to yield to
{
  int i;
  t = MyCreateThread(printCubes, t);
  Printf("In printCubes1...Created thread %d\n", t);
  Printf("In printCubes1...Exiting %d\n", MyGetThread());
  MyExitThread();
}

void printCubes2 (t)
  int t;        // thread to yield to
{
  int i;
  t = MyCreateThread(printCubes1, t);
  Printf("In printCubes2...Created thread %d\n", t);
  Printf("In printCubes2...Exiting %d\n", MyGetThread());
  MyExitThread();
}

void printCubes3 (t)
  int t;        // thread to yield to
{
  int i;
  t = MyCreateThread(printCubes2, t);
  Printf("In printCubes3...Created thread %d\n", t);
  Printf("In printCubes3...Exiting %d\n", MyGetThread());
  MyExitThread();
}
