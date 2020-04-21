/*	Author: Isaac Kang - ikang005
 *  Partner(s) Name: 
 *	Lab Section:21
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	Fuel Sensor
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, INIT, INC, DEC, WAIT, RESET}state;

void Tick(){
    //State transitions
    switch(state){
        case START:
            state = INIT;
            break;
        case INIT:
            if((~PINA & 0x03) == 0x01){
                state = INC;
		break;
            }
            else if((~PINA & 0x03) == 0x02){
                state = DEC;
		break;
            }
            else if((~PINA & 0x03) == 0x03){
                state = RESET;
		break;
            }
            else{
                state = INIT;
		break;
            }
        case INC:
            state = WAIT;
            break;
        case DEC:
            state = WAIT;
            break;
        case WAIT:
            if(((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02)){
                state = WAIT;
		break;
            }
            else if((~PINA & 0x03) == 0x03){
                state = RESET;
		break;
            }
            else{
                state = INIT;
		break;
            }
        case RESET:
            if(((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02)){
                state = RESET;
		break;
            }
            else{
                state = INIT;
		break;
            }
        default:
            break;
    }
    //State Actions
    switch(state){
        case START:
            PORTC = 0x07;
            break;
        case INIT:
            break;
        case INC:
            if(PORTC >= 0x09){
                PORTC = 0x09;
		break;
            }
            else{
                PORTC = PORTC + 0x01;
		break;
            }
        case DEC:
            if(PORTC <= 0x00){
                PORTC = 0x00;
		break;
            }
            else{
                PORTC = PORTC - 0x01;
		break;
            }
        case WAIT:
            break;
        case RESET:
            PORTC = 0x00;
            break;
        default:
            break;
    }
}

void main(){
    DDRA = 0x00; PORTA = 0xFF; //Initialize outputs
    DDRC = 0xFF; PORTC = 0x07;
    state = START;//Indicates initial call

    while(1){
        Tick();
    }
    return;
}
