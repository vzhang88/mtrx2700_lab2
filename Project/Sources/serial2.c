
#include "serial2.h"

#include <hidef.h> // common defines and macros 
#include "stdlib.h"

#include "derivative.h"


char array2[200];
char* ptr2;
char cx2;
char* dx2;

   
void Init_SCI1 (void) {
  
  // set up serial port SCI0 to use interrupt
  SCI1BDH = 0x00;       // set up baud rate
  SCI1BDL = 0x9C;       // set up baud rate
  SCI1CR1 = 0x4C;       // clear all options
  SCI1CR2 = 0xAC;       // enable transmitter and receiver and receive interrupt
  
  ptr2 = array2;         // pointer points to start of array

  dx2 = array2;
  return;
  
}


void putcSCI1 (char cx) {
 
  if (!(SCI1SR1 & 0x80)) {
  
    SCI1DRL = cx; 
  }
}

void putsSCI1 (char *dx) {
 while (!(*dx)) {
    putcSCI1(*dx);
    dx++;
    
 }
}






#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void SCI1_ISR(void) {
  
  
  if (SCI1SR1 & 0x20) {
  // read status register to reset flag
    
     
     cx2 = SCI1DRL;    // read SCI0DRL
     
     
     SCI1DRL = cx2;    // show what has beeen entered on terminal
     
     if (cx2 != 0x0D) {    // not a carriage return
      
     
       *ptr2 = SCI1DRL;  // store character in array
       
         putcSCI1(*ptr2);  
       
       if (cx2 == 0x08)  {  //if it is a backspace character
            
         ptr2-- ;//move back string pointer
          
      
         //SCI0DRL = 0x20;
         putcSCI1(0x20);   //output a space
         putcSCI1(0x08);   // output a backspace
     
         
          
       } else {
        
         ptr2++; // not a backspace, increment pointer by 1
                        
       }
       
    
      
     } 
     
      
     *ptr2 = 0;
     
     
  
  }    
  
  
  
  if (SCI1SR1 & 0x80) {
      
     // write operation
     putsSCI1 (dx2);
      

  }
  
  
  
}



