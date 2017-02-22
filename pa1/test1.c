#include <stdio.h>
 #include "aux.h"
 #include "umix.h"
 
 #define NUMPROCS 9
 
 void Main ()
 {
   int i, pid;
 
   // Make 10 procs total
   for (i = 0; i < NUMPROCS; i++)
   {
       if ((pid = Fork ()) == 0) {
       Printf ("Exiting pid %d\n", Getpid ());
       Exit ();
     }
       Printf("%d\n", pid);
   }
 
   // Exit out of 2-5
   for (i = 2; i <= NUMPROCS / 2 + 1; i++)
   {
     Yield (i);
   }
 
   Printf ("PIDs 1 and 6-10 exist. Testing to make 2-5\n");
 
   // Create pid 2-5
   for (i = 2; i <= NUMPROCS / 2 + 1; i++)
   {
     if ((pid = Fork ()) == 0) {
       Printf ("Exiting pid %d\n", Getpid ());
       Exit ();
     }
     Printf ("Created pid %d\n", pid);
   }
 
   Printf("Exiting parent pid %d\n", Getpid ());
 
   // Exit 1-10
   for (i = 0; i < NUMPROCS; i++)
   {
     if ((pid = Fork ()) == 0) {
       Printf ("Exiting pid %d\n", Getpid ());
       Exit ();
     }
   }
 
 }
