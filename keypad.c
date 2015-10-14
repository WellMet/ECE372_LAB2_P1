#include <xc.h>
#include "keypad.h"
#include "timer.h"

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    //set row pins as output
    TRISGbits.TRISG0 = OUTPUT;
    TRISDbits.TRISD9 = OUTPUT;
    TRISDbits.TRISD12 = OUTPUT;
    TRISDbits.TRISD6 = OUTPUT;
    
    //set col pins as input
    TRISBbits.TRISB10 = INPUT;
    TRISBbits.TRISB12 = INPUT;
    TRISBbits.TRISB14 = INPUT;
    
//    ANSELBbits.ANSB4 = 1;
//    ANSELBbits.ANSB2 = 1;
//    ANSELBbits.ANSB0 = 1;
    ANSELBbits.ANSB12 = 0;
    ANSELBbits.ANSB10 = 0;
    ANSELBbits.ANSB14 = 0;
    //enable ODC for the output pins
    ODCGbits.ODCG0 = 1;
    ODCDbits.ODCD9 = 1;
    ODCDbits.ODCD12 = 1;
    ODCDbits.ODCD6 = 1;
    
    //initialize outputs initially to zero
    LATGbits.LATG0 = 0;
    LATFbits.LATF1 = 0;
    LATDbits.LATD12 = 0;
    LATDbits.LATD6 = 0;
    
    //enable change notifications for the inputs
    CNCONBbits.ON=1;       // Turn on CN device
    CNENBbits.CNIEB10 = 1;       // Enable CN interrupt for pin
    CNENBbits.CNIEB12 = 1;
    CNENBbits.CNIEB14 = 1;
    IEC1bits.CNBIE = 1;
    IFS1bits.CNBIF = 0;
    IPC8bits.CNIP = 7;
    
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    char key = -1;
    
    //scan row 1
    ROW1 = 0, ROW2 = 1, ROW3 = 1, ROW4 = 1;
    if(COL1 == 0) 
        return '1';
    if(COL2 == 0) 
        return '2';
    if(COL3 == 0) 
        return '3';
    
    //scan row 2
    ROW1 = 1, ROW2 = 0, ROW3 = 1, ROW4 = 1;
    if(COL1 == 0) 
        return '4';
    if(COL2 == 0) 
        return '5';
    if(COL3 == 0) 
        return '6';
    
    //scan row 3
    ROW1 = 1, ROW2 = 1, ROW3 = 0, ROW4 = 1;
    if(COL1 == 0) 
        return '7';
    if(COL2 == 0) 
        return '8';
    if(COL3 == 0) 
        return '9';
 
    //scan row 4
    ROW1 = 1, ROW2 = 1, ROW3 = 1, ROW4 = 0;
    if(COL1 == 0) 
        return '*'; 
    if(COL2 == 0) 
        return '0';
    if(COL3 == 0) 
        return '#';
    
    return key;
}
