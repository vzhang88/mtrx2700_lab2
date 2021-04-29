#include "sound.h"
#include <string.h>
#include "derivative.h" 

// 7 Song Notes
#define R 65977     //Rest note                
#define C 22934
#define D 20431
#define E 18202
#define F 17181
#define G 15306
#define A 13636
#define B 12149

#define Q 0     //End Song Flag

int numbers[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};    //Layout in the seven seg for 0-9 in hex form

//routing to each seven segment display
#define SEGONE  0x0E   
#define SEGTWO  0x0D
#define SEGTHREE 0x0B
#define SEGFOUR  0x07

// London bridge defined in a string
int song[] = {G,A,G,F,E,F,G,R,D,E,F,R,E,F,G,R,G,A,G,F,E,F,G,R,D,D,G,G,E,C,R,R,Q};  // 15 notes to each song


// Global Value for changing the note 
int musicNote = 0;


// Interrupt for note update to TC5
#pragma CODE_SEG __NEAR_SEG NON_BANKED          
interrupt 13 void TC5_ISR(void){

    TC5   = TC5 + musicNote;             // Update to TC5 
    TFLG1 = 0x20;                        // Reset main timer interupt flag                   
} 


//Initialise TC5 and Seven Segment
void Initialise(void){
 
    DDRB = 0xFF;        //  PORTB Output
    DDRP = 0xFF;        //  PORTP Output to Seven Segment Display
    DDRJ = 0xFF;        //  PORTJ Output
    PTP  = 0x00;
    PTJ  = 0xFF;
   
   
    TSCR1 = 0x80;       // Timer Enable
    TIOS  = 0x20;       // Select Channel 5 for output compare
    TCTL1 = 0x04;       // Toggle PT5 pin
    TIE   = 0x20;       // Enable Interrupt for Channel 5
    TFLG1 = 0x20;       // Clear C5F
  
    return;
}


//Delay function
void delay(int time) 
{
   int i;             
   int j =time*200;   //delay is in half notes where 400 cycles = 1 second
   
   TSCR1 = 0x80;       // Enable Timer
   TSCR2 = 0x00;       // No interrupts
                                            
   for(i=0; i<j; ++i) {                  
      TFLG2 = 0x80;                           // Clear TOF
      while(!(TFLG2 & TFLG2_TOF_MASK));       // Wait for overflow flag to be raised 
   }
}

//Delay for Showing multiple numbers across the seven seg
void short_delay(int time) 
{
   
   int i;                             
   int j =time*4;          //1/100 of a second so unable to see the change in digit
   
   TSCR1 = 0x80;                            // Enable Timer
   TSCR2 = 0x00;                            // No interrupts
                                            // Count Value
   for(i=0; i<j; ++i) {                  
      TFLG2 = 0x80;                           // Clear TOF
      while(!(TFLG2 & TFLG2_TOF_MASK));       // Wait for overflow flag to be raised 
   }
}


//Main function for playing sound
void sound(void) 
{
  
    int i,j;
    int count =0;             // Counter for number of notes in song
    int big;
      
      for(i=0; i<240;i++){   //count the number of notes until the finish flag is reached
       
        if(song[i] ==Q){
        break;
        }
        count++;
      }
      
                                                       
      
      for(i = 0; i < 240; i++){         //loop through the notes in the song
         
         
        count--;                     //Count down to end of song               
        if(song[i] ==Q){                //First check if the End flag has been reached
          TCTL1 = 0x0;
          break; 
        }
        
        musicNote = song[i];             //Set the current note as the music note
                                         //The interrupt 
        big = count/10;                  //This number is to get the second digit of the count
        
          if(count > 9){                  //For numbers greater than 9 use the next segment
            for(j=0; j<25;j++){           
              
             PTP = SEGFOUR;                   //Route the output to 4th 7-seg
             PORTB = numbers[count-big*10];   //Display the end digit
             short_delay(1);                  //Delay the change in digit for 1/100 of a second
             PTP = SEGTHREE;                  //Route the output to the 3rd 7-seg
             PORTB = numbers[big];            //Display the 2nd digit
             short_delay(1);                  //Delay the change in digit for 1/100 of a second
            }
           }
            if(count <= 9){                   //For numbers 9-0
             PTP = SEGFOUR;                   //Route the output to 4th 7-seg
             PORTB = numbers[count];          //Display the current Digit
             delay(1);                        //Hold display for 1 beat before advancing
            }                
         
       }



} 



