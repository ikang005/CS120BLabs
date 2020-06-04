enum ObstacleStates{Start3, mStart, Hit, None, Wait3, wGame3}obstaclestate;

int Obstacle(int obstaclestate){
    switch(obstaclestate){
        case Start3:
            if(play1 || play2){
                obstaclestate = mStart;
            }
            else{
                obstaclestate = Start3;
            }
            break;
        case mStart:
            if(speedC <= 0){
                random = rand() % 5 + 1;
                if((cursPos == obst1) || (cursPos == obst2) || (cursPos == laser)){
                    speed = 0;
                    speedC = 4;
                    obst1 = 0;
                    obst2 = 0;
                    bullPos = 0;
                    obstaclestate = Hit;
                }
                else{
                    LCD_ClearScreen();
                    LCD_Cursor(cursPos);
                    if(play2){
                        if(!bullPos){
                            if(cursPos == 17){
                                bullPos = 18;
                            }
                            else{
                                bullPos = 2;
                            }
                        }
                    }
                    if(obst1 == 0){
                        if(random <= 2 && obst2 <= 27){
                            obst1 = 16;
                        }
                    }
                    if(obst2 = 0){
                        if(random >= 3 && obst1 <= 12){
                            obst2 = 32;
                        }
                    }
                    //Ostacles
                    LCD_Cursor(obst1);
                    LCD_WriteData('#');
                    LCD_Cursor(obst2);
                    LCD_WriteData('|');
                    
                    //P2
                    if(p2Choice){
                        LCD_Cursor(cursPos2);
                        LCD_WriteData('2');
                        LCD_Cursor(laser);
                        LCD_WriteData('<');
                    }
                    
                    //Laser Movement
                    LCD_Cursor(bullPos);
                    LCD_WriteData('>');
                    
                    if(bullPos){
                        if(bullPos < 15){
                            bullPos++;
                        }
                        else if(bullPos < 31 && bullPos > 17){
                            bullPos++;
                        }
                        else{
                            bullPos = 0;
                        }
                        //Displaying hitting destroyable target
                        if(obst2){
                            bullHit = obst2 - bullPos;
                            if(bullHit <= 1){
                                LCD_Cursor(obst2);
                                LCD_WriteData('\0');
                                obst2 = 0;
                                bullPos = 0;
                            }
                        }
                    }
                    //Speed toggle
                    if(obst1 > 1){
                        obst1--;
                        if(obst1 == 1){
                            speed++;
                        }
                    }
                    else{
                        obst1 = 0;
                    }
                    if(obst2 > 17){
                        obst2--;
                        if(obst2 == 17){
                            speed++;
                        }
                    }
                    else{
                        obst2 = 0;
                    }
                    if(slow >= 6){
                        if(laser){
                            if(laser > 17){
                                laser--;
                            }
                            else if(laser == 16){
                                laser = 0;
                            }
                            else if(laser > 1){
                                laser--;
                            }
                            else{
                                laser = 0;
                            }
                        }
                        slow = 0;
                    }
                    else{
                        slow++;
                    }
                    if(speed < 2){
                        speedC = 3;
                    }
                    else if(speed < 5){
                        speedC = 2;
                    }
                    else if(speed < 7){
                        speedC = 1;
                    }
                    else{
                        speedC = 0;
                    }
                    score++;
                }
            }
            else{
                speedC--;
            }
            break;
        case Hit:
            if(cursPos == 1){
                for(cursPos = 1; cursPos <= 8; cursPos++){
                    LCD_Cursor(cursPos);
                    LCD_WriteData('\0');
                    LCD_Cursor(cursPos + 16);
                    LCD_WriteData('\0');
                }
                state = None;
            }
            else{
                for(cursPos = 17; cursPos <= 24; cursPos++){
                    LCD_Cursor(cursorPosition);
                    LCD_WriteData('\0');
                    LCD_Cursor(cursorPosition - 16);
                    LCD_WriteData('\0');
                }
                state = None;
            }
            break;
        case None:
            if(noneC < 90){
                noneC++;
            }
            else if(p2Up || p2D){
                obstaclestate = wGame3;
                noneC = 0;
            }
            else if (play2){
                obstaclestate = Wait3;
                noneC = 0;
            }
            else{
                obstaclestate = None;
            }
            break;
        case Wait3:
            if(play2){
                obstaclestate = Wait3;
            }
            else{
                obstaclestate = Start3;
            }
            break;
        case wGame3:
            if(p2Up || p2D){
                obstaclestate = wGame3;
            }
            else{
                obstaclestate = mStart;
            }
            break;
        default:
            obstaclestate = Start3;
            break;
    }
}

init = Start3
startMove = mStart
explosion = Hit
noInput = None
holdStart3 = Wait3
holdGame3 = wGame3
state = obstaclestate
D = p2;
speedControl = speedC
bulletHit3 = bullHit;
bulletHit4 = bullHit2;

