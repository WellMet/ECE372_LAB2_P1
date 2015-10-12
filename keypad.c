#include <xc.h>
#include "keypad.h"
#include "timer.h"

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    //set row pins as output
    TRISGbits.TRISG0 = OUTPUT;
    TRISFbits.TRISF1 = OUTPUT;
    TRISDbits.TRISD12 = OUTPUT;
    TRISDbits.TRISD6 = OUTPUT;
    
    //set col pins as input
    TRISBbits.TRISB4 = INPUT;
    TRISBbits.TRISB2 = INPUT;
    TRISBbits.TRISB0 = INPUT;
    
    ANSELBbits.ANSB4 = 1;
    ANSELBbits.ANSB2 = 1;
    ANSELBbits.ANSB0 = 1;
    
    //enable ODC for the output pins
    ODCGbits.ODCG0 = 1;
    ODCFbits.ODCF1 = 1;
    ODCDbits.ODCD12 = 1;
    ODCDbits.ODCD6 = 1;
    
    //initialize outputs initially to zero
    LATGbits.LATG0 = 0;
    LATFbits.LATF1 = 0;
    LATDbits.LATD12 = 0;
    LATDbits.LATD6 = 0;
    
    //enable change notifications for the inputs
    CNCONBbits.ON=1;       // Turn on CN device
    CNENBbits.CNIEB4 = 1;       // Enable CN interrupt for pin
    CNENBbits.CNIEB2 = 1;
    CNENBbits.CNIEB0 = 1;
    IEC1bits.CNBIE = 1;
    IFS1bits.CNBIF = 0;
    
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
    ROW1 = 1, ROW2 = 0, ROW3 = 0, ROW4 = 0;
    if(COL1 == 0) key = 1;
    if(COL2 == 0) key = 2;
    if(COL3 == 0) key = 3;
    
    //scan row 2
    ROW1 = 0, ROW2 = 1, ROW3 = 0, ROW4 = 0;
    if(COL1 == 0) key = 4;
    if(COL2 == 0) key = 5;
    if(COL3 == 0) key = 6;
    
    //scan row 3
    ROW1 = 0, ROW2 = 0, ROW3 = 1, ROW4 = 0;
    if(COL1 == 0) key = 7;
    if(COL2 == 0) key = 8;
    if(COL3 == 0) key = 9;
 
    //scan row 4
    ROW1 = 0, ROW2 = 0, ROW3 = 0, ROW4 = 1;
    if(COL1 == 0) key = '*'; //10 means *
    if(COL2 == 0) key = 0; //
    if(COL3 == 0) key = '#'; //11 means #
    
    return key;
}
