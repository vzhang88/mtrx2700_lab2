#include "serial.h"

#include <hidef.h> // common defines and macros 
#include "stdlib.h"

#include "derivative.h"

/******************************* KEY VARIABLES *******************************/
struct port sc0;
/******************************* SERIAL PORT SETUP **************************/
/* Set-up the Serial Port SCI0 to use interrupts */   
void Init_SCI0 (void) {
 
  SCI0BDH = 0x00;       // Configure the Baud Rate by writing to the Baud Rate register
  SCI0BDL = 0x9C;       
  SCI0CR1 = 0;          // Clear all options for SCI Control Register 1 
  SCI0CR2 = 0x2C;       // Enable the transmitter (TE), receiver (RE) and receive 
                        // interrupt enable (RIE) bits only 
  
  sc0.ptr = sc0.array;         // pointer points to start of array
  sc0.dx =sc0.array; 
}

/******************************* HELPER FUNCTIONS ****************************/
/* Prints the character to the terminal */
void putcSCI0 (char cx) {
 
  while (!(SCI0SR1 & 0x80));
  
    SCI0DRL = cx; 
  
}

/******************************* SERIAL PORT OUTPUT SETUP *********************/
/* Set-up the Serial Port SCI0 to use interrupts */  
void Init_out_SCI0 (char* line) {
 
  SCI0BDH = 0x00;       // Configure the Baud Rate by writing to the Baud Rate register
  SCI0BDL = 0x9C;      
  SCI0CR1 = 0;          // Clear all options for SCI Control Register 1
  SCI0CR2 = 0xAC;       // Enable the transmitter (TE), receiver (RE) and receive interrupt enable (RIE) bits only
 
  int len = 0;
  char c = *line;
  while(c != 0) {
    line++;
    len++;
    c = *line;
  }
  
  sc0.ptr = line + len -1;      // Last inputted byte points to end of array
  sc0.dx = line;           // Transmitting byte points to start of array
  sc0.send = 1;
}  

#pragma CODE_SEG __NEAR_SEG NON_BANKED


__interrupt void SCI0_ISR(void) {

  /********************************* RECEIVING INPUT ********************************/                         
  
  /* Check the SCI0 Status Register 1 to see if the interrupt was triggered by a
  full receiver data register i.e. check if RDRF is set, in which case an interrupt 
  is requested to the MCU. This indicates that the received byte can be read */
  
  if (SCI0SR1 & 0x20) {
 
     
     sc0.cx = SCI0DRL;        // Read in the received byte in the data register SCI0DRL 
     
     if (sc0.cx != 0x0D) {    // Check if the received byte is not a carriage return character
          
       *(sc0.ptr) = SCI0DRL;    // Store the received byte in an entry of a container array specified 
                          // by the pointer  
       
       putcSCI0(*(sc0.ptr));    // Print the received byte to the terminal so we have an indication
                          // of what we are typing 
       
       if (sc0.cx == 0x08) {  // Check if the received byte is a backspace character 
            
         (sc0.ptr)-- ;//move back string pointer
         putcSCI0(0x20);   // Output a space
         putcSCI0(0x08);   // Output a backspace
          
       } else { 
           
         (sc0.ptr)++;           // Increment the pointer by one to point to the next entry in the array 
        
       }  
      
     } else {             // The received byte is a carriage return character 
       
       putcSCI0(sc0.cx);      // Print the carriage return character to terminal 
       *(sc0.ptr) = 0;          // Add a null terminator to the end of the sequence of characters 
       sc0.send = 1;          // Toggle the value of the boolean 'send' to indicate that we have sent a string across;             
       SCI0CR2 = 0xAC;    // Set the   BIG CHANGE HERE
                          
     }       
  }  
  
  /********************************* TRANSMITTING OUTPUT ***************************/    

  /* Check to see if the transmit data register empty flag (TDRE) is set, in which case the SCI data
  register transfers the currently stored byte to the transmit shift register */ 
  
  while ((SCI0SR1 & 0x80) && (sc0.send == 1)) {
  
    SCI0DRL = *(sc0.dx);       // Print the current character in the array 
    
    if ((sc0.dx) == (sc0.ptr)) {     // Check if the current character in the array points to the same character
                         // that was last entered into the data register
     sc0.send = 0;           // Toggle the boolean 'send' to 0 to indicate that we have finished sending
     SCI0CR2 = 0x2C;     // Enable the transmitter (TE), receiver (RE) and receive interrupt enable (RIE) bits 
     SCI0DRL = 0x0D;     // Print a carriage return character 
     break;              // Break out of the loop to indicate that we have finished transmitting
       
    }  
    (sc0.dx)++;                // Increment the pointer to inspect the next element in the array to be transmitted 
  }
}
