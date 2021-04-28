#ifndef SERIAL2_HEADER
#define SERIAL2_HEADER


//function to initialise serial SCI0
void Init_SCI1 (void);


void putcSCI1 (char cx);

void putsSCI1 (char *dx);





__interrupt void SCI1_ISR(void);



/*
char getch (void);

int getsSCI0 (char *ptr);
*/


#endif 