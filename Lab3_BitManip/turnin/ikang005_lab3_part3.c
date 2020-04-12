/*    Author: ikang005
 *  Partner(s) Name:
 *    Lab Section:
 *    Assignment: Lab #  Exercise #
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    
    unsigned char fl = 0x00;
    unsigned char belt = 0x00;
    unsigned char seated = 0x00;
    unsigned char ign = 0x00;
    unsigned char sens = 0x00;
    
    while(1){
        fl = PINA;
        belt = PINA & 0x40;
        seated = PINA & 0x20;
        ign = PINA & 0x10;
        
        if((fl & 0x00) == 0x00)
        {
            sens = 0x40;
        }
        if((fl & 0x01) == 0x01)
        {
            sens = 0x60;
        }
        if((fl & 0x02) == 0x02)
        {
            sens = 0x60;
        }
        if((fl & 0x03) == 0x03)
        {
            sens = 0x70;
        }
        if((fl & 0x04) == 0x04)
        {
            sens = 0x70;
        }
        if((fl & 0x05) == 0x05)
        {
            sens = 0x38;
        }
        if((fl & 0x06) == 0x06)
        {
            sens = 0x38;
        }
        if((fl & 0x07) == 0x07)
        {
            sens = 0x3C;
        }
        if((fl & 0x08) == 0x08)
        {
            sens = 0x3C;
        }
        if((fl & 0x09) == 0x09)
        {
            sens = 0x3C;
        }
        if((fl & 0x0A) == 0x0A)
        {
            sens = 0x3E;
        }
        if((fl & 0x0B) == 0x0B)
        {
            sens = 0x3E;
        }
        if((fl & 0x0C) == 0x0C)
        {
            sens = 0x3E;
        }
        if((fl & 0x0D) == 0x0D)
        {
            sens = 0x3F;
        }
        if((fl & 0x0E) == 0x0E)
        {
            sens = 0x3F;
        }
        if((fl & 0x0F) == 0x0F)
        {
            sens = 0x3F;
        }
        if(ign == 0x10)
        {
            if(seated == 0x20)
            {
                if(belt == 0x40)
                {
                    PORTC = sens;
                }
                else
                {
                    PORTC = (sens | 0xA0);
                }
            }
            else{
                PORTC = sens;
            }
        }
        else
        {
            PORTC = sens;
        }
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
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
        if(ign == 0x10)
        {
            if(seated == 0x20)
            {
                if(belt == 0x40)
                {
                    PORTC = fl;
                }
                else
                {
                    PORTC = (fl | 0xA0);
                }
            }
            else{
                PORTC = fl;
            }
        }
        else
        {
            PORTC = fl;
        }
    }
    */
    return 0;
}


