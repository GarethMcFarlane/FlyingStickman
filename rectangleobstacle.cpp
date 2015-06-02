#include "rectangleobstacle.h"

RectangleObstacle::RectangleObstacle(int startX, int startY, float xVelocity, int height, int width, QColor color, int xBack, int yBack)
    :m_x(startX),
      m_y(startY),
      m_xVelocity(xVelocity),
      m_height(height),
      m_width(width),
      m_color(color),
      m_xBack(xBack),
      m_yBack(yBack),
      m_initialx(startX)
{
}
void RectangleObstacle::render(QPainter &painter, int collisioncheck, bool invuln) const{
    if(m_x + m_width>0 && m_x < m_xBack){
        painter.fillRect(QRect(m_x ,m_yBack-m_height-m_y,m_width,m_height),QBrush(m_color));
    }
}

void RectangleObstacle::update(){
    m_x -= int(m_xVelocity);

}

void RectangleObstacle::setMax(float max){
    m_max = max;
    if(m_xVelocity<0){
        m_x -= max+m_xBack;
    }
}

int RectangleObstacle::hasCollided(int x, int y, int width, int height) const{
    if(x+width>=m_x && x<=m_x+m_width){
        if(y<m_height+m_y && y+height>m_y){
            return -1;
        }
    }
    return 0;
 }


void RectangleObstacle::setXVelocity(int x) {
    m_xVelocity += x;
}

RectangleObstacle::~RectangleObstacle()
{

}

void RectangleObstacle::resetLevel() {
    m_x = m_initialx;
}
