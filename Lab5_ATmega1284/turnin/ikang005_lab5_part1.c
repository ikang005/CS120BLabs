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

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char fl = 0x00;

    while(1){
        fl = ~PINA;
        switch(fl){
            case 0x00:
                PORTC = 0x40;
                break;
            case 0x01:
                PORTC = 0x60;
                break;
            case 0x02:
                PORTC = 0x60;
                break;
            case 0x03:
                PORTC = 0x70;
                break;
            case 0x04:
                PORTC = 0x70;
                break;
            case 0x05:
                PORTC = 0x38;
                break;
            case 0x06:
                PORTC = 0x38;
                break;
            case 0x07:
                PORTC = 0x3C;
                break;
            case 0x08:
                PORTC = 0x3C;
                break;
            case 0x09:
                PORTC = 0x3C;
                break;
            case 0x0A:
                PORTC = 0x3E;
                break;
            case 0x0B:
                PORTC = 0x3E;
                break;
            case 0x0C:
                PORTC = 0x3E;
                break;
            case 0x0D:
                PORTC = 0x3F;
                break;
            case 0x0E:
                PORTC = 0x3F;
                break;
            case 0x0F:
                PORTC = 0x3F;
                break;
            default:
                break;
        }
    }
    return 0;
}
