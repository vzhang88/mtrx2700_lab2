#ifndef SERIAL_HEADER
#define SERIAL_HEADER


void Init_SCI0 (void);

struct port {

    char array[200];
    char* ptr;
    char output[200];
    char*  outptr
    int  send;
};




__interrupt void SCI0_ISR(void);


 #endif 