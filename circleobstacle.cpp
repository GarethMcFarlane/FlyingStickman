#include "circleobstacle.h"
#include <iostream>

#include <cmath>

CircleObstacle::CircleObstacle(int startX, int startY, float xVelocity, int radius, QColor color, int xBack, int yBack)
    :m_x(startX),
      m_y(startY),
      m_xVelocity(xVelocity),
      m_radius(radius),
      m_color(color),
      m_xBack(xBack),
      m_yBack(yBack),
      m_initialx(startX)
{
}
void CircleObstacle::render(QPainter &painter, int collisioncheck, bool invuln) const{
    if(m_x + 2*m_radius >0 && m_x < m_xBack){
        painter.setBrush(m_color);
        painter.drawEllipse(m_x,
            m_yBack-2*m_radius - m_y,
            m_radius * 2,
            m_radius * 2);
    }
}

void CircleObstacle::update(){
    m_x -= int(m_xVelocity);

}

void CircleObstacle::setMax(float max){
    m_max = max;
    if(m_xVelocity<0){
        m_x -= max+m_xBack;
    }
}

int CircleObstacle::hasCollided(int x, int y, int width, int height) const{

    if(m_x>x+width || m_x+m_radius*2<x){
        return 0;
    }
    if(y<2*m_radius){
        //get closest distance to center in x and y direction
        int Y = m_radius+m_y - y;
        int Y1 = m_radius+m_y -y-height;
        if(Y*Y1 <0){
            Y = 0;
        } else {
            if(abs(Y) > abs(Y1)){
                Y=Y1;
            }
        }
        int X = m_x+m_radius -(width+x);
        int X1 = m_x+m_radius -x;
        if(X*X1 <0){
            X = 0;
        } else {
            if(abs(X) > abs(X1)){
                X=X1;
            }
        }
        //need to check X^2 + Y^2 < m_radius^2 (circle equation)
        Y = Y*Y;
        X = X*X;
        int R = m_radius*m_radius;
        if(X + Y <= R){
             return -1;
        }
    }
    return 0;

}


void CircleObstacle::setXVelocity(int x) {
    m_xVelocity += x;
}

CircleObstacle::~CircleObstacle()
{

}

void CircleObstacle::resetLevel() {
    m_x = m_initialx;
}
