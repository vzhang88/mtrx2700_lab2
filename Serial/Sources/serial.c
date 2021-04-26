#include "serial.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


void Init_SCI0 (void) {

    SCI0BDH = 0x00; // set baud rate to 9600
    SCI0BDL = 0x9C; // divide factor 156 for baud rate 9600
    SCI0CR1 = 0x00; // 8 data bits, address mark wakeup
    SCI0CR2 = 0x2C; // enable transmitter, receiver, and receive interrupt
      
}

// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void SCI0_ISR(void) { 

      

}