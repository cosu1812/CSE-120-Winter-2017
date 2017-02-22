#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main ()
{
	int i, pid;
  int NUMPROCS = 13;
    // Make 10 procs total
    for (i = 0; i < NUMPROCS; i++)
    {
      if ((pid = Fork ()) == 0) {
        Printf ("1Exiting pid %d\n", Getpid ());
        Exit ();
      }
    }
  
		Yield(2);
                //Yield(5);
		if ((pid = Fork ()) == 0) {
        Printf ("Exiting pid %d\n", Getpid ());
        Exit ();
      }
  	Printf(" I am the big boss %d\n", Getpid());
}
