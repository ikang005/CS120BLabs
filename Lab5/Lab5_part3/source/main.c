/*    Author: Isaac Kang - ikang005
 *    Partner(s) Name:
 *    Lab Section:21
 *    Assignment: Lab #5  Exercise #3
 *    Exercise Description: [optional - include for your own benefit]
 *    INC & DEC
 *    I acknowledge all content contained herein, excluding tmplate or example
 *    code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, INIT, s1, s2, s3, s4, w1, w2, w3, w4}state;
unsigned char tmp;

void Tick(){
    switch(state){
        case START:
            state = INIT;
            break;
        case INIT:
            if(tmp == 0x01){
                state = s1;
            }
            else{
                state = INIT;
            }
            break;
        case s1:
            if(tmp == 0x01){
                state = s1;
            }
            else{
                state = w1;
            }
            break;
        case w1:
            if(tmp == 0x00){
                state = w1;
            }
            else{
                state = s2;
            }
            break;
        case s2:
            if(tmp == 0x01){
                state = s2;
            }
            else{
                state = w2;
            }
            break;
        case w2:
            if(tmp == 0x00){
                state = w2;
            }
            else{
                state = s3;
            }
            break;
        case s3:
            if(tmp == 0x01){
                state = s3;
            }
            else{
                state = w3;
            }
            break;
        case w3:
            if(tmp == 0x00){
                state = w3;
            }
            else{
                state = s4;
            }
            break;
        case s4:
            if(tmp == 0x01){
                state = s4;
            }
            else{
                state = w4;
            }
            break;
        case w4:
            if(tmp == 0x00){
                state = w4;
            }
            else{
                state = INIT;
            }
            break;
        default:
            break;
    }
    switch(state){
        case START:
            break;
        case INIT:
            PORTB = 0x00;
            break;
        case s1:
            PORTB = 0x21;
            break;
        case w1:
            break;
        case s2:
            PORTB = 0x12;
            break;
        case w2:
            break;
        case s3:
            PORTB = 0x0C;
            break;
        case w3:
            break;
        case s4:
            PORTB = 0x3F;
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    PORTB = 0x00;
    state = START;
    
    while (1)
    {
        tmp = (~PINA & 0x01);
        Tick();
    }
}
