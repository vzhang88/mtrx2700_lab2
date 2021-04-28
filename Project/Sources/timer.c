#include "timer.h"

#include <hidef.h> // common defines and macros 
#include "stdlib.h"

#include "derivative.h"




#pragma CODE_SEG __NEAR_SEG NON_BANKED


__interrupt void TOF_ISR(void) {
     TFLG2 = 0x80;  
     overflow = 1; 
  
}