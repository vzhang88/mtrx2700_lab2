/******************************* SERIAL PORT OUTPUT SETUP *********************/
/* Set-up the Serial Port SCI0 to use interrupts */  
void Init_out_SCI0 (char* line) {
 
  SCI0BDH = 0x00;       // Configure the Baud Rate by writing to the Baud Rate register
  SCI0BDL = 0x9C;      
  SCI0CR1 = 0;          // Clear all options for SCI Control Register 1
  SCI0CR2 = 0xAC;       // Enable the transmitter (TE), receiver (RE) and receive interrupt enable (RIE) bits only
 
  sc0.ptr = line-1;      // Last inputted byte points to end of array
  sc0.dx = line;           // Transmitting byte points to start of array
  sc0.send = 1;
}  
