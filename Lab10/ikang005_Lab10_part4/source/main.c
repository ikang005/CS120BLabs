/*    Author: Isaac Kang
 *    Partner(s) Name:
 *    Lab Section: 21
 *    Assignment: Lab #10  Exercise #3
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}

void TimerOff(){
    TCCR1B = 0x00;
}

void TimerISR(){
    TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

enum ThreeStates{Start, s1, s2, s3}ThreeState;
enum BlinkingStates{ON, OFF}BlinkingState;
enum CombineStates{OUT}CombineState;
enum SpeakerStates{Init, tON, tOFF}SpeakerState;
enum FrequencyStates{b1, b2}FrequencyState;

unsigned char threeLEDs;
unsigned char blinkingLED;
unsigned char button;
unsigned char temp;
unsigned char inc;
unsigned char dec;
unsigned char freq;
unsigned char freqc;
unsigned char c;

void ThreeLEDsSM(){
    switch(ThreeState){
        case Start:
            ThreeState = s1;
            break;
        case s1:
            ThreeState = s2;
            break;
        case s2:
            ThreeState = s3;
            break;
        case s3:
            ThreeState = s1;
            break;
        default:
            ThreeState = s1;
            break;
    }
    switch(ThreeState){
        case Start:
            break;
        case s1:
            threeLEDs = 0x01;
            break;
        case s2:
            threeLEDs = 0x02;
            break;
        case s3:
            threeLEDs = 0x04;
            break;
        default:
            break;
    }
}

void BlinkingLEDSM(){
    switch(BlinkingState){
        case ON:
            BlinkingState = OFF;
            break;
        case OFF:
            BlinkingState = ON;
            break;
        default:
            BlinkingState = ON;
            break;
    }
    switch(BlinkingState){
        case ON:
            blinkingLED = 0x08;
            break;
        case OFF:
            blinkingLED = 0x00;
            break;
        default:
            break;
    }
}

void SpeakerSM(){
    switch(SpeakerState){
        case Init:
            if(button == 0x04){
                SpeakerState = tON;
            }
            else{
                SpeakerState = Init;
            }
            break;
        case tON:
            if(button == 0x04 && freqc == freq){
                SpeakerState = tOFF;
                freqc = 0;
            }
            else if(button == 0x04 && freqc != freq){
                SpeakerState = tON;
                freqc++;
            }
            else{
                SpeakerState = Init;
            }
            break;
        case tOFF:
            if(button == 0x04 && freqc == freq){
                SpeakerState = tON;
                freqc = 0;
            }
            else if(button == 0x04 && freqc != freq){
                SpeakerState = tOFF;
                freqc++;
            }
            else{
                SpeakerState = Init;
            }
            break;
        default:
            SpeakerState = Init;
            break;
    }
    switch(SpeakerState){
        case Init:
            temp = 0x00;
            break;
        case tON:
            temp = 0x10;
            break;
        case tOFF:
            temp = 0x00;
            break;
        default:
            break;
    }
}

void CombineLEDsSM(){
    switch(CombineState){
        case OUT:
            CombineState = OUT;
            break;
        default:
            CombineState = OUT;
            break;
    }
    switch(CombineState){
        case OUT:
            PORTB = threeLEDs | blinkingLED | temp;
            break;
        default:
            break;
    }
}

void FrequencySM(){
    switch(FrequencyState){
        case b1:
            if(dec == 0x02 && freq < 0x05){
                if(c == 1){
                    freq++;
                    c = 0;
                    FrequencyState = b2;
                }
            }
            else if(inc == 0x01 && freq > 0x00){
                if(c == 1){
                    freq--;
                    c = 0;
                    FrequencyState = b2;
                }
            }
            break;
        case b2:
            if(inc == 0x01 || dec == 0x02){
                FrequencyState = b2;
            }
            else{
                FrequencyState = b1;
                c = 1;
            }
            break;
        default:
            FrequencyState = b1;
            c = 1;
            break;
    }
    switch(FrequencyState){
        case b1:
            break;
        case b2:
            break;
        default:
            break;
    }
}

int main(void)
{
    unsigned long Three_et = 0;
    unsigned long Blink_et = 0;
    unsigned long Speak_et = 0;
    const unsigned long synchPeriod = 1;
    
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    TimerSet(1);
    TimerOn();
    
    button = 0x00;
    temp = 0x00;
    threeLEDs = 0x00;
    blinkingLED = 0x00;
    freq = 0x00;
    freqc = 0x00;
    c = 1;
    
    
    ThreeState = Start;
    BlinkingState = ON;
    CombineState = OUT;
    SpeakerState = Start;
    FrequencyState = b1;
    
    while(1){
        button = ~PINA & 0x04;
        inc = ~PINA & 0x01;
        dec = ~PINA & 0x02;
        
        if(Three_et >= 300){
            ThreeLEDsSM();
            Three_et = 0;
        }
        if(Blink_et >= 1000){
            BlinkingLEDSM();
            Blink_et = 0;
        }
        if(Speak_et >= 2){
            SpeakerSM();
            Speak_et = 0;
        }
        FrequencySM();
        CombineLEDsSM();
        
        while(!TimerFlag);
        TimerFlag = 0;
        
        Three_et += synchPeriod;
        Blink_et += synchPeriod;
        Speak_et += synchPeriod;
    }
    return 0;
}


