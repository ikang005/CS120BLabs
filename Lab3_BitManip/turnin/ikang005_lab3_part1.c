/*	Author: ikang005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char numA = 0x00;
	unsigned char numB = 0x00;
	unsigned char totA = 0x00;
	unsigned char totB = 0x00;
	unsigned char tmp = 0x00;
	unsigned char i;	
    while(1)
    {
		numA = PINA;
		numB = PINB;
		totA = 0x00;
		totB = 0x00;
		for(i = 0x00; i < 0x08; i = i + 0x01)
		{
			tmp = (numA >> i) & 0x01;
			if(tmp == 0x01)
			{
				totA = totA + 0x01;
			}
		}
		i = 0x00;
		for(i = 0x00; i < 0x08; i = i + 0x01)
		{
			tmp = (numB >> i) & 0x01;
			if(tmp == 0x01)
			{
				totB = totB + 0x01;
			}
		}
		PORTC = totA + totB;	
    }


    return 0;
}
