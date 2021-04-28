#include "serial.h"

#include <hidef.h> // common defines and macros 
#include "stdlib.h"

#include "derivative.h"

char array[200];
char* ptr;
char cx;
char* dx;
int send;  
struct serialPort sc0;
 

void main(void) {
  

  Init_SCI0();

	EnableInterrupts;
	
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}


/******************************* SERIAL PORT SETUP **************************/
/* Set-up the Serial Port SCI0 to use interrupts */   
void Init_SCI0 (void) {
 
  SCI0BDH = 0x00;       // Configure the Baud Rate by writing to the Baud Rate register
  SCI0BDL = 0x9C;       
  SCI0CR1 = 0;          // Clear all options for SCI Control Register 1 
  SCI0CR2 = 0x2C;       // Enable the transmitter (TE), receiver (RE) and receive 
                        // interrupt enable (RIE) bits only 
}

/******************************* HELPER FUNCTIONS ****************************/
/* Prints the character to the terminal */
void putcSCI0 (char cx) {
 
  while (!(SCI0SR1 & 0x80));
  
    SCI0DRL = cx; 
  
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED


__interrupt void SCI0_ISR(void) {

  /********************************* RECEIVING INPUT ********************************/                         
  
  /* Check the SCI0 Status Register 1 to see if the interrupt was triggered by a
  full receiver data register i.e. check if RDRF is set, in which case an interrupt 
  is requested to the MCU. This indicates that the received byte can be read */
  
  if (SCI0SR1 & 0x20) {
 
     
     cx = SCI0DRL;        // Read in the received byte in the data register SCI0DRL 
     
     if (cx != 0x0D) {    // Check if the received byte is not a carriage return character
          
       *ptr = SCI0DRL;    // Store the received byte in an entry of a container array specified 
                          // by the pointer  
       
       putcSCI0(*ptr);    // Print the received byte to the terminal so we have an indication
                          // of what we are typing 
       
       if (cx == 0x08) {  // Check if the received byte is a backspace character 
            
         ptr-- ;//move back string pointer
         putcSCI0(0x20);   // Output a space
         putcSCI0(0x08);   // Output a backspace
          
       } else { 
           
         ptr++;           // Increment the pointer by one to point to the next entry in the array 
        
       }  
      
     } else {             // The received byte is a carriage return character 
       
       putcSCI0(cx);      // Print the carriage return character to terminal 
       *ptr = 0;          // Add a null terminator to the end of the sequence of characters 
       send = 1;          // Toggle the value of the boolean 'send' to indicate that we have sent a string across;             
       SCI0CR2 = 0xAC;    // Set the   BIG CHANGE HERE
                          
     }       
  }  
  
  /********************************* TRANSMITTING OUTPUT ***************************/    

  /* Check to see if the transmit data register empty flag (TDRE) is set, in which case the SCI data
  register transfers the currently stored byte to the transmit shift register */ 
  
  while ((SCI0SR1 & 0x80) && (send == 1)) {
  
    SCI0DRL = *dx;       // Print the current character in the array 
    
    if (dx == ptr) {     // Check if the current character in the array points to the same character
                         // that was last entered into the data register
     send = 0;           // Toggle the boolean 'send' to 0 to indicate that we have finished sending
     SCI0CR2 = 0x2C;     // Enable the transmitter (TE), receiver (RE) and receive interrupt enable (RIE) bits 
     SCI0DRL = 0x0D;     // Print a carriage return character 
     break;              // Break out of the loop to indicate that we have finished transmitting
       
    }  
    dx++;                // Increment the pointer to inspect the next element in the array to be transmitted 
  }
}

