/*    Author: Isaac Kang
 *    Partner(s) Name:
 *    Lab Section: 21
 *    Assignment: Lab #8  Exercise #4
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

 int main(void)
 {
     DDRB = 0xFF;
     DDRD = 0xFF;
     
     ADC_init();
     unsigned short convADC = 0x0000;
     unsigned short max = (0x0C7);
     unsigned short tmp = (max)/8;
     
     while (1)
     {
         convADC = ADC;
         if(convADC > (tmp*7)){
             PORTB = 0xFF;
         }
         else if(convADC > (tmp*6)){
             PORTB = 0x7F;
         }
         else if(convADC > (tmp*5)){
             PORTB = 0x3F;
         }
         else if(convADC > (tmp*4)){
             PORTB = 0x1F;
         }
         else if(convADC > (tmp*3)){
             PORTB = 0x0F;
         }
         else if(convADC > (tmp*2)){
             PORTB = 0x07;
         }
         else if(convADC > (tmp*1)){
             PORTB = 0x03;
         }
         else if(convADC > (tmp*0)){
             PORTB = 0x01;
         }
         else{
             PORTB = 0x00;
         }
     }
 }
