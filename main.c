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
#include "interrupt.h"
#define delay5 5 //delay 5ms debounce 
#define PRESS 0
#define RELEASE 1
// ******************************************************************************************* //
  typedef enum stateTypeEnum {
      scan, waitRelease, waitPress, debouncePress, debounceRelease, print
 
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

    x = 0;
    y = 0;
    state = waitPress;

    while(1)
    {
        switch(state){
            case (waitPress):
                break;
                
            case (debouncePress):
                delayUs(5000);
                state = scan;
                break;
                
            case (scan):
                ROW1 = 1, ROW2 = 1, ROW3 = 1, ROW4 = 1;
                key = scanKeypad();
                ROW1 = 0, ROW2 = 0, ROW3 = 0, ROW4 = 0;
                state = waitRelease;
                break;
            
            case (waitRelease):
                break;
                
            case (debounceRelease):
                delayUs(5000);
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
                state = waitPress;
                break;
            default:
                state = waitPress;
                break;
        }
    }    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
//implementation of the change notice ISR.  Sends the state machine into debounce modes
    IFS1bits.CNBIF = 0;
    
    int dummycol1 = COL1;
    int dummycol2 = COL2;
    int dummycol3 = COL3;
    
    //once the button is released enter the write state
    if((COL1 == PRESS || COL2 == PRESS || COL3 == PRESS) && state == waitPress){
        state = debouncePress;
    }
    else if(COL1 == RELEASE && COL2 == RELEASE && COL3 == RELEASE && state == waitRelease){
        state = debounceRelease;
    }
}