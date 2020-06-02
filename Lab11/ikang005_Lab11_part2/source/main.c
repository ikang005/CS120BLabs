/*    Author: Isaac Kang
 *    Partner(s) Name:
 *    Lab Section: 21
 *    Assignment: Lab #11  Exercise #2
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

//Demo:
/*
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <io.h>
#include <keypad.h>
#include <timer.h>
#endif

unsigned char i;
unsigned char cnt = 0;
unsigned char pos = 0;
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
int keypadSMTick(int state){
    x = GetKeypadKey();
    switch(state) {
        case keypad:
            state = keypad;
            break;
        default:
            state = keypad;
            break;
    }
    switch(state) {
        case keypad:
            switch(x) {
                       case '\0': keyout = 0x1F; break;
                        case '1': keyout = 0x01; break;
                        case '2': keyout = 0x02; break;
                        case '3': keyout = 0x03; break;
                        case '4': keyout = 0x04; break;
                        case '5': keyout = 0x05; break;
                        case '6': keyout = 0x06; break;
                        case '7': keyout = 0x07; break;
                        case '8': keyout = 0x08; break;
                        case '9': keyout = 0x09; break;
                        case 'A': keyout = 0x0A; break;
                        case 'B': keyout = 0x0B; break;
                        case 'C': keyout = 0x0C; break;
                        case 'D': keyout = 0x0D; break;
                        case '*': keyout = 0x0E; break;
                        case '0': keyout = 0x00; break;
                        case '#': keyout = 0x0F; break;
                        default: keyout = 0x1B; break;
            }
    }
    return state;
}

enum lcd_states {display};
int lcdSMTick(int state){
    unsigned char msg[37] = {'C', 'S', '1', '2', '0', 'B', ' ', 'i', 's', ' ', 'L', 'e', 'g', 'e', 'n', 'd', '.', '.', '.', ' ', 'w', 'a', 'i', 't', ' ', 'f', 'o', 'r', ' ', 'i', 't', ' ', 'D', 'A', 'R', 'Y', '!'};
    switch(state){
        case display:
            state = display;
            break;
        default:
            state = display;
            break;
    }
    switch(state){
        case display:
            if (pos < 24){
                for(cnt = 1; cnt <= 16; cnt++){
                    LCD_Cursor(cnt);
                    LCD_WriteData(msg[pos + cnt]);
                }
                pos++;
            }
            else{
                pos = 0;
            }
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
    
    static task task1;
    task *tasks[] = { &task1 };
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    
    task1.state = display;
    task1.period = 300;
    task1.elapsedTime = task1.period;
    task1.TickFct = &lcdSMTick;

    unsigned long GCD = tasks[0]->period;
    for(i = 1; i < numTasks; i++) {
        GCD = findGCD(GCD,tasks[i]->period);
    }

    TimerSet(300);
    TimerOn();

    while (1) {
        for (i = 0; i < numTasks; i++){
            if (tasks[i]->elapsedTime == tasks[i]->period){
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
*/

/*
 * lab011_2.c
 *
 * Created: 2/21/2019 4:23:27 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <io_alt.c>
#include <timer.h>
#include <scheduler.h>

unsigned char stuff[] = "CS120B is Legend... wait for it DARY!";


enum State {SCROLL};
int Tick(int state){
        static unsigned char scroll = 16;
        static unsigned char disp = 0;
        static unsigned long offset_trigger = 0; 
        static unsigned long offset = 0;
        static unsigned long character_pos = 0 ;
        static unsigned long i = 0; 
        //static unsigned long j = 0;
        
        unsigned long mess_length = sizeof(stuff)/sizeof(stuff[0]) ;
    switch(state){
        case SCROLL:
                
               // scroll = 15;
                LCD_ClearScreen();
                LCD_Cursor(16);
                
               // for(int i = 0; i < (mess_length + 15); ++i){
                   if(i < (mess_length + 15)){
                        ++i;
                    //LCD_ClearScreen();
                    for(int j = 16; j > scroll; --j){
                        if( (character_pos = (j-scroll-1 + offset) ) >= (mess_length - 1) ) disp = 32;
                        else disp = stuff[character_pos];
                        
                        LCD_Cursor(j);
                        LCD_WriteData(disp);
                        
                    }
                    //while(!TimerFlag);
                    //TimerFlag = 0;
                    
                    if(scroll) --scroll;
                    ++offset_trigger;
                    if(offset_trigger >= 16) {
                        ++offset;
                    }                   
                }else {
                    i = 0; 
                    scroll = 15;
                    offset = 0;
                offset_trigger = 0;}
        default: 
            state = SCROLL;
        break;
    }
    return state;
}

int main(void)
{
    DDRA = 0xFF; PORTC = 0x00;
    DDRB = 0xFF; PORTC = 0x00;
    DDRC = 0xF0; PORTC = 0x0F; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
      
    unsigned long period = 1;  
    TimerSet(400);
    TimerOn();
    TimerFlag = 0;
      
    static task task0;
    task0.elapsedTime = period;
    task0.period = period;
    task0.state = -1;
    task0.TickFct = &Tick; 
    
    task *tasks[] = {&task0};
    //unsigned char stuff[] = "Matthew is Legend... wait for it DARY!";
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    // Initializes the LCD display
    LCD_init();
    LCD_ClearScreen();
    int i = 0;
    while (1) 
    {  
        for ( i = 0; i < numTasks; i++ ) {
            // Task is ready to tick
            if ( tasks[i]->elapsedTime == tasks[i]->period ) {
                // Setting next state for task
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                // Reset the elapsed time for next tick.
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 1;
        }
        while(!TimerFlag);
        TimerFlag = 0;
   }

    // Error: Program should not exit!
    return 0;
              
}

