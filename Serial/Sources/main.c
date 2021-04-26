#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "serial.h"

void main(void) {
  
  DDRB = 0xFF; //port B output
  DDRJ = 0xFF; //port P output
  PTJ = 0x00; // enable LEDS
  
  PORTB = 0x0F; //debugging
  
  // call the initialise serial function
  Init_SCI0();

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
