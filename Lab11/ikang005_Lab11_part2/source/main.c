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

#include <io.c>
#include <avr/io.h>
#include <bit.h>
#include <timer.h>
#include <stdio.h>

#define LCD_SIZE 16
#define STRING_SIZE 38
#define SEPARATION 3
volatile unsigned char inputs[LCD_SIZE];
volatile unsigned char inputstring[STRING_SIZE] = "CS120B is Legend, wait for it... dary!";

typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
/* Keypad arrangement
        PC4 PC5 PC6 PC7
   col  1   2   3   4
row
PC0 1   1 | 2 | 3 | A
PC1 2   4 | 5 | 6 | B
PC2 3   7 | 8 | 9 | C
PC3 4   * | 0 | # | D
*/

unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
		b = c;
	}
	return 0;
}

enum Output_States {Init, Assign};
	
int Output_tick(int state){
	switch(state){ //Transitions
		case Init:
			state = Assign;
			break;
		case Assign:
			state = Assign;
			break;
		default: state = Init;
	}
	switch(state){ //Actions
		case Init: break;
		case Assign:
			for(unsigned char i = 1; i <= LCD_SIZE; i++){
				if(inputs[i-1] != '\0'){
					LCD_Cursor(i); LCD_WriteData(inputs[i - 1]);
				}else{
					LCD_Cursor(i); LCD_WriteData(' ');
				}
			}
		break;
	}
	return state;
}

enum TextScroll_States{TextScroll_init, TextScroll_start, TextScroll_scroll};
	
int TextScroll_tick(int state){
	static unsigned char index;
	switch(state){ //Transitions
		case TextScroll_init:
			state = TextScroll_start;
		break;
		case TextScroll_start:
			state = TextScroll_scroll;
		break;
		
		case TextScroll_scroll:
			if(index > STRING_SIZE + SEPARATION){
				index = 0;
				state = TextScroll_start;
			}else{
				state = TextScroll_scroll;
			}
		break;
	}
	switch(state){
		case TextScroll_init:
		break;
		
		case TextScroll_start:
		inputs[LCD_SIZE - 1] = inputstring[0];
		index++;
		break;
		
		case TextScroll_scroll:
		inputs[0] = inputs[1];
		inputs[1] = inputs[2];
		inputs[2] = inputs[3];
		inputs[3] = inputs[4];
		inputs[4] = inputs[5];
		inputs[5] = inputs[6];
		inputs[6] = inputs[7];
		inputs[7] = inputs[8];
		inputs[8] = inputs[9];
		inputs[9] = inputs[10];
		inputs[10] = inputs[11];
		inputs[11] = inputs[12];
		inputs[12] = inputs[13];
		inputs[13] = inputs[14];
		inputs[14] = inputs[15];
		if(index >= STRING_SIZE){
		inputs[15] = '\0';
		}else{
		inputs[15] = inputstring[index];
		}
		index++;
		break;
		
		default: break;
	}
	return state;
}
	
int main(void)
{
	unsigned long int scroll_calc = 200;
	unsigned long int output_calc = 200;
	unsigned long int tmpGCD = 0;
	tmpGCD = findGCD(scroll_calc, output_calc);
	unsigned long int GCD = tmpGCD;
	unsigned long int scroll_period = scroll_calc/GCD;
	unsigned long int output_period = output_calc/GCD;
	
	static task task1, task2;
	task *tasks[] = { &task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	unsigned char i;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00; // PORTD set to output, outputs init 0s
//	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1
	task1.state = TextScroll_init;
	task1.period = scroll_period;
	task1.elapsedTime = scroll_period;
	task1.TickFct = &TextScroll_tick;
	task2.state = Init;
	task2.period = output_period;
	task2.elapsedTime = output_period;
	task2.TickFct = &Output_tick;
	LCD_init();
	TimerSet(GCD);
	TimerOn();
//			LCD_DisplayString(1, "Hello World");
	while(1) {
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
	return 1;
}

