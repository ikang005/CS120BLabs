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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char tmp = 0x00;

enum States{Start, First, Second, Third}state;

void TimerOn(){
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}

void TimerOff(){
    TCCR1B = 0x00;
}

void TimerISR(){
    TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
    -_avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0){
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

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
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    TimerSet(1000);
    TimerOn();
    state = START;
    
    while (1)
    {
        Tick();
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

