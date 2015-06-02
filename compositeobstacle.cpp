#include "compositeobstacle.h"

CompositeObstacle::CompositeObstacle()
{
}
void CompositeObstacle::add(Obstacle *obst){
    m_obstacles.push_back(obst);
}

void CompositeObstacle::render(QPainter &painter, int collisioncheck, bool invuln) const{
    for(std::list<Obstacle*>::const_iterator it=m_obstacles.begin(); it!=m_obstacles.end(); ++it){
        (*it)->render(painter, collisioncheck, invuln);
    }
}

void CompositeObstacle::update(){
    for(std::list<Obstacle*>::iterator it=m_obstacles.begin(); it!=m_obstacles.end(); ++it){
        (*it)->update();
    }
}

void CompositeObstacle::setMax(float max){
    for(std::list<Obstacle*>::iterator it=m_obstacles.begin(); it!=m_obstacles.end(); ++it){
        (*it)->setMax(max);
    }
}
int CompositeObstacle::hasCollided(int x, int y, int width, int height) const{
    for(std::list<Obstacle*>::const_iterator it=m_obstacles.begin(); it!=m_obstacles.end(); ++it){
        int result = (*it)->hasCollided(x,y, width, height);
        if(result == -1){
            return -1;
        } else if (result != 0) {
            return result;
        }
    }
    return 0;
}
CompositeObstacle::~CompositeObstacle()
{
    for(std::list<Obstacle*>::iterator it=m_obstacles.begin(); it!=m_obstacles.end(); ++it){
        delete(*it);
    }
}


void CompositeObstacle::setXVelocity(int x) {
    for(std::list<Obstacle*>::iterator it=m_obstacles.begin(); it!=m_obstacles.end(); ++it){
        (*it)->setXVelocity(x);
    }
}

void CompositeObstacle::resetLevel() {
    for(std::list<Obstacle*>::iterator it=m_obstacles.begin(); it!=m_obstacles.end(); ++it){
        (*it)->resetLevel();
    }
}
