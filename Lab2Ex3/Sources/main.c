#include <hidef.h>
#include "derivative.h"
#include "stdlib.h"

#include "sound.h"
#include "serial.h"


int function = 3;
  


void main(void){

Init_SCI0();






if(function ==3){
  
  __asm(sei);     //Disable Interrupts
  Initialise();     //Initialise Outputs
  __asm(cli);      //Enable Interrupts

  sound();         //Run play sound function
   
}
  
  
   
   for(;;) {
    _FEED_COP();
  }
  
  
}