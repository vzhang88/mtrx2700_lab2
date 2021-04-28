# Lab 2: C coding for microcontrollers
## Members

The team comprises of Jack Allsop, Reihanna Tsao and Vincent Zhang. Jack was in charge of designing and implementing the solution for Exercise 3. Reihanna was in charge of designing and implementing the solution for Exercise 2. Vincent was in charge of designing and implementing the solution for Exercise 1 and managing the minutes and helping out on Exercise 2. 

## Repository Structure 

There is one primary file, main.c (contained in the Projects folder) which contains all of the functionality for all three exercises. The demonstration order of the exercises was chosen to be: Exercise 1 (Timing), Exercise 3 (Audio) and Exercise 2 (Serial Module). There is one main function within main.c (the main function), which initialises variables that are necessary for further questions such as serial communication and represents the starting point for each of the questions. In addition to the project, there is also a separate folder for minutes, where minutes have been taken and converteed into PDF format. 



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

The module is created in the file sound.c, and the functions are linked to the main.c file with the header file sound.h. Inside the main.c file contains the enabling of the ports for the LED and the ports for the speaker, titled "Initialise". Interrupts are turned off before intiailising and then on again after. The main.c file then calls upon the sound function wher the rest of the sound module lies. 

The Sound function will play a tune found within a predefined string located in the sound.c file. It first counts through the string to see how many notes there are. Then the function will enter the main for loop to run through the notes one by one. First, within the for loop, the count is decreased by one. Then the current note in the string is polled to see if it the end of song flag. If so then the speakers are turned off and the for loop is broken, ending the sound function and returning to the main.c file. Otherwise, the function will update the note in the string titled “song[i]” to the variable “musicNote”. This will trigger the interupt.

The interrupt is trigger when the music note value is updated, and in turn will add the value of the note applied to the base operating frequency of the speaker. Then the flag on the timer is reset to allow for the interrupt to be triggered again.

The second part of the main for loop is the display for the number of notes left on the 7 segment display. The notes run on the average song speed of 120bpm where one note takes up half a second. If the number of notes left has two digits, the ouput will switch between the digits every 0.04 of a second, 25 times to reach 0.5 of a second. Otherwise if there is just one digit, a half second delay is added after displaying the number.

## User instructions:
Start the code by changing the function variable number to 3, and then run the debugger. The number 0 will hold at the end of the runtime and it must be reset before running again. To change the song, update the notes in the song string found in the sound.c file. 
## Testing:
After the debugger is run, the sound should play and the countdown on the notes left should run automatically.
