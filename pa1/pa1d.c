/* Programming Assignment 1: Exercise D
 *
 * Let's continue using Yield (pid) to effect a variety of executions
 * sequences.  Using the code below, the sequence of the print statements
 * will be ABP:
 *
 *	First Child (A)
 *	Second Child (B)
 *	Parent (P)
 *
 *
 * Questions
 *
 * 1. See if you can cause a change in the sequence as specified below just by
 * ADDING Yield statements (i.e., do not remove any of the ORIGINAL Yield
 * statements, just add extra ones anywhere you wish):
 *
 * a. BAP do b and add Yield(pid1) after Yield(pid2)
 * b. BPA add yield(ppid) before first child Printf
 * c. PAB do b and e
 * d. PBA do c and add Yield(pid2) after parent Printf
 * e. APB add yield(ppid) before second child Printf
 *
 */

#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main ()
{
	int ppid, pid1, pid2;

	ppid = Getpid ();
	//Yield(ppid);
	if ((pid1 = Fork ()) == 0) {
		Yield(ppid);
		//Yield(pid2);
		/* first child executes here */
		Printf ("I am the first child, my pid is %d\n", Getpid ());
		Exit ();
	}
		
	Yield (pid1);
	//Yield(ppid);
	if ((pid2 = Fork ()) == 0) {
		Yield(ppid);
		/* second child executes here */
		Printf ("I am the second child, my pid is %d\n", Getpid ());

		Exit ();
	}
	
	Yield (pid2);	// yield to second child before continuing
	
	Printf ("I am the parent, my pid is %d\n", Getpid ());
	Yield(pid2);

}
