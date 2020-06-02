/*    Author: Isaac Kang
 *    Partner(s) Name:
 *    Lab Section: 21
 *    Assignment: Lab #11  Exercise #3
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

//Demo:

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <io.h>
#include <keypad.h>
#include <timer.h>
#endif

unsigned char i;
unsigned char x = 0;
unsigned char keyout = 0;

unsigned long int findGCD(unsigned long int a, unsigned long int b){
    unsigned long int c;
    while(1) {
        c = a%b;
        if (c==0) {return b;}
        a = b;
        b = c;
    }
    return 0;
}

typedef struct task{
    signed char state;
    unsigned long int period;
    unsigned long int elapsedTime;
    int (*TickFct) (int);
} task;

enum keypad_states {keypad};
int Keypad(int state){
    x = GetKeypadKey();
    switch(state){
        case keypad:
            state = keypad;
            break;
        default:
            state = keypad;
            break;
    }
    switch(state){
        case keypad:
            switch(x){
                       case '\0': keyout = '\0'; break;
                        case '1': keyout = '1'; break;
                        case '2': keyout = '2'; break;
                        case '3': keyout = '3'; break;
                        case '4': keyout = '4'; break;
                        case '5': keyout = '5'; break;
                        case '6': keyout = '6'; break;
                        case '7': keyout = '7'; break;
                        case '8': keyout = '8'; break;
                        case '9': keyout = '9'; break;
                        case 'A': keyout = 'A'; break;
                        case 'B': keyout = 'B'; break;
                        case 'C': keyout = 'C'; break;
                        case 'D': keyout = 'D'; break;
                        case '*': keyout = '*'; break;
                        case '0': keyout = '0'; break;
                        case '#': keyout = '#'; break;
                        default: keyout = 0x1B; break;
            }
    }
    return state;
}

enum lcd_states {display, press};
int LCD(int state) {
    static char temp;
    switch(state){
        case display:
            if (keyout == '\0'){
                state = display;
            }
            else{
                state = press;
            }
            break;
        case press:
            state = display;
            break;
        default:
            state = display;
            break;
    }
    switch(state) {
        case display:
            LCD_Cursor(1);
            LCD_WriteData(temp);
            break;
        case press:
            temp = keyout;
            break;
    }
    return state;
}

int main(void){
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;

    LCD_init();
    
    static task task1, task2;
    task *tasks[] = { &task1, &task2 };
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    //Task 1
    task1.state = display;
    task1.period = 250;
    task1.elapsedTime = task1.period;
    task1.TickFct = &LCD;

    //Task 2
    task2.state = keypad;
    task2.period = 10;
    task2.elapsedTime = task2.period;
    task2.TickFct = &Keypad;

    unsigned long GCD = tasks[0]->period;
    for(i = 1; i < numTasks; i++) {
        GCD = findGCD(GCD,tasks[i]->period);
    }

    TimerSet(GCD);
    TimerOn();

    while (1) {
        for(i = 0; i < numTasks; i++){
            if(tasks[i]->elapsedTime == tasks[i]->period){
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += GCD;
        }
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 0;
}
