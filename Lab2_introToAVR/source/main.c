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
	DDRB = 0X00; PORTB = 0XFF;
  	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0XFF; PORTD = 0X00;
	
	unsigned char wgtA = 0x00;
	unsigned char wgtB = 0x00;
	unsigned char wgtC = 0x00;
	unsigned char wgtDiff = 0x00;
	unsigned char tmpWgt = 0x00;
	unsigned short totWgt = 0x0000;
	
    	while (1) {
		wgtA = PINA;
		wgtB = PINB;
		wgtC = PINC;

		totWgt = wgtA + wgtB + wgtC;
		wgtDiff = abs((wgtA - wgtC));

		if((wgtDiff >= 0x50) && (totWgt >= 0x008C)){
			PORTD = (totWgt << 2) | 0x03;
		}
		else{
			PORTD = (totWgt << 2) | 0x00;
		}

		tmpWgt = 0x00;
		wgtDiff = 0x00;
		totWgt = 0x0000;
   	}
    return 0;
}
