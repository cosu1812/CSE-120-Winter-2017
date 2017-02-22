/* mykernel2.c: your portion of the kernel
 *
 *	Below are procedures that are called by other parts of the kernel. 
 *	Your ability to modify the kernel is via these procedures.  You may
 *	modify the bodies of these procedures any way you wish (however,
 *	you cannot change the interfaces).  
 * 
 */

#include "aux.h"
#include "sys.h"
#include "mykernel2.h"

#define TIMERINTERVAL 1	// in ticks (tick = 10 msec) 100000
#define L 100000
/*	A sample process table. You may change this any way you wish.  
 */

static struct {
	int valid;		// is this entry valid: 1 = yes, 0 = no
	int pid;		// process ID (as provided by kernel)
        int timestamp;
        int cpu;
        int request;
        int stride;
        int pass;
} proctab[MAXPROCS];

int globalclock = 0;
int uCPU = 100;
int rCPU = 0;
int numU = 0;
int head = -1;
int last = -1;

/*	InitSched () is called when kernel starts up.  First, set the
 *	scheduling policy (see sys.h). Make sure you follow the rules
 *	below on where and how to set it.  Next, initialize all your data
 *	structures (such as the process table).  Finally, set the timer
 *	to interrupt after a specified number of ticks. 
 */
void distributeUCPU();
void reset();

void InitSched ()
{
	int i;

	/* First, set the scheduling policy.  You should only set it
	 * from within this conditional statement.  While you are working
	 * on this assignment, GetSchedPolicy will return NOSCHEDPOLICY,
	 * and so the condition will be true and you may set the scheduling
	 * policy to whatever you choose (i.e., you may replace ARBITRARY). 
	 * After the assignment is over, during the testing phase, we will
	 * have GetSchedPolicy return the policy we wish to test, and so
	 * the condition will be false and SetSchedPolicy will not be
	 * called, thus leaving the policy to whatever we chose to test.  
	 */
	if (GetSchedPolicy () == NOSCHEDPOLICY) {	// leave as is
		SetSchedPolicy (PROPORTIONAL);		// set policy here
	}
		
	/* Initialize all your data structures here */
	for (i = 0; i < MAXPROCS; i++) {
		proctab[i].valid = 0;
                proctab[i].timestamp = 0;
                proctab[i].pass = 0;
                proctab[i].stride = 0;
                proctab[i].request = 0;
                proctab[i].cpu = 0;
	}

	/* Set the timer last */
	SetTimer (TIMERINTERVAL);
}


/*	StartingProc (pid) is called by the kernel when the process
 *	identified by pid is starting.  This allows you to record the
 *	arrival of a new process in the process table, and allocate
 *	any resources (if necessary). Returns 1 if successful, 0 otherwise.  
 */

int StartingProc (pid)
	int pid;			// process that is starting
{
	int i;

	for (i = 0; i < MAXPROCS; i++) {
		if (! proctab[i].valid) {
                        if (head == -1){
                            head = i;
                            last = i;
                        }    
                        else { 
                           last = i;
                        }  
			proctab[i].valid = 1;
			proctab[i].pid = pid;
                        proctab[i].timestamp = globalclock;
                        globalclock++;
                        if (GetSchedPolicy() == LIFO) DoSched();
                        if (GetSchedPolicy() == PROPORTIONAL) {
                            numU++;
                            //Printf("UCPU:%d\n", uCPU); 
                            if (numU > 0)  distributeUCPU();
                        }
			return (1);
		}
	}

	Printf ("Error in StartingProc: no free table entries\n");
	return (0);
}
			

/*	EndingProc (pid) is called by the kernel when the process
 *	identified by pid is ending.  This allows you to update the
 *	process table accordingly, and deallocate any resources (if
 *	necessary). Returns 1 if successful, 0 otherwise.  
 */


int EndingProc (pid)
	int pid;			// process that is ending
{
	int i;
        //Printf( "Ending %d\n", pid );
	for (i = 0; i < MAXPROCS; i++) {
		if (proctab[i].valid && proctab[i].pid == pid) {
			proctab[i].valid = 0;
                        if (GetSchedPolicy() == PROPORTIONAL) {
                            int temp = proctab[i].cpu;                     
                        
                            if (proctab[i].request == 1) {
                                rCPU -= temp;
                                uCPU += temp;
                                proctab[i].request = 0;
                            }
                            else numU -= 1;
                         //Printf("numU %d\n", numU);
                            if (numU > 0) distributeUCPU(); 
                        }
                        proctab[i].cpu = 0;
                        proctab[i].pass = 0;
                        head = i++;
                        //Printf("uCPU: %d\n", uCPU);
			return (1);
		}
	}

	Printf ("Error in EndingProc: can't find process %d\n", pid);
	return (0);
}


/*	SchedProc () is called by kernel when it needs a decision for
 *	which process to run next.  It calls the kernel function
 *	GetSchedPolicy () which will return the current scheduling policy
 *	which was previously set via SetSchedPolicy (policy). SchedProc ()
 *	should return a process id, or 0 if there are no processes to run.  
 */

int SchedProc ()
{
	int i;
        int min = L + 1;
        int minI = -1;

	switch (GetSchedPolicy ()) {

	case ARBITRARY:

		for (i = 0; i < MAXPROCS; i++) {
			if (proctab[i].valid) {
				return (proctab[i].pid);
			}
		}
		break;

	case FIFO:

		/* your code here */
                for (int j = 0; j < globalclock; j++) {
                    for (i = 0; i < MAXPROCS; i++){
                        if (proctab[i].valid && proctab[i].timestamp == j) {
                            return (proctab[i].pid);
                        }    
                    }
                }
		break;

	case LIFO:

		/* your code here */
                for (int j = globalclock - 1; j >= 0; j--){
                    for (i = MAXPROCS - 1; i >= 0; i--){
                        if (proctab[i].valid && proctab[i].timestamp == j) {  
                            return (proctab[i].pid);
                        }
                    }    
                }
		break;

	case ROUNDROBIN:

		/* your code here */
                for (i = head; i <= last; i++) {
                    if (proctab[i].valid) {
                        head = i + 1; 
                        return (proctab[i].pid); 
                    }
                }

                for (i = 0; i <= head; i++) {
                    if (proctab[i].valid) {
                        head = i + 1;
                        return proctab[i].pid;
                    }    
                }    
		break;

	case PROPORTIONAL:

		/* your code here */  
                for (i = 0; i < MAXPROCS; i++) {
                    if (proctab[i].valid && proctab[i].pass < min) {
                        min = proctab[i].pass;
                        minI = i;
                    //Printf("PID: %d pass: %d\n", proctab[i].pid, proctab[i].pass);
                    }
                }

                proctab[minI].pass += proctab[minI].stride;
                if (proctab[minI].pass >= L) reset();
                //Printf("\nPass = %d\n", proctab[minI].pass);
                return (proctab[minI].pid);
                break;

	}
	
	return (0);
}


/*	HandleTimerIntr () is called by the kernel whenever a timer
 *	interrupt occurs.  
 */

void HandleTimerIntr ()
{
	SetTimer (TIMERINTERVAL);

	switch (GetSchedPolicy ()) {	// is policy preemptive?

	case ROUNDROBIN:		// ROUNDROBIN is preemptive
            DoSched();
            break;
        case PROPORTIONAL:		// PROPORTIONAL is preemptive

		DoSched ();		// make scheduling decision
		break;

	default:			// if non-preemptive, do nothing
		break;
	}
}

/*	MyRequestCPUrate (pid, n) is called by the kernel whenever a process
 *	identified by pid calls RequestCPUrate (n). This is a request for
 *	n% of CPU time, i.e., requesting a CPU whose speed is effectively
 *	n% of the actual CPU speed.  Roughly n out of every 100 quantums
 *	should be allocated to the calling process.  n must be greater than
 *	0 and must be less than or equal to 100. MyRequestCPUrate (pid, n)
 *	should return 0 if successful, i.e., if such a request can be
 *	satisfied, otherwise it should return -1, i.e., error (including if
 *	n < 1 or n > 100).  If MyRequestCPUrate (pid, n) fails, it should
 *	have no effect on scheduling of this or any other process, i.e., AS
 *	IF IT WERE NEVER CALLED.
 */

int MyRequestCPUrate (pid, n)
	int pid;			// process whose rate to change
	int n;				// percent of CPU time
{
	/* your code here */
        if (n < 0 || n > 100) return (-1);
        //Printf("PID:%d CPU: %d\n", pid, n);
        int h;
        for (h = 0; h < MAXPROCS; h++) {
            if (proctab[h].pid == pid) break;
        }

        if (proctab[h].request == 1 && n <= (uCPU + proctab[h].cpu)) {
            uCPU = (uCPU + proctab[h].cpu) - n;
            //Printf("r:%d\n", uCPU);
            rCPU = (rCPU - proctab[h].cpu) + n; 
        }
        else if (proctab[h].request == 0 && n <= uCPU) {
            uCPU -= n;
            //Printf("%d\n", uCPU);
            rCPU += n;
            numU -= 1;
            proctab[h].stride = L/n;
            //Printf("stride: %d\n",proctab[h].stride);
            proctab[h].request = 1;
            proctab[h].cpu = n;

        }
        else return (-1);
        if (numU > 0) distributeUCPU();
            // Printf("PID: %d;CPU: %d; UCPU: %d\n", proctab[i].pid, proctab[i].cpu, uCPU);
        
	
        return (0);
}

 void distributeUCPU() {
    int split = 0;
    int div = 0;

    if (uCPU == 0) {
        split = 0;
        div = 0;
    }

    else{
        split = uCPU/numU;
        div = L/split;
    }

    for (int i = 0; i < MAXPROCS; i++) {
        if (proctab[i].valid && proctab[i].request == 0) {
            if (div == 0) {
                proctab[i].stride = L;
                proctab[i].pass = L;
                proctab[i].cpu = 0;
            }
            else {
                proctab[i].stride = div;
                proctab[i].cpu = split;
            }        
        }
//Printf("PID: %d;CPU: %d; UCPU: %d\n", proctab[i].pid, proctab[i].cpu, uCPU);

    }
 }

void reset() {
    for (int i = 0; i < MAXPROCS; i++) {
        if (proctab[i].valid && proctab[i].cpu != 0) proctab[i].pass -= L;
                        //Printf("PID: %d pass: %d\n", proctab[i].pid, proctab[i].pass);
    }
}
 
