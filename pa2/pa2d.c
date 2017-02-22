//pa2d.c
#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main ()
{
	if (Fork () == 0) {//
		
		RequestCPUrate (30);				// process 2
		SlowPrintf (4, "222222222222222222");

		Exit ();
	}

	if (Fork () == 0) {

		RequestCPUrate (20);				// process 3
		SlowPrintf (4, "333333333333333333");
	
		Exit ();
	}
  
  if (Fork () == 0) {

			RequestCPUrate (10);			// process 4
			SlowPrintf (4, "444444444444444444");

			Exit ();
		}

  if (Fork () == 0) {

			                    			// process 5
			SlowPrintf (4, "555555555555555555");

			Exit ();
		}
  if (Fork () == 0) {

			RequestCPUrate (40);			// process 6
			SlowPrintf (4, "666666666666666666");

			Exit ();
		}

	RequestCPUrate (40);					// process 1
	SlowPrintf (4, "111111111111111111");
	
	Exit ();
}
