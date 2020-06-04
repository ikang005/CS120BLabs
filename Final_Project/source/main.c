/*    Author: Isaac Kang
 *    Lab Section: 21
 *    CS120B Final Project - LCD Racer
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
//#ifdef _SIMULATE_
#include "simAVRHeader.h"
//#endif
#include "bit.h"
#include "io.c"
#include "scheduler.h"
#include "timer.h"
#include "Game.h"
#include "Enemy.h"
#include "Obstacles.h"

//Declare Global Variables-----------------------------------------
unsigned char introString[32] = "LCD Racer       Choose: P1 or P2";
unsigned char gameString[11] = "Game Over!";
unsigned char scoreString[9] = "Score: ";
unsigned char i = 0;
unsigned char cursPos = 1;
unsigned char cursPos2 = 16;
unsigned char obst1 = 0;
unsigned char obst2 = 0;
unsigned char obst3 = 0;
unsigned char obst4 = 0;
unsigned char bullPos = 0;
unsigned char bullH = 10;
unsigned char bullH2 = 10;
unsigned char laser = 0;
unsigned char laserC = 3;
unsigned long holdDC = 0;
unsigned char noneC = 0;
unsigned char speedC = 4;
unsigned char speed = 0;
unsigned long score = 0;
unsigned char showS = 0;
unsigned char showSPos;
unsigned char random;
unsigned long slow = 0;
unsigned long holdCount = 0;
unsigned short p2Choice = 0;
/*
 unsigned char x = '\0';
 unsigned char stringStart[30] = "Sam's CS120B    Final Project";
 unsigned char stringEnd[11] = "Game Over!";
 unsigned char stringScore[8] = "Score:";
 unsigned char cursorPosition = 1;
 unsigned char cursorPosition2 = 16;
 unsigned char obstacle1Position = 0;
 unsigned char obstacle2Position = 0;
 unsigned char obstacle3Position = 0;
 unsigned char obstacle4Position = 0;
 unsigned char bulletPosition = 0;
 unsigned char bulletHit3 = 10;
 unsigned char bulletHit4 = 10;
 unsigned char laserPosition = 0;
 unsigned long holdDisplayCount = 0;
 unsigned char noInputCount = 0;
 unsigned char speedControl = 4;
 unsigned char speed = 0;
 unsigned long score = 0;
 unsigned char showScore = 0;
 unsigned char showScorePosition;
 unsigned char randomNumber;
 unsigned long slowDown = 0;
 unsigned char laserCount = 3;
 unsigned long holdCount = 0;
 unsigned short player2option = 0;
 */
















unsigned char play1 = ~PINA & 0x01;
unsigned char play2 = ~PINB & 0x01;

unsigned char p1Up = ~PINA & 0x10;
unsigned char p2Up = ~PINB & 0x10;

unsigned char p1D = ~PINA & 0x04;
unsigned char p2D = ~PINB & 0x04;

unsigned char Reset = ~PINA & 0x80;

//Task Scheduler----------------------------------------------------
typedef struct task{
    signed char state;
    unsigned long int period;
    unsigned long int elapsedTime;
    int (*TickFct)(int);
} task;

//Main Function-----------------------------------------------------
int main(void){
    DDRA = 0x00; PORTA = 0xFF; //P1 Controller
    DDRB = 0x00; PORTB = 0xFF; //P2 Controller
    DDRC = 0xFF; PORTC = 0x00; //LCD Data Lines
    DDRD = 0x00; PORTD = 0xFF; //LCD Control Lines

    unsigned long int Game_et = 1;
    unsigned long int Enemy_et = 1;
    unsigned long int Obstacles_et = 50;

    unsigned long int tmpGCD = 1;
    tmpGCD = findGCD(Game_et, Enemy_et);

    unsigned long int GCD = tmpGCD;

    unsigned long int Game_period = Game_et/GCD;
    unsigned long int Enemy_period = Enemy_et/GCD;
    unsigned long int Obstacles_period = Obstacles_et/GCD;

    static task task1, task2, task3;
    task *tasks[] = {&task1, &task2, &task3};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    task1.state = -1;
    task1.period = Game_period;
    task1.elapsedTime = Game_period;
    task1.TickFct = &Game;

    task2.state = -1;
    task2.period = Enemy_period;
    task2.elapsedTime = Enemy_period;
    task2.TickFct = &Enemy;

    task3.state = -1;
    task3.period = Obstacles_period;
    task3.elapsedTime = Obstacles_period;
    task3.TickFct = &Obstacles;

    LCD_init();

    TimerSet(GCD);
    TimerOn();
    
    srand(300);

    while(1){
        for(i = 0; i < numTasks; i++){
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

