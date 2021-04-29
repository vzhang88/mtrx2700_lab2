#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "serial.h"

int overflow = 0;

#pragma CODE_SEG __NEAR_SEG NON_BANKED


__interrupt void TOF_ISR(void) {
     TFLG2 = 0x80;  
     overflow = 1; 
  
}


/*
int printSerial(int arr[4][6]){
    char str[100];
    char types[6][12] = {"Add", "Multiply", "Divide", "Squareroot", "Sin", "Cos"};

    // Make an array of strings 
    sprintf(str, "%11s %11s %11s %11s %11s %11s %11s", " ", "Add", "Multiply", "Divide", "Squareroot", "Sin", "Cos");
    
    // Send this string across serial 
    Init_out_SCI0(str);
    
    for(int i=0; i < 4; i++){
        sprintf(str, "%11s %11d %11d %11d %11d %11d %11d", types[i], arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5]);
        Init_out_SCI0(str);
    }
}
  */
  
void main(void) {
  /* put your own code here */  
  
  
  int tcnt1, tcnt2;
   
  int array[4][6] = {0};
  
  volatile int a = 3;
  volatile int b = 4;
  volatile int c;
  
  volatile long l = 3;
  volatile long m = 4;
  volatile long n;
  volatile float g = 1.5;
  volatile float h = 3.4;
  volatile float f;
  
  volatile double d = 1.5;
  volatile double e = 3.4;
  volatile double k;
  
  TSCR1 = 0x80;
  TSCR2 = 0x80;
  EnableInterrupts;
  
  /*********** TIMING FOR INT ********/ 
  
  tcnt1 = TCNT;   // Record the time before the operation 
  c = a + b;      // Perform the operation (addition) 
  tcnt2 = TCNT;   // Record the time after the operation (subtraction) 
  if(overflow == 1) {  // Check if the timer has overflowed 
    array[0][0] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;      // Reset the timer overflow flag to 0 
  }else{
    array[0][0] = tcnt2 - tcnt1;
  }
  
  /* Since the calculations are similar for different data types and 
  maths operations, we do not comment any further */ 
  
  tcnt1 = TCNT;
  c = a * b;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[0][1] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[0][1] = tcnt2 - tcnt1;
  }
  
  tcnt1 = TCNT;
  f = a / b;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[0][2] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[0][2] = tcnt2 - tcnt1;
  }
   
  tcnt1 = TCNT;
  f = sqrt(a);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[0][3] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[0][3] = tcnt2 - tcnt1;
  }
  
  
  tcnt1 = TCNT;
  f = sin(a);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[0][4] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[0][4] = tcnt2 - tcnt1;
  }
    
  tcnt1 = TCNT;
  f = cos(a);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[0][5] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[0][5] = tcnt2 - tcnt1;
  }
  
  
  /******* TIMING FOR LONG ***********/
  
  tcnt1 = TCNT;
  n = l + m;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[1][0] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[1][0] = tcnt2 - tcnt1;
  }
  
  tcnt1 = TCNT;
  n = l * m;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[1][1] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[1][1] = tcnt2 - tcnt1;
  }
  
  tcnt1 = TCNT;
  f = l / m;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[1][2] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[1][2] = tcnt2 - tcnt1;
  }
  
  
  tcnt1 = TCNT;
  f = sqrt(m);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[1][3] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[1][3] = tcnt2 - tcnt1;
  }
  
  
  tcnt1 = TCNT;
  f = sin(m);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[1][4] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[1][4] = tcnt2 - tcnt1;
  }
    
  tcnt1 = TCNT;
  f = cos(m);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[1][5] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[1][5] = tcnt2 - tcnt1;
  }
  
  
    
  /******* TIMING FOR FLOAT 32 ********/
  
  tcnt1 = TCNT;
  f = g + h;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[2][0] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[2][0] = tcnt2 - tcnt1;
  }
  
  tcnt1 = TCNT;
  f = g * h;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[2][1] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[2][1] = tcnt2 - tcnt1;
  }
  
  tcnt1 = TCNT;
  f = g / h;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[2][2] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[2][2] = tcnt2 - tcnt1;
  }
  
  
  tcnt1 = TCNT;
  f = sqrt(g);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[2][3] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[2][3] = tcnt2 - tcnt1;
  }
  
  
  tcnt1 = TCNT;
  f = sin(g);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[2][4] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[2][4] = tcnt2 - tcnt1;
  }
    
  tcnt1 = TCNT;
  f = cos(g);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[2][5] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[2][5] = tcnt2 - tcnt1;
  }
  
  /********** TIMING FOR FLOAT64 *********/
  
  tcnt1 = TCNT;
  k = d + e;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[3][0] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[3][0] = tcnt2 - tcnt1;
  }
  
  tcnt1 = TCNT;
  k = d * e;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[3][1] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[3][1] = tcnt2 - tcnt1;
  }
  
  tcnt1 = TCNT;
  k = d / e;
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[3][2] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[3][2] = tcnt2 - tcnt1;
  }
  
  
  tcnt1 = TCNT;
  k = sqrt(d);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[3][3] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[3][3] = tcnt2 - tcnt1;
  }
  
  
  tcnt1 = TCNT;
  k = sin(d);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[3][4] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[3][4] = tcnt2 - tcnt1;
  }
    
  tcnt1 = TCNT;
  k = cos(d);
  tcnt2 = TCNT;
  if(overflow == 1) {
    array[3][5] = 2^16 - tcnt1 + tcnt2;
    overflow = 0;
  }else{
    array[3][5] = tcnt2 - tcnt1;
  }
  
  
  /***** PRINTING TO SERIAL *******
  
  printSerial(array[][]);
  */

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
  
  
}

