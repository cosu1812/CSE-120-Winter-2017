#include "aux.h"
#include "umix.h"
#include "mythreads.h"

#define NUMYIELDS	5

void Main ()
{
	MyInitThreads ();

	int me = MyGetThread ();

  int i;
	for (i = 0; i < NUMYIELDS; i++) {
		MyYieldThread (me);
		Printf ("currThread: %d  i: %d\n", MyGetThread(), i);
	}

	MyExitThread ();
}
