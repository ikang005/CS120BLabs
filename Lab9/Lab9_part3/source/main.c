/*    Author: Isaac Kang
 *    Partner(s) Name:
 *    Lab Section: 21
 *    Assignment: Lab #9  Exercise #3
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
    if(_avr_timer_cntcurr == 0){
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

void set_PWM(double frequency){
    static double current_frequency;
    
    if(frequency != current_frequency){
        if(!frequency){
            TCCR3B &= 0x08;
        }
        else{
            TCCR3B |= 0x03;
        }
        if(frequency < 0.954){
            OCR3A = 0xFFFF;
        }
        else if(frequency > 31250){
            OCR3A = 0x0000;
        }
        else{
            OCR3A = (short) (8000000 / (128 * frequency)) - 1;
        }
        TCNT3 = 0;
        current_frequency = frequency;
    }
}

void PWM_on(){
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}

void PWM_off(){
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

double seq[25] = {329.63, 293.66, 261.63, 293.66, 329.63, 329.63, 329.63,
    293.66, 293.66, 293.66, 329.63, 329.63, 329.63, 329.63, 293.66, 261.63,
    293.66, 329.63,329.63, 329.63,329.63, 293.66, 293.66, 329.63, 293.66};
unsigned char hold[25] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
unsigned char down[25] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
unsigned char button;
unsigned char i;
unsigned char t;

enum States{Start, Init, Play, Stop, Wait}state;

void Tick(){
    switch(state){
        case Start:
            state = Init;
            break;
        case Init:
            if(button == 0x01){
                state = Play;
            }
            else{
                state = Init;
            }
            break;
        case Play:
            if(i < 25){
                if(t < hold[i]){
                    state = Play;
                    t++;
                    set_PWM(seq[i]);
                }
                else{
                    state = Stop;
                    t = 0;
                }
            }
            else{
                if(button == 0x01){
                    state = Wait;
                }
                else{
                    state = Init;
		}
	    }
            break;
        case Stop:
            if(t < down[i]){
                state = Stop;
                t++;
            }
            else{
                state = Play;
                i++;
            }
            break;
        case Wait:
            if(button == 0x01){
                state = Wait;
            }
            else{
                state = Start;
            }
        default:
            state = Init;
            break;
    }
    switch(state){
        case Start:
            set_PWM(0);
            break;
        case Init:
            PWM_off();
            i = 0;
            t = 0;
            break;
        case Play:
            PWM_on();
            set_PWM(seq[i]);
            break;
        case Stop:
            PWM_off();
            break;
        case Wait:
            PWM_off();
            break;
        default:
            PWM_off();
            break;
    }
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    TimerSet(100);
    TimerOn();
    
    state = Start;
    i = 0;
    t = 0;
    
    while(1)
    {
        button = ~PINA & 0x01;
        Tick();
        while (!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}

