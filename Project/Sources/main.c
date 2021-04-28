#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "stdlib.h"

#include "serial2.h"

void main(void) {
  

  
  
  Init_SCI1();

	EnableInterrupts;
	


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
