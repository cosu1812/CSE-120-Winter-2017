//lifo.c
#include <stdio.h>
#include "aux.h"
#include "umix.h"

void Main( ) {
  if( Fork( ) == 0 ) {
    if( Fork( ) == 0 ) {
      Printf("A");
      Exit( );
    }  
    
    if( Fork( ) == 0 ) {
      if( Fork( ) == 0 ) {
        if( Fork( ) == 0 ) {
            Printf("B");
            Exit( );
          }
        if( Fork( ) == 0 ) {
          Printf("C");
          Exit( );
        }
        Printf("D");
        Exit( );
      }
      
      Printf("E");
      Exit( );
    }
    
    Printf("F");
    Exit( );
  }

  if( Fork( ) == 0 ) {
    if( Fork( ) == 0 ) {
      Printf("G");
      Exit( );
    }  
    if( Fork( ) == 0 ) {
      Printf("H");
      Exit( );
    }
    Printf("I");
    Exit( );
  }
  
  Printf("J");
  Exit();
}
