/*     Author: ikang005
*      Partner(s) Name:
*      Lab Section: 21
*      Assignment: Lab #4  Exercise #1
*      Exercise Description: [optional - include for your own benefit]
*      I acknowledge all content contained herein, excluding template or example
*      code, is my own original work.
*/
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, INIT, OFF, ON, WAIT1, WAIT2}state;

void Tick(){
    //State transitions
    switch(state){
        case START:
            PORTB = 0x01;
            state = INIT;
            break;
        case INIT:
            if(PINA == 0x01){
                state = OFF;
            }
            else{
                state = INIT;
            }
            break;
        case OFF:
            if(PINA == 0x00){
                state = WAIT1;
            }
            else{
                state = OFF;
            }
            break;
        case WAIT1:
            if(PINA == 0x01){
                state = ON;
            }
            else{
                state = WAIT1;
            }
            break;
        case ON:
            if(PINA == 0x00){
                state = WAIT2;
            }
            else{
                state = ON;
            }
            break;
        case WAIT2:
            if(PINA == 0x01){
                state = OFF;
            }
            else{
                state = WAIT2;
            }
            break;
        default:
            break;
    }
    //State Actions
    switch(state){
        case START:
            break;
        case INIT:
            PORTB = 0x01;
            break;
        case OFF:
            PORTB = 0x02;
            break;
        case WAIT1:
            break;
        case ON:
            PORTB = 0x01;
            break;
        case WAIT2:
            break;
        default:
            break;
        
    }
}

void main(){
    DDRA = 0x00; PORTA = 0xFF; //Initialize outputs
    DDRB = 0xFF; PORTB = 0x00;
    state = START;//Indicates initial call
    
    while(1){
        Tick();
    }
    return 0;
}
