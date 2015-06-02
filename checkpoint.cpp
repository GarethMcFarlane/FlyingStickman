#include "checkpoint.h"
#include <iostream>


Checkpoint::Checkpoint(int startX, int startY, float xVelocity, int height, int width, QColor color, int xBack, int yBack, int level)
    :m_x(startX),
      m_y(startY),
      m_xVelocity(xVelocity),
      m_height(height),
      m_width(width),
      m_color(color),
      m_xBack(xBack),
      m_yBack(yBack),
      m_level(level),
      checkpointimage(":/resources/checkpoint.gif"),
      m_initialx(startX)
{
}
void Checkpoint::render(QPainter &painter, int collisioncheck, bool invuln) const{
    if(m_x + m_width>0 && m_x < m_xBack){
        painter.drawImage(QRect(m_x ,m_yBack-m_height-m_y,m_width,m_height),checkpointimage);
    }
}

void Checkpoint::update(){
    m_x -= int(m_xVelocity);

}

void Checkpoint::setMax(float max){
    m_max = max;
    if(m_xVelocity<0){
        m_x -= max+m_xBack;
    }
}

int Checkpoint::hasCollided(int x, int y, int width, int height) const{
    if(x+width>=m_x && x<=m_x+m_width){
        if(y<m_height+m_y && y+height>m_y){
            return m_level;
        }
    }
    return 0;
}

void Checkpoint::setXVelocity(int x) {
    m_xVelocity += x;
}

Checkpoint::~Checkpoint()
{

}

void Checkpoint::resetLevel() {
    m_x = m_initialx;
}
