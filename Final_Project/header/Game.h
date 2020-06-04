enum gameState{Start, dis1, gStart, gOver, dis2, Score, Wait, wGame}gamestate;

int Game(int gamestate){
    switch(gamestate){
        case Start:
            LCD_DisplayString(1, introString);
            LCD_Cursor(0);
            p2Choice = 0;
            gamestate = dis1;
            break;
        case dis1:
            if(play1){
                LCD_ClearScreen();
                gamestate = gStart;
            }
            else if(play2){
                LCD_ClearScreen();
                p2Choice = 1;
                gamestate = gStart;
            }
            else{
                gamestate = dis1;
            }
            break;
        case gStart:
            if((cursPos == obst1) || (cursPos == obst2) || (cursPos == laser)){
                gamestate = dis2;
            }
            else{
                LCD_Cursor(cursPos);
                if(p1Up){
                    cursPos = 1;
                }
                else(p1D){
                    cursPos = 17;
                }
            }
            break;
        case dis2:
            if(holdDC < 500){
                holdDC++;
            }
            else{
                holdDC = 0;
                LCD_ClearScreen();
                LCD_DisplayString(1, gameString);
                gamestate = gOver;
            }
            break;
        case gOver:
            if(holdDC < 2000){
                holdDC++;
            }
            else{
                showSPos = 7;
                LCD_DisplayString(1, scoreString);
                while(score > 100){
                    showS++;
                    score -= 100;
                }
                if(showS != 0){
                    LCD_Cursor(showSPos);
                    LCD_WriteData(showS + '0');
                    showS = 0;
                    showSPos++;
                }
                while(score > 10){
                    showS++;
                    score -= 10;
                }
                LCD_Cursor(showSPos);
                LCD_WriteData(showS + '0');
                showS = 0;
                showSPos++;
                while(score > 1){
                    showS++;
                    score -= 1;
                }
                LCD_Cursor(showSPos);
                LCD_WriteData(showS + '0');
                showS = 0;
                showSPos++;
                
                score = 0;
                gamestate = Score;
                holdDC = 0;
                cursPos = 1;
            }
            break;
        case Score:
            if(holdDC < 2000){
                holdDC++;
            }
            else if(p1Up || p1D){
                holdDC = 0;
                gamestate = wGame;
            }
            else if(p1){
                holdDC = 0;
                gamestate = Wait;
            }
            else{
                gamestate = Score;
            }
            break;
        case Wait:
            if(p1){
                gameState = Wait;
            }
            else{
                gameState = Start;
            }
            break;
        case wGame:
            if(p1Up || p1D){
                gamestate = wGame;
            }
            else{
                gamestate = gStart;
            }
            break;
        default:
            gamestate = Start;
            break;
    }
    return gamestate;
}
