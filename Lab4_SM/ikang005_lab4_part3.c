/*     Author: ikang005
*      Partner(s) Name:
*      Lab Section: 21
*      Assignment: Lab #4  Exercise #3
*      Exercise Description: [optional - include for your own benefit]
*      I acknowledge all content contained herein, excluding template or example
*      code, is my own original work.
*/
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Init, P, Y, Wait}state;

void Tick(){
    switch(state){
        case Start:
            state = Init;
            break;
        case Init:
            if((PINA & 0x04) && !(PINA & 0x83)){
                state = P;
            }
            else{
                state = Init;
            }
            break;
        case P:
            if((PINA & 0x04) && !(PINA & 0x83)){
                state = P;
            }
            else if(PINA == 0x00){
                state = Wait;
            }
            else{
                state = Init;
            }
            break;
        case Wait:
            if((PINA & 0x02) && !(PINA & 0x85)){
                state = Y;
            }
            else if(PINA == 0x00){
                state = Wait;
            }
            else{
                state = Init;
            }
            break;
        case Y:
            if((PINA & 0x80) && !(PINA & 0x07)){
                state = Init;
            }
            else{
                state = Y;
            }
            break;
        default:
            state = Start;
            break;
    }
    switch(state){
        case Start:
            PORTC = 0x00;
            break;
        case Init:
            PORTB = 0x00;
            PORTC = 0x01;
            break;
        case P:
            PORTC = 0x02;
            break;
        case Wait:
            PORTC = 0x03;
            break;
        case Y:
            PORTB = 0x01;
            PORTC = 0x04;
            break;
        default:
            break;
    }
}
 
int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    
    //initialize
    state = Start;
        
    while (1)
    {
        Tick();
    }
    return 0;
}

