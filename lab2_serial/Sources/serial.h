#ifndef SERIAL_HEADER
#define SERIAL_HEADER

//function to initialise serial SCI0
void Init_SCI0 (void);

void putcSCI0 (char cx);



// serial interrupt function
 
__interrupt void SCI0_ISR(void);



/*
char getch (void);

int getsSCI0 (char *ptr);
*/


#endif 