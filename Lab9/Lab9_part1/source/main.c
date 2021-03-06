/*    Author: Isaac Kang
 *    Partner(s) Name:
 *    Lab Section: 21
 *    Assignment: Lab #9  Exercise #1
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

enum States{Start, Init, sC, sD, sE}state;
unsigned char tmp;

void Tick(){
    switch(state){
        case Start:
            state = Init;
            break;
        case Init:
            if(tmp == 0x01){
                state = sC;
            }
            else if(tmp == 0x02){
                state = sD;
            }
            else if(tmp == 0x04){
                state = sE;
            }
            else{
                state = Init;
            }
            break;
        case sC:
            if(tmp == 0x01){
                state = sC;
            }
            else{
                state = Init;
            }
            break;
        case sD:
            if(tmp == 0x02){
                state = sD;
            }
            else{
                state = Init;
            }
            break;
        case sE:
            if(tmp == 0x04){
                state = sE;
            }
            else{
                state = Init;
            }
            break;
        default:
            state = Init;
            break;
    }
    
    switch(state){
        case Start:
            set_PWM(0);
            break;
        case Init:
            set_PWM(0);
            break;
        case sC:
            set_PWM(261.63);
            break;
        case sD:
            set_PWM(293.66);
            break;
        case sE:
            set_PWM(329.63);
            break;
        default:
            break;
    }
}

int main(void) {
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;

    tmp = 0x00;
    state = Start;
    PWM_on();
    
    while (1) {
        tmp = ~PINA & 0x07;
        Tick();
    }
    return 1;
}
