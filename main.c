// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "keypad.h"
#include "timer.h"
#include "config.h"
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#define delay5 5 //delay 5ms debounce 
#define PRESS 0
#define RELEASE 1
// ******************************************************************************************* //
  typedef enum stateTypeEnum {
      scan, waitRelease, print
 
} stateType;
volatile stateType state;
volatile char key;
volatile int x;
volatile int y;

int main(void)
{   
    
    enableInterrupts();
    initTimer2();
    initKeypad();
    initLCD();
    moveCursorLCD(0,0);
    //printStringLCD("WORK PLS!");
    
    x = 0;
    y = 0;
    state = scan;

    while(1)
    {
        switch(state){
            case (scan):
                key = scanKeypad();
                break;
            
            case (waitRelease):
                if(COL1 == 0 || COL2 == 0 || COL3 == 0)
                    state = waitRelease;
                else if(COL1 == 1 || COL2 == 1 || COL3 == 1)
                    state = print;
                break;
            
            case (print):
                moveCursorLCD(x, y);
                printCharLCD(key);
                if(x == 0 && y == 7){
                    x++;
                    y = 0;
                }
                else if(x == 1 && y == 7){
                   x = 0;
                   y = 0;
                }
                else{
                    y++;
                }
                break;
            default:
                state = scan;
                break;
        }
    }    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
//    //TODO: Implement the interrupt to capture the press of the button
//
    //delay 5us to debounce
    delayUs(5);
    
    IFS1bits.CNBIF = 0;
    
    int dummycol1 = COL1;
    int dummycol2 = COL2;
    int dummycol3 = COL3;
    
    //once the button is released enter the write state
    if((COL1 == 0 || COL2 == 0 || COL3 == 0) && state == scan){
        state = waitRelease;
    }
}