/*     Author: ikang005
*      Partner(s) Name:
*      Lab Section: 21
*      Assignment: Lab #4  Exercise #5
*      Exercise Description: [optional - include for your own benefit]
*      I acknowledge all content contained herein, excluding template or example
*      code, is my own original work.
*/
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Init, P, Wait, X1, w2, Y1, w3, X2, Lock, wL, Lock2, wL2, Lock3, wL3}state;

void Tick(){
    switch(state){
        case Start:
            state = Init;
            break;
        case Init:
            if((PINA & 0x04) && !(PINA & 0x83)){
                state = P;
            }
            else{
                state = Init;
            }
            break;
        case P:
            if((PINA & 0x04) && !(PINA & 0x83)){
                state = P;
            }
            else if(PINA == 0x00){
                state = Wait;
            }
            else{
                state = Init;
            }
            break;
        case Wait:
            if((PINA & 0x01) && !(PINA & 0x86)){
                state = X1;
            }
            else if(PINA == 0x00){
                state = Wait;
            }
            else{
                state = Init;
            }
            break;
        case X1:
            if((PINA & 0x01) && !(PINA & 0x86)){
                state = X1;
            }
            else if(PINA == 0x00){
                state = w2;
            }
            else{
                state = Init;
            }
            break;
        case w2:
            if((PINA & 0x02) && !(PINA & 0x85)){
                state = Y1;
            }
            else if(PINA == 0x00){
                state = w2;
            }
            else{
                state = Init;
            }
            break;
        case Y1:
            if((PINA & 0x02) && !(PINA & 0x85)){
                state = Y1;
            }
            else if(PINA == 0x00){
                state = w3;
            }
            else{
                state = Init;
            }
            break;
        case w3:
            if((PINA & 0x01) && !(PINA & 0x86)){
                state = X2;
            }
            else if(PINA == 0x00){
                state = w3;
            }
            else{
                state = Init;
            }
            break;
        case X2:
            if((PINA & 0x04) && !(PINA & 0x03)){
                state = Lock;
            }
            else if((PINA & 0x80) && !(PINA & 0x07)){
                state = Init;
            }
            else{
                state = X2;
            }
            break;
        case Lock:
            if((PINA & 0x04) && !(PINA & 0x83)){
                state = Lock;
            }
            else if(PINA == 0x00){
                state = wL;
            }
            else{
                state = X2;
            }
            break;
        case wL:
            if((PINA & 0x01) && !(PINA & 0x86)){
                state = Lock2;
            }
            else if(PINA == 0x00){
                state = wL;
            }
            else{
                state = X2;
            }
            break;
        case Lock2:
            if((PINA & 0x01) && !(PINA & 0x86)){
                state = Lock2;
            }
            else if(PINA == 0x00){
                state = wL2;
            }
            else{
                state = X2;
            }
            break;
        case wL2:
            if((PINA & 0x02) && !(PINA & 0x85)){
                state = Lock3;
            }
            else if(PINA == 0x00){
                state = wL2;
            }
            else{
                state = X2;
            }
            break;
        case Lock3:
            if((PINA & 0x02) && !(PINA & 0x85)){
                state = Lock3;
            }
            else if(PINA == 0x00){
                state = wL3;
            }
            else{
                state = X2;
            }
            break;
        case wL3:
            if((PINA & 0x01) && !(PINA & 0x86)){
                state = Init;
            }
            else if(PINA == 0x00){
                state = wL3;
            }
            else{
                state = X2;
            }
            break;
        default:
            state = Start;
            break;
    }
    switch(state){
        case Start:
            PORTC = 0x00;
            break;
        case Init:
            PORTB = 0x00;
            PORTC = 0x01;
            break;
        case P:
            PORTC = 0x02;
            break;
        case Wait:
            PORTC = 0x03;
            break;
        case X1:
            PORTC = 0x04;
            break;
        case w2:
            PORTC = 0x05;
            break;
        case Y1:
            PORTC = 0x06;
            break;
        case w3:
            PORTC = 0x07;
            break;
        case X2:
            PORTB = 0x01;
            PORTC = 0x08;
            break;
        case Lock:
            PORTC = 0x09;
            break;
        case wL:
            PORTC = 0x0A;
            break;
        case Lock2:
            PORTC = 0x0B;
            break;
        case wL2:
            PORTC = 0x0C;
            break;
        case Lock3:
            PORTC = 0x0D;
            break;
        case wL3:
            PORTC = 0x0E;
            break;
        default:
            break;
            
    }
}
 
int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    
    //initialize
    state = Start;
        
    while (1)
    {
        Tick();
    }
    return 0;
}


