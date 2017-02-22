//iof.c
#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main( ) {
  if( Fork( ) == 0 ) {
    RequestCPUrate( 1 );
    SlowPrintf( 8, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
    Exit( );
  }
  
  RequestCPUrate( 1 );
  SlowPrintf(8, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  Exit( );
}
