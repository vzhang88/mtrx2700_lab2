#ifndef SERIAL_HEADER
#define SERIAL_HEADER


// Function to initialise serial SCI0
void Init_SCI0 ();
 
// Interrupt Service Routine for SCI0 
__interrupt void SCI0_ISR(void);

struct port{
   char array[200];      // Container array that contains the input for the Serial Port 
   char* ptr;            // A pointer representing the last entered byte of input
   char cx;              // A temporary variable storing a character 
   char* dx;             // A pointer representing the current transmitted byte 
   int send;             // A boolean representing whether we have finished transmitting (0) or not (1) 
};


#endif 
