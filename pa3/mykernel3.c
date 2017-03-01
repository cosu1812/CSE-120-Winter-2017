/* mykernel.c: your portion of the kernel
 *
 *	Below are procedures that are called by other parts of the kernel. 
 *	Your ability to modify the kernel is via these procedures.  You may
 *	modify the bodies of these procedures any way you wish (however,
 *	you cannot change the interfaces).  
 */

#include "aux.h"
#include "sys.h"
#include "mykernel3.h"

#define FALSE 0
#define TRUE 1

/*	A sample semaphore table. You may change this any way you wish.  
 */

static struct {
	int valid;	// Is this a valid entry (was sem allocated)?
	int value;	// value of semaphore
        //char name;
        int procs[MAXPROCS];
        int head;
        int tail;
} semtab[MAXSEMS];


int globalclock = 0;
//char /alpha = 'a';
/*	InitSem () is called when kernel starts up.  Initialize data
 *	structures (such as the semaphore table) and call any initialization
 *	procedures here. 
 */

void InitSem ()
{
	int s;
        int i;
	/* modify or add code any way you wish */

	for (s = 0; s < MAXSEMS; s++) {		// mark all sems free
		semtab[s].valid = FALSE;
                semtab[s].head = 0;
                semtab[s].tail = 0;
	}

        
}

/*	MySeminit (p, v) is called by the kernel whenever the system
 *	call Seminit (v) is called.  The kernel passes the initial
 * 	value v, along with the process ID p of the process that called
 *	Seminit.  MySeminit should allocate a semaphore (find a free entry
 *	in semtab and allocate), initialize that semaphore's value to v,
 *	and then return the ID (i.e., index of the allocated entry). 
 */

int MySeminit (int p, int v)
{
	int s;
        int i;
	/* modify or add code any way you wish */

	for (s = 0; s < MAXSEMS; s++) {
		if (semtab[s].valid == FALSE) {
			break;
		}
	}


	if (s == MAXSEMS) {
		Printf ("No free semaphores\n");
		return (-1);
	}

	semtab[s].valid = TRUE;
	semtab[s].value = v;
        //semtab[s].name = alpha; 
        //alpha++;
        //Printf("s: %d; name: %c\n", s, semtab[s].name);
	return (s);
}

/*	MyWait (p, s) is called by the kernel whenever the system call
 *	Wait (s) is called.  
 */

void MyWait (p, s)
	int p;				// process
	int s;				// semaphore
{
	/* modify or add code any way you wish */
	semtab[s].value--;
        DPrintf("Block: p: %d; s: %d; v: %d\n", p, s, semtab[s].value); 
        if (semtab[s].value < 0){
            semtab[s].procs[semtab[s].tail] = p;
            if (semtab[s].tail == MAXPROCS - 1) semtab[s].tail = 0;
            else semtab[s].tail++;

        DPrintf("p: %d; s = %d; v = %d\n", p, s, semtab[s].value);
            Block(p);
        }
}

/*	MySignal (p, s) is called by the kernel whenever the system call
 *	Signal (s) is called.  
 */

void MySignal (p, s)
	int p;				// process
	int s;				// semaphore
{
	/* modify or add code any way you wish */

	semtab[s].value++;
        if (semtab[s].procs[semtab[s].head] != 0) {  
            Unblock(semtab[s].procs[semtab[s].head]);
            DPrintf("Signal: p: %d; s: %d; v = %d\n", semtab[s].procs[semtab[s].head], s, semtab[s].value);

            semtab[s].procs[semtab[s].head] = 0;
            if (semtab[s].head == MAXPROCS - 1) semtab[s].head = 0;
            else semtab[s].head++;
            //Printf("next: %d\n", semtab[s].procs[semtab[s].head]);
        } 
}

