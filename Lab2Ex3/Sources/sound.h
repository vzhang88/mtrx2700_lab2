#ifndef SOUND_HEADER
#define SOUND_HEADER

// Timer interrupt definition
interrupt 13 void TC5_ISR(void);

// function to initialise the timer
void Initialise(void);


void delay(int time);
void short_delay(int time);
void sound(void);



#endif