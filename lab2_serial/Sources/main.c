#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "stdlib.h"

#include "serial.h"

void main(void) {
  
  struct ports port; //declare port of type ports
  port.BDH_value = 0x00;
  port.BDL_value = 0x9C;
  port.CR1_value = 0x4C;
  port.CR2_value = 0xAC;
  
  Init_SCI0();

	EnableInterrupts;
	


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
