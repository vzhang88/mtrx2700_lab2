#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "stdlib.h"

#include "serial.h"


void main(void) {
  
  
  Init_SCI0();

	EnableInterrupts;
	


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
