//nomercy.c
#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main() {  
  RequestCPUrate(100); //process A
  
  if( Fork() == 0 ) { //Process B
    RequestCPUrate( 100 );  
    
     if( Fork() == 0 ) { //Process D
     RequestCPUrate( 100 );
       SlowPrintf(7, "44444");
       Exit();
     }
    
    SlowPrintf(7, "22222");
    Exit();
  }
  
  if( Fork() == 0 ) { //Process C
    SlowPrintf(7, "33333");
    Exit();
  }
  
  SlowPrintf(7, "11111");
  Exit();
}
