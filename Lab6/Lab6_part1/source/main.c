/*    Author: Isaac Kang - ikang005
 *    Partner(s) Name:
 *    Lab Section:21
 *    Assignment: Lab #6  Exercise #1
 *    Exercise Description: [optional - include for your own benefit]
 *    Blink three LEDs
 *    I acknowledge all content contained herein, excluding tmplate or example
 *    code, is my own original work.
 */

//Demo:

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum States{Start, First, Second, Third}states;

void Tick(){
    switch(state){
        case Start:
            state = First;
            break;
        case First:
            state = Second;
            break;
        case Second:
            state = Third;
            break;
        case Third:
            state = First;
            break;
        default:
	    state = First;
            break;
    }
    switch(state){
        case Start:
            break;
        case First:
            PORTB = 0x01;
            break;
        case Second:
            PORTB = 0x02;
            break;
        case Third:
            PORTB = 0x04;
            break;
	default:
	    PORTB = 0x00;
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    TimerSet(1000);
    TimerOn();
    state = Start;
    
    while (1)
    {
        Tick();
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

