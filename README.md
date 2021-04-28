# Lab 2: C coding for microcontrollers
## Members

## Exercise 2: Serial Module
The program uses the serial module to receive and transmit to serial in the background through interrupts. The functions used in the program are the Init_SCI which initialises the serial through setting up the baud rate and control register values, the interrupt service routine which defines what happens when the serial interrupt occurs, and the putcSCI function, where the entered character is taken and printed to the terminal if TDRE flag is low. THe paramters used in serial receiving and transmitting are the array where the received string is stored, the pointer to the input, the pointer to the intended output when transmitting, and the send flag. These are saved in a struct.

When the terminal is opened and a string is entered, the enabled receive interrupt for serial will trigger an interrupt service routine. This will save each character to an array. This is all done in the serial.c module, connected to main.c with the serial.h header. The main function only has the purpose of initialising and then enabling the interrupts, and then waiting in a loop for any interrupts to occur. The initialise function calls the function in serial.c.

As each character is entered, the interrupt service routine checks the Status Register 1 value for the RDRF and TDRE flags. The RDRF flag is set, so the received byte will be read in and saved to array pointed to by pointer. It then uses the putc function to print the character to the terminal so there is an indication of what has been typed. 

Once every character from the string is entered, the user presses enter. Within the interrupt service routine this will result in the character being printed but not saved to the array, and a NULL terminator added to the end of the string. The send value is toggled to indicate that a string has been sent across and the transmit interrupt is enabled.

The serial interrupt service routine then checks for the TDRE flag and if both the TDRE flag and the send flag are high, then it will go to the saved array and print the character pointed to by the output pointer. This will loop through until the output pointer reaches the input pointer at the end of the array and the send flag will be toggled back to zero, a carriage return is printed and the transmit interrupt is diabled, with receive interrupt still enabled.

### User Instructions
Input any valid string to terminal and press enter. The string will save to array and be printed again underneth the entered string.

### Testing
After running the program and entering a string to terminal, spc array to inspect what has been saved to the array is the intended input string. For earlier deugging, spc the values set when initialising serial by spc SCI0CR1 etc. To test the output string is correct, simply press enter and see if what is printed again to terminal is exactly the same as what has been entered and that it will only print once not repeatedly.
