#include "gamemediator.h"
#include <iostream>

GameMediator::GameMediator(Stickman *stickman, Background *background, CompositeObstacle** levels, int xcollisioncheck, int numlevels, bool pausescreen) :
    m_stickman(stickman),
    m_background(background),
    m_paused(false),
    m_pauseImage(":/resources/paused.png"),
    m_jumps(0),
    m_moveSpeed(3),
    m_score(0),
    m_currlevel(1),
    m_finished(false),
    m_won(false),
    m_sprites(NULL),
    m_explosioncounter(0),
    m_levels(levels),
    m_invuln(false),
    m_xCollisionCheck(xcollisioncheck),
    m_levelnum(numlevels),
    m_pauseScreenEnabled(pausescreen)
{

}

GameMediator::~GameMediator()
{

}

void GameMediator::update() {
    //used alot
    int y= m_stickman->getYOffset();
    int yv = m_stickman->getYVelocity();

    // Update the game state if not paused
    if (!m_paused && !m_finished) {
        //0 = no collision
        //-1 = collision
        //Numbers greater than 0 indicate the checkpoint reached
        //Numbers less than -1 indicate powerups


        //only update in x direction if we wont hit an obstacle,
        int result = m_levels[m_stickman->getCurrLevel()-1]->hasCollided(m_xCollisionCheck,y, m_stickman->getWidth(), m_stickman->getHeight());
        switch (result) {
        //No collision
        case 0:
            m_stickman->update(m_timerMs);
            m_background->update(m_timerMs);
            m_levels[m_stickman->getCurrLevel() - 1]->update();
            m_score+=10;
            break;

            //Collision with obstacle
        case -1:
            if (m_invuln) {
                m_stickman->update(m_timerMs);
                m_background->update(m_timerMs);
                m_levels[m_stickman->getCurrLevel()-1]->update();
                m_score+=10;
            } else {
                m_stickman->loseLife();
                if (m_stickman->getLives() == 0) {
                    //Game over
                    m_finished = true;
                } else {
                    //Reset level
                    m_levels[m_stickman->getCurrLevel() -1]->resetLevel();
                }
           }
            break;
            //Tiny powerup
        case -2:
            m_stickman->update(m_timerMs);
            m_background->update(m_timerMs);
            m_levels[m_stickman->getCurrLevel() -1]->update();
            m_score+=10;
            m_stickman->setScale(1);
            m_stickman->setGravity(1);
            m_invuln = false;
            break;
            //normal powerup
        case -3:
            m_stickman->update(m_timerMs);
            m_background->update(m_timerMs);
            m_levels[m_stickman->getCurrLevel() -1]->update();
            m_score+=10;
            m_stickman->setScale(2);
            m_stickman->setGravity(1);
            m_invuln = false;
            break;
            //large powerup
        case -4:
            m_stickman->update(m_timerMs);
            m_background->update(m_timerMs);
            m_levels[m_stickman->getCurrLevel() -1]->update();
            m_score+=10;
            m_stickman->setScale(4);
            m_stickman->setGravity(0.5);
            m_invuln = false;
            //set jump
            break;
            //giant powerup
        case -5:
            m_stickman->update(m_timerMs);
            m_background->update(m_timerMs);
            m_levels[m_stickman->getCurrLevel() -1]->update();
            m_score+=10;
            m_stickman->setScale(8);
            m_stickman->setGravity(1);
            m_invuln = true;
            break;
            //Checkpoint collision
        default:
            m_stickman->update(m_timerMs);
            m_background->update(m_timerMs);
            m_levels[m_stickman->getCurrLevel() -1]->update();
            //Check if all checkpoints are finished
            if (m_stickman->getCurrLevel() == m_levelnum) {
                //Game over - passed checkpoints
                m_finished = true;
                m_won = true;
            } else {
                m_score+=10;
                m_stickman->setCurrlevel(result+1);
            }
            break;
        }



        }
        //need to check if we are checking a negative value first, dont wont
        if(y+yv<0){
            yv = -y;
        }

        //try and move in y direction. if we hit a collision hald the yvelocity and try again until yVelocity = 0
        //will make it appear like stickamn lands on obstacle rather than float. also reset jumps if we hit something

        while(m_levels[m_stickman->getCurrLevel()-1]->hasCollided(m_xCollisionCheck -m_stickman->getXVelocity(),
                                                   y+yv,
                                                   m_stickman->getWidth(), m_stickman->getHeight()) == -1){
            yv/=2;
            m_stickman->setYVelocity(yv);
            m_stickman->setJumps(0);
            if(yv == 0){
                break;
            }
        }
        //move stickman in y direction based on above result
        m_stickman->updateJump();
        m_explosioncounter++;
        //reset jumps if on the ground
        if(m_stickman->getYOffset() == 0){
            m_stickman->setJumps(0);
        }

}


bool GameMediator::isFinished() {
    return m_finished;
}

bool GameMediator::isPaused() {
    return m_paused;
}

int GameMediator::getScore() {
    return m_score;
}

bool GameMediator::getinvuln() {
    return m_invuln;
}
