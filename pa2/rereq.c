//rereq.c
#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main() {
  RequestCPUrate(40);
  
  if( Fork() == 0 ) {
    RequestCPUrate( 50 );  
    SlowPrintf(7, "222222222222222222");
    Exit();
  }
  
  RequestCPUrate(50);
  
  if( Fork() == 0 ) {    
    SlowPrintf(7, "333333333333333333");
    Exit();
  }
  
  SlowPrintf(7, "111111111111111111");
  RequestCPUrate( 20 );

  SlowPrintf(7, "444444444444444444");
  Exit();
}
