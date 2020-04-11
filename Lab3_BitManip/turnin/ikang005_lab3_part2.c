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
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    
    unsigned char fl = 0x00;
    unsigned char sensor = 0x00;
    
    while(1){
        if((fl & 0x00) == 0x00){
            sensor = 0x40;
        }
        if((fl & 0x01) == 0x01){
            sensor = 0x60;
        }
        if((fl & 0x02) == 0x02){
            sensor = 0x60;
        }
        if((fl & 0x03) == 0x03){
            sensor = 0x70;
        }
        if((fl & 0x04) == 0x04){
            sensor = 0x70;
        }
        if((fl & 0x05) == 0x05){
            sensor = 0x38;
        }
        if((fl & 0x06) == 0x06){
            sensor = 0x38;
        }
        if((fl & 0x07) == 0x07){
            sensor = 0x3C;
        }
        if((fl & 0x08) == 0x08){
            sensor = 0x3C;
        }
        if((fl & 0x09) == 0x09){
            sensor = 0x3C;
        }
        if((fl & 0x0A) == 0x0A){
            sensor = 0x3E;
        }
        if((fl & 0x0B) == 0x0B){
            sensor = 0x3E;
        }
        if((fl & 0x0C) == 0x0C){
            sensor = 0x3E;
        }
        if((fl & 0x0D) == 0x0D){
            sensor = 0x3F;
        }
        if((fl & 0x0E) == 0x0E){
            sensor = 0x3F;
        }
        if((fl & 0x0F) == 0x0F){
            sensor = 0x3F;
        }
        PORTC = sensor;
        fl = 0x00;
        sensor = 0x00;
    }


    return 0;
}


