/*	Author: ikang005
 *	Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRD = 0x00; PORTD = 0xFF;
    DDRB = 0xFE; PORTB = 0x01;
    
    unsigned char sensor = 0x0000;
    unsigned char tmp = 0x00;
    unsigned char output = 0x01;
    
    while(1){
        sensor = PIND << 1;
        tmp = PINB & 0x01;
        sensor = sensor | tmp;
        
        if(sensor >= 0x0046){
            output = 0x02;
        }
        else if((sensor < 70) && (sensor > 5)){
            output = 0x04;
        }
        PORTB = output;
    }

    return 0;
}


