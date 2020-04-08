/*	Author: ikang005
 *      Partner(s) Name: 
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
  	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char cntavail = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char tmpD = 0x00;
	
    	while (1) {
		tmpA = PINA & 0x01;
		tmpB = PINA & 0x02;
		tmpC = PINA & 0x04;
		tmpD = PINA & 0x08;
		
		tmpB = tmpB >> 1;
		tmpC = tmpC >> 2;
		tmpD = tmpD >> 3;
		
		cntavail = tmpA + tmpB + tmpC + tmpD;
		cntavail = 0x04 - cntavail;
		PORTC = cntavail;
   	}
    return 0;
}
