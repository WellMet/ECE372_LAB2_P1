/* 
 * File:   keypad.h
 * Author: user
 *
 * Created on February 5, 2015, 11:42 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H


void initKeypad(void);
char scanKeypad(void);

#define OUTPUT 0
#define INPUT 1
#define ROW1 LATGbits.LATG0
#define ROW2 LATFbits.LATF1
#define ROW3 LATDbits.LATD12
#define ROW4 LATDbits.LATD6
#define COL1 PORTBbits.RB4
#define COL2 PORTBbits.RB2
#define COL3 PORTBbits.RB0

#endif	/* KEYPAD_H */

