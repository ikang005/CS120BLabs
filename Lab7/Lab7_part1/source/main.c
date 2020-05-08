/*	Author: ikang005
 *      Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	INC & DEC with LED
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Init, Inc, Dec, Wait, Reset} state;
unsigned char button;
unsigned char tmp;
unsigned char i;
unsigned char st;

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


void Tick(){
    switch(state){
        case Start:
            state = Init;
            break;
        case Init:
            if(button == 0x01){
                state = Inc;
                if(tmp < 0x09){
                    tmp += 0x01;
                }
            }
            else if(button == 0x02){
                state = Dec;
                if(tmp > 0){
                    tmp -= 0x01;
                }
            }
            else if(button == 0x03){
                state = Reset;
            }
            else{
                state = Init;
            }
            break;
        case Inc:
            if(button == 0x00){
                state = Wait;
            }
            else if(button == 0x03){
                state = Reset;
            }
            else{
                state = Inc;
            }
            break;
        case Dec:
            if(button == 0x00){
                state = Wait;
            }
            else if(button == 0x03){
                state = Reset;
            }
            else{
                state = Dec;
            }
            break;
        case Wait:
            if(button == 0x01){
                state = Inc;
                if(tmp < 0x09){
                    tmp += 0x01;
                }
            }
            else if(button == 0x02){
                state = Dec;
                if(tmp > 0x00){
                    tmp -= 0x01;
                }
            }
            else if(button == 0x03){
                state = Reset;
            }
            else{
                state = Wait;
            }
            break;
        case Reset:
            if(button == 0x03){
                state = Reset;
            }
            else{
                state = Wait;
            }
            break;
        default:
            state = Start;
            break;
    }
    switch(state){
        case Start:
            tmp = 0x00;
            break;
        case Init:
            tmp = 0x00;
            i = 0;
	    st = 1;
            break;
        case Inc:
            if(tmp < 0x09 && i == 10){
                tmp += 0x01;
                i = 0;
            }
            i++;
	    st = 2;
            break;
        case Dec:
            if(tmp > 0x00 && i == 10){
                tmp -= 0x01;
                i = 0;
            }
            i++;
	    st = 3;
            break;
        case Wait:
            i = 0;
	    st = 4;
            break;
        case Reset:
            tmp = 0x00;
            i = 0;
	    st = 5;
            break;
        default:
            tmp = 0x00;
            i = 0;
            break;
    }
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    LCD_init();
    TimerSet(100);
    TimerOn();
    tmp = 0x07;
    state = Init;
    
    while(1){
        button = ~PINA & 0x03;
        Tick();
        while(!TimerFlag);
        TimerFlag = 0;
        PORTB = st;
	LCD_Cursor(1);
	LCD_WriteData(tmp + '0');
    }
    return 0;
}



