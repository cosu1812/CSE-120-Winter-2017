/*	User-level thread system
 *
 */

#include <setjmp.h>
#include <string.h>
#include "aux.h"
#include "umix.h"
#include "mythreads.h"

static int MyInitThreadsCalled = 0;	// 1 if MyInitThreads called, else 0

static struct thread {			// thread table
	int valid;			// 1 if entry is valid, else 0
	jmp_buf env;			// current context
        int next;
        int prev;
        jmp_buf initial;
        void (*func)();			// function to be executed
	int param;	
} thread[MAXTHREADS];
static int curr;
static int lastAssign;
static int head;
static int tail;
static int exit;
static int last;
//void printQueue();
#define STACKSIZE	65536		// maximum size of thread stack


void printqueue(){
    int j = head;
    while (thread[j].next){
        DPrintf("Thread: %d, prev: %d, next: %d\n", j, thread[j].prev, thread[j].next);
        j = thread[j].next;
    }
}
/*	MyInitThreads () initializes the thread package. Must be the first
 *	function called by any user program that uses the thread package.  
 */
void enqueue(int i){
     thread[tail].next = i;
     thread[i].prev = tail;
     thread[i].next = -1;
     tail = i;
    
}

void dequeue(int i){
    if (i == head){
       head = thread[i].next;
        thread[head].prev = -1; 
    }
    else if (i == tail){
        tail = thread[i].prev;
        thread[tail].next = -1;
    }
    else {
        int temp = thread[i].next;
        thread[i].next = thread[temp].next;
        thread[thread[temp].next].prev = i;
    }
}

void insertBegin(int i) {
    thread[i].prev = -1;
    thread[i].next = head;
    thread[head].prev = i;
    head = i;

}
void MyInitThreads ()
{
	int i;

	if (MyInitThreadsCalled) {		// run only once
		Printf ("InitThreads: should be called only once\n");
		Exit ();
	}

	for (i = 0; i < MAXTHREADS; i++) {	// initialize thread table
		thread[i].valid = 0;
                thread[i].next = -1;
                thread[i].prev = -1;
                thread[i].func = NULL;
                thread[i].param = -1;
	}
	
        thread[0].valid = 1;			// initialize thread 0 
        curr = 0;
        head = 0;
        tail = 0;
        exit = 0;
        last = 0;
        int t;
        if (setjmp(thread[0].initial) == 0) { 
            //memcpy(thread[0].env, thread[0].env, sizeof(thread[0].env));
            for (int j = 0; j < MAXTHREADS; j++){
                char s[j * STACKSIZE];
                if (((int) &s[STACKSIZE-1]) - ((int) &s[0]) + 1 != STACKSIZE) {
	            Printf ("Stack space reservation failed\n");
		    Exit ();
	        }

                if ((t = setjmp(thread[j].initial)) == 0) {
                //DPrintf("==\n");
                    //memcpy(thread[j].initial, thread[j].env, sizeof(jmp_buf));
                }
            
                else {
                    //DPrintf("!=\n");
                    
                    void (*f)() = thread[MyGetThread()].func;
                    int p = thread[MyGetThread()].param;
                    //if (setjmp(thread[j].env) == 0) {
                       //Printf("exit %d\n", MyGetThread());
         //int d = MyInitThreadsCalled;
         //DPrintf("%d\n", d);  
                   //     longjmp(thread[MyGetThread()].env, j);
                    //}
                    //else {
                //Printf("fd");
                    (*f) (p);
                    MyExitThread(); 
                }
            }
        }
        else {
           (*thread[0].func) (thread[0].param);
           DPrintf("0s\n");
           MyExitThread();
        }
	MyInitThreadsCalled = 1;
}

/*	MyCreateThread (func, param) creates a new thread to execute
 *	func (param), where func is a function with no return value and
 *	param is an integer parameter.  The new thread does not begin
 *	executing until another thread yields to it. 
 */

int MyCreateThread (func, param)
	void (*func)();			// function to be executed
	int param;			// integer parameter
{
	if (! MyInitThreadsCalled) {
		Printf ("CreateThread: Must call InitThreads first\n");
		Exit ();
	}
        int i;
	//if (setjmp (thread[0].env) == 0) {	// save context of thread 0
        //Printf("start");
        //if (setjmp(thread[MyGetThread()].env) == 0) { 
		/* The new thread will need stack space.  Here we use the
		 * following trick: the new thread simply uses the current
		 * stack, and so there is no need to allocate space.  However,
		 * to ensure that thread 0's stack may grow and (hopefully)
		 * not bump into thread 1's stack, the top of the stack is
		 * effectively extended automatically by declaring a local
		 * variable (a large "dummy" array). This array is never
		 * actually used; to prevent an optimizing compiler from
		 * removing it, it should be referenced.  
		 */

		//char s[STACKSIZE];	// reserve space for thread 0's stack
		//void (*f)() = func;	// f saves func on top of stack
		//int p = param;		// p saves param on top of stack
            
		/*if (((int) &s[STACKSIZE-1]) - ((int) &s[0]) + 1 != STACKSIZE) {
			Printf ("Stack space reservation failed\n");
			Exit ();
		}*/
              	/*if (setjmp (thread[1].env) == 0) {	// save context of 1
			longjmp (thread[0].env, 1);	// back to thread 0
		}*/
                //Printf("ss"); 
                 int found = 0;
                 for (i = lastAssign + 1; i < MAXTHREADS; i++){
                    if (thread[i].valid == 0) {
                        found = 1;
                        break;
                    }
                 }
                 
                 if (found == 0){
                    for (i = 0; i <= lastAssign; i++){
                        if (thread[i].valid == 0) {
                            found = 1;
                            break;
                        }
                    }
                 }
                 
                 int j = head;
                 while (j != tail){
                    //DPrintf("Thread: %d\n", j);
                    j = thread[j].next;
                 }

                 if (found == 0) {
                     //DPrintf("noslot");
                     return -1;
                 }
                 
                 thread[i].func = func;
                 thread[i].param = param;
                 enqueue(i);
                 //longjmp(thread[i].env, i);
//Printf("create %d\n", i);
                memcpy(thread[i].env, thread[i].initial, sizeof(jmp_buf));              
		/* here when thread 1 is scheduled for the first time */

					// execute func (param)
                //(*func) (param);
		//MyExitThread ();		// thread 1 is done - exit
	//}
        
	//thread[1].valid = 1;	// mark the entry for the new thread valid
        
            thread[i].valid = 1; 
            lastAssign = i;
        
          printqueue();
	return (i);		// done, return new thread ID
}

/*	MyYieldThread (t) causes the running thread, call it T, to yield to
 *	thread t.  Returns the ID of the thread that yielded to the calling
 *	thread T, or -1 if t is an invalid ID. Example: given two threads
 *	with IDs 1 and 2, if thread 1 calls MyYieldThread (2), then thread 2
 *	will resume, and if thread 2 then calls MyYieldThread (1), thread 1
 *	will resume by returning from its call to MyYieldThread (2), which
 *	will return the value 2.
 */

int MyYieldThread (t)
	int t;				// thread being yielded to
{
        int s;
        //Printf("yt");
        if (! MyInitThreadsCalled) {
		Printf ("YieldThread: Must call InitThreads first\n");
		Exit ();
	}

	if (t < 0 || t >= MAXTHREADS) {
		Printf ("YieldThread: %d is not a valid thread ID\n", t);
		return (-1);
	}
	
        if (! thread[t].valid) {
		Printf ("YieldThread: Thread %d does not exist\n", t);
		return (-1);
	}
        //printqueue(); 
        last = MyGetThread();
        if (MyGetThread() == t) return t;                
       
        if (s = setjmp (thread[MyGetThread()].env) == 0) {
            if (thread[MyGetThread()].valid == 1) { 
                thread[thread[MyGetThread()].next].prev = thread[MyGetThread()].prev;
                //thread[thread[MyGetThread()].prev].next = thread[MyGetThread()].next;
                dequeue(MyGetThread());
                enqueue(MyGetThread()); 
                dequeue(t);
                insertBegin(t);/*
                if (thread[t].next == -1){
                    thread[t].prev = -1;
                }
                else {
                    int temp = thread[t].next;
                    thread[t].next = temp;
                    thread[thread[t].next].prev = t;
                    //thread[thread[t].prev].next = thread[t].next;
                }
                thread[t].prev = -1;
                thread[t].next = head;
                thread[head].prev = t;
                head = t;
                tail = MyGetThread();*/
            }

        curr = t;

                longjmp (thread[t].env, t);
            //}

        }
        return last;
}

/*	MyGetThread () returns ID of currently running thread.  
 */

int MyGetThread ()
{
	if (! MyInitThreadsCalled) {
		Printf ("GetThread: Must call InitThreads first\n");
		Exit ();
	}
        return curr;

}

/*	MySchedThread () causes the running thread to simply give up the
 *	CPU and allow another thread to be scheduled.  Selecting which
 *	thread to run is determined here. Note that the same thread may
 * 	be chosen (as will be the case if there are no other threads).  
 */

void MySchedThread ()
{
	if (! MyInitThreadsCalled) {
		Printf ("SchedThread: Must call InitThreads first\n");
		Exit ();
	}
        DPrintf("sched\n");
        //MyYieldThread(head);
        if (exit) {
            exit = 0;
            DPrintf("head:%d\n",head);
            MyYieldThread(head);
            //longjmp(thread[MyGetThread()].env, MyGetThread());
        }

        else {
            int i = thread[MyGetThread()].next;
            if (i == -1)  MyYieldThread(MyGetThread());
            else {
                curr = i;
                MyYieldThread(i);   
            }
        }
}

/*	MyExitThread () causes the currently running thread to exit.  
 */

void MyExitThread ()
{
	if (! MyInitThreadsCalled) {
		Printf ("ExitThread: Must call InitThreads first\n");
		Exit ();
	}
        
        int i = MyGetThread();
            thread[i].valid = 0; 
            
            //thread[thread[i].prev].next = thread[i].next;
            thread[thread[i].next].prev = -1;
                       //curr = thread[i].next;
            head = thread[i].next;
            DPrintf("prev: %d\n", thread[i].prev); 
            thread[i].next = -1;
            thread[i].prev = -1;
        
        memcpy(thread[i].env, thread[i].initial, sizeof(jmp_buf)); 
        printqueue(); 
        int zeroThread = 0;
        for (int j = 0; j < MAXTHREADS; j++){
            if (thread[j].valid == 0) {
                zeroThread = 1;
            }
            else{
                zeroThread = 0;
                break;
            }
        }
        
        if (zeroThread) {
            //DPrintf("nothread");
            Exit();
        }    
        else {
            exit = 1;
            MySchedThread();
        }
}


