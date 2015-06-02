#include "normalpowerup.h"

NormalPowerup::NormalPowerup(int startX, int startY, float xVelocity, int height, int width, QColor color, int xBack, int yBack)
    :m_x(startX),
      m_y(startY),
      m_xVelocity(xVelocity),
      m_height(height),
      m_width(width),
      m_color(color),
      m_xBack(xBack),
      m_yBack(yBack),
      m_initialx(startX),
      m_powerupimage(":/resources/normal.png")
{
}
void NormalPowerup::render(QPainter &painter, int collisioncheck, bool invuln) const{
    if(m_x + m_width>0 && m_x < m_xBack){
       painter.drawImage(QRect(m_x ,m_yBack-m_height-m_y,m_width,m_height),m_powerupimage);
    }
}

void NormalPowerup::update(){
    m_x -= int(m_xVelocity);
}

void NormalPowerup::setMax(float max){
    m_max = max;
    if(m_xVelocity<0){
        m_x -= max+m_xBack;
    }
}

int NormalPowerup::hasCollided(int x, int y, int width, int height) const{
    if(x+width>=m_x && x<=m_x+m_width){
        if(y<m_height+m_y && y+height>m_y){
            return -3;
        }
    }
    return 0;
}


void NormalPowerup::setXVelocity(int x) {
    m_xVelocity += x;
}

NormalPowerup::~NormalPowerup()
{

}

void NormalPowerup::resetLevel() {
    m_x = m_initialx;
}
