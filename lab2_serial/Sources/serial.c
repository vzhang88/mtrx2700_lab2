#include "serial.h"

#include <hidef.h> // common defines and macros 
#include "stdlib.h"

#include "derivative.h"


char array[200];
char* ptr;
char cx;
char* dx;
char str[200] = "abcdefghijklmnop";


   
void Init_SCI0 (void) {
  
  // set up serial port SCI0 to use interrupt
  SCI0BDH = 0x00;       // set up baud rate
  SCI0BDL = 0x9C;       // set up baud rate
  SCI0CR1 = 0x4C;       // clear all options
  SCI0CR2 = 0x2C;       // enable transmitter and receiver and receive interrupt
  
  ptr = array;         // pointer points to start of array
  
  
  dx = array;
  return;
  
}


void putcSCI0 (char cx) {
 
  while (!(SCI0SR1 & 0x80));
  
    SCI0DRL = cx; 
  
}

void putsSCI0 (char *dx) {
 while (!(*dx)) {
    putcSCI0(*dx);
    dx++;
    
 }
}




void delay (int x) {
  int i;
  for (i = 0; i < x; i++) {
    int y = 0x00;
  }
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void SCI0_ISR(void) {
  

   
  while (SCI0SR1 & 0x20) {
  // read status register to reset flag
    
    
     
     cx = SCI0DRL;    // read SCI0DRL
     
     
     SCI0DRL = cx;    // show what has beeen entered on terminal
     
     if (cx != 0x0D) {    // not a carriage return
      
     
       *ptr = SCI0DRL;  // store character in array
       
         putcSCI0(*ptr);  
       
       if (cx == 0x08)  {  //if it is a backspace character
            
         ptr-- ;//move back string pointer
          
      
         //SCI0DRL = 0x20;
         putcSCI0(0x20);   //output a space
         putcSCI0(0x08);   // output a backspace
     
         
          
       } else {
        
         ptr++; // not a backspace, increment pointer by 1
                        
       }
       
    
      
     } 
     
      
     *ptr = 0;
     
     
  
  }  
  
  if ((SCI0SR1 & 0x80) && (dx != ptr)) {
  
    SCI0DRL = *dx;
    dx ++;
    
    SCI0SR1 & 0x7F;
    
  }
  
  
  
  
}


/*
char getch (void) {
  
  while(!(SCI0SR1 & RDRF));
  return(SCI0DRL);
}


int getsSCI0 (char *ptr) {
  
  char cx;
  
  while ((cx = getch()) != 0x0D) {
    *ptr = cx;
    putch(cx);
    
    if (cx == 0x08) { // is it a backspace character?
      ptr--; // move back the string pointer
      putch(0x20); // output a space
      putch(0x08); // output another backspace character
    }
    
    ptr++; // move buffer pointer
  }
  
  *ptr = 0; // terminate the string with a NULL character
  
  return 0;
}

*/
