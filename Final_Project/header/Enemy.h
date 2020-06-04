enum EnemyStates{Start2, eMove, Hold, Wait2, wGame2}enemystate;

int Enemy(int enemystates){
    switch(enemystate){
        case Start2:
            if(play2){
                enemystate = eMove;
            }
            else{
                enemystate = Start2;
            }
            break;
        case eMove:
            if((cursPos == obst1) || (cursPos == obst2) || (cursPos == laser)){
                slow = 0;
                laserC = 3;
                cursPos2 = 16;
                enemystate = Hold;
            }
            if(p2Up){
                cursPos2 = 16;
            }
            else if(p2D){
                cursPos2 = 32;
            }
            if(p2){
                if(!laser && laserC){
                    if(cursPos2 == 16){
                        laser = 15;
                        laserC--;
                    }
                    else if(cursPos2 == 32){
                        laser = 31;
                        laserC--;
                    }
                }
            }
            break;
        case Hold:
            if(holdCount < 4500){
                holdCount++;
            }
            else if(p2Up || p2D){
                enemystate = wGame2;
                holdCount = 0;
            }
            else if(p2){
                enemystate = Wait2;
                holdCount = 0;
            }
            else{
                laser = 0;
                enemystate = Hold;
            }
            break;
        case Wait2:
            if(p2){
                enemystate = Wait2;
            }
            else{
                enemystate = Start2;
            }
            break;
        case wGame2:
            if(p2Up || p2D){
                enemystate = wGame2;
            }
            else{
                enemystate = Move;
            }
            break;
        default:
            enemystate = Start2;
            break;
    }
    return enemystate;
}
