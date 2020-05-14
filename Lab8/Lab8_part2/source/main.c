/*    Author: Isaac Kang
 *    Partner(s) Name:
 *    Lab Section: 21
 *    Assignment: Lab #8  Exercise #2
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    ADC_init();

    unsigned short convADC;
    unsigned char ledB;
    unsigned char ledD;
    
    while (1) {
        convADC = ADC;
        ledB = (char)convADC;
        ledD = (char) ((convADC >> 8) & 0x0F);
        
        PORTB = ledB;
        PORTD = ledD;
    }
    return 1;
}
