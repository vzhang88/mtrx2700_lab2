#include "serial.h"

#include <hidef.h> // common defines and macros 
#include "stdlib.h"

#include "derivative.h"   

void Init_SCI0 (void) {
  
 // set up serial port SCI0 to use interrupt
  SCI0BDH = 0x00;       // set up baud rate
  SCI0BDL = 0x9C;       // set up baud rate
  SCI0CR1 = 0x4C;       // clear all options
  SCI0CR2 = 0x2C;       // enable transmitter and receiver and receive interrupt
}













#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void SCI0_ISR(void) {

    if (SCI0SR1 & 0x20) {
    
        
    }
  
  
}