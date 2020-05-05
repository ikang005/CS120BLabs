/*    Author: Isaac Kang - ikang005
 *    Partner(s) Name:
 *    Lab Section:21
 *    Assignment: Lab #6  Exercise #2
 *    Exercise Description: [optional - include for your own benefit]
 *    Blink three LEDs Game (Stop the light)
 *    I acknowledge all content contained herein, excluding tmplate or example
 *    code, is my own original work.
 */

//Demo:

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, First, Second, Third, Wait, Restart}state;
unsigned char button;
unsigned char path;
unsigned char B;
unsigned char button_pressed;

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
            if(button == 0x01 && button_pressed == 0){
                state = Wait;
            }
            else{
                if(button == 0x00){
                    button_pressed = 0;
                }
                state = Second;
            }
            break;
        case Second:
            if(button == 0x01 && button_pressed == 0){
                state = Wait;
            }
            else{
                if(path == 1){
                    if(button == 0x00){
                        button_pressed = 0;
                    }
                    state = Third;
                }
                else{
                    if(button == 0x00){
                        button_pressed = 0;
                    }
                    state = First;
                }
            }
            break;
        case Third:
            if(button == 0x01 && button_pressed == 0){
                state = Wait;
            }
            else{
                if(button == 0x00){
                    button_pressed = 0;
                }
                state = Second;
            }
            break;
        case Wait:
            if(button == 0x01){
                state = Wait;
            }
            else{
                state = Restart;
            }
            break;
        case Restart:
            if(button == 0x01){
                state = First;
                button_pressed = 1;
            }
            else{
                state = Restart;
            }
            break;
        default:
            state = First;
            break;
    }
    switch(state){
        case Start:
            break;
        case First:
            B = 0x01;
            path = 1;
            break;
        case Second:
            B = 0x02;
            break;
        case Third:
            B = 0x04;
            path = 0;
            break;
        case Wait:
            break;
        case Restart:
            break;
        default:
            B = 0x01;
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    TimerSet(300);
    TimerOn();
    state = Start;
    
    button = 0x00;
    B = 0x00;
    
    while (1)
    {
        button = ~PINA & 0x01;
        Tick();
        while(!TimerFlag);
        TimerFlag = 0;
        PORTB = B;
    }
    return 0;
}
