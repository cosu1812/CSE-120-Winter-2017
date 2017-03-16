#include "aux.h"
#include "umix.h" 
#include "mythreads.h"
#define NUMYIELDS 5 
static int square, cube; // global variables, shared by threads
void Main () {
    int i, t, me;
    void printSquares (), printCubes (); 
    MyInitThreads (); 
    me = MyGetThread ();
 t = MyCreateThread (printSquares, me); //1
 t = MyCreateThread (printCubes, t); //2 
 t = MyCreateThread(printSquares, t); //3
 t = MyCreateThread(printSquares, t); //4
 t = MyCreateThread(printSquares, t); //5
   t = MyCreateThread(printSquares, t); //6
 t = MyCreateThread(printSquares, t); //7
   t = MyCreateThread(printSquares, t); //8
 t = MyCreateThread(printSquares, t); //9 
 Printf ("T%d: square = %d, cube = %d\n", me, square, cube); 
 MyExitThread ();
} 
void printSquares (t) 
 int t;// thread to yield to 
{ 
     int i;
Printf("Exiting %d\n", MyGetThread());
    MyExitThread();
}
void printCubes (t)                                                             
  int t;        // thread to yield to                                           
{                                                                               
  int i;                                                                      
  t = MyCreateThread(printSquares, t); //10                                     
  Printf("Created thread %d\n", t);                                             
  Printf("Exiting %d\n", MyGetThread());                                        
  MyExitThread();                                                               
}  
