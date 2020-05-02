/*    Author: Isaac Kang - ikang005
 *    Partner(s) Name:
 *    Lab Section:21
 *    Assignment: Lab #5  Exercise #2
 *    Exercise Description: [optional - include for your own benefit]
 *    INC & DEC
 *    I acknowledge all content contained herein, excluding tmplate or example
 *    code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, INIT, INC, DEC, RESET, WAIT}state;
unsigned char tmp;
unsigned char tmpVal;

void Tick()
{
    switch(state)
    {
       case START:
        state = INIT;
        break;
        case INIT:
            if(tmp == 0x01){
              state = INC;
            }
            else if(tmp == 0x02)
            {
              state = DEC;
            }
            else if(tmp == 0x03)
            {
              state = RESET;
            }
            else
            {
              state = INIT;
            }
            break;
        case WAIT:
            if(tmp == 0x00){
              state = INIT;
            }
            else if(tmp == 0x03)
            {
              state = RESET;
            }
            break;
        case INC:
            state = WAIT;
            break;
        case DEC:
            state = WAIT;
            break;
        case RESET:
            state = WAIT;
            break;
        default:
            break;
    }

    switch(state)
    {
        case START:
            break;
        case INIT:
            PORTC = tmpVal;
            break;
        case WAIT:
            PORTC = tmpVal;
            break;
        case INC:
            if(PORTC == 0x09){
                PORTC = tmpVal;
            }
            else{
                PORTC = tmpVal + 0x01;
                tmpVal = tmpVal + 0x01;
            }
            break;
        case DEC:
            if(PORTC == 0x00){
                PORTC = tmpVal;
            }
            else{
                PORTC = tmpVal - 0x01;
                tmpVal = tmpVal - 0x01;
            }
            break;
        case RESET:
            PORTC = 0x00;
            tmpVal = 0x00;
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    tmpVal = 0x00;
    state = START;
    
    while (1)
    {
        tmp = (~PINA & 0x03);
        Tick();
    }
}
