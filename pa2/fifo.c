//fifo.c
#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main( ) {
  if( Fork( ) == 0 ) {
    if( Fork( ) == 0 ) {
      Printf("D");
      Exit( );
    }  
    
    if( Fork( ) == 0 ) {
      if( Fork( ) == 0 ) {
        if( Fork( ) == 0 ) {
            Printf("I");
            Exit( );
          }
        
        if( Fork( ) == 0 ) {         
          
          Printf("J");
          Exit( );
        }
        Printf("H");
        Exit( );
      }
      
      Printf("E");
      Exit( );
    }
    
    Printf("B");
    Exit( );
  }

  if( Fork( ) == 0 ) {
    if( Fork( ) == 0 ) {
      Printf("F");
      Exit( );
    }  
    if( Fork( ) == 0 ) {
      Printf("G");
      Exit( );
    }
    Printf("C");
    Exit( );
  }
  
  Printf("A");
  Exit();
}
