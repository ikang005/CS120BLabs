/*    Author: Isaac Kang
 *    Partner(s) Name:
 *    Lab Section: 21
 *    Assignment: Lab #10  Exercise #1
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

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
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

enum ThreeStates{Start, s1, s2, s3}ThreeState;
enum BlinkingStates{ON, OFF}BlinkingState;
enum CombineStates{OUT}CombineState;

unsigned char threeLEDs;
unsigned char blinkingLED;


void ThreeLEDsSM(){
    switch(ThreeState){
        case Start:
            ThreeState = s1;
            break;
        case s1:
            ThreeState = s2;
            break;
        case s2:
            ThreeState = s3;
            break;
        case s3:
            ThreeState = s1;
            break;
        default:
            ThreeState = s1;
            break;
    }
    switch(ThreeState){
        case Start:
            break;
        case s1:
            threeLEDs = 0x01;
            break;
        case s2:
            threeLEDs = 0x02;
            break;
        case s3:
            threeLEDs = 0x04;
            break;
        default:
            break;
    }
}

void BlinkingLEDSM(){
    switch(BlinkingState){
        case ON:
            BlinkingState = OFF;
            break;
        case OFF:
            BlinkingState = ON;
            break;
        default:
            BlinkingState = ON;
            break;
    }
    switch(BlinkingState){
        case ON:
            blinkingLED = 0x08;
            break;
        case OFF:
            blinkingLED = 0x00;
            break;
        default:
            break;
    }
}

void CombineLEDsSM(){
    switch(CombineState){
        case OUT:
            CombineState = OUT;
            break;
        default:
            CombineState = OUT;
            break;
    }
    switch(CombineState){
        case OUT:
            PORTB = threeLEDs | blinkingLED;
            break;
        default:
            break;
    }
}

int main(void)
{
    DDRB = 0xFF; PORTB = 0x00;
    
    TimerSet(1000);
    TimerOn();
    
    threeLEDs = 0x00;
    blinkingLED = 0x00;
    
    ThreeState = Start;
    BlinkingState = ON;
    CombineState = OUT;
    
    while(1){
        ThreeLEDsSM();
        BlinkingLEDSM();
        CombineLEDsSM();
        
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 0;
}

