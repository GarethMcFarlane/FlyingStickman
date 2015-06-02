#include "triangleobstacle.h"

TriangleObstacle::TriangleObstacle(int startX, int startY, float xVelocity, int height, int width, QColor color, int xBack, int yBack)
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
void TriangleObstacle::render(QPainter &painter, int collisioncheck, bool invuln) const{
    if(m_x + m_width>0 && m_x < m_xBack){
        painter.setBrush(m_color);
        QPolygon triangle;
        triangle.putPoints(0, 3, m_x, m_yBack-m_y, m_x+m_width, m_yBack-m_y, m_x+(m_width/2), m_yBack-m_height-m_y);
        painter.drawPolygon(triangle);
    }
}

void TriangleObstacle::update(){
    m_x -= int(m_xVelocity);

}

void TriangleObstacle::setMax(float max){
    m_max = max;
    if(m_xVelocity<0){
        m_x -= max+m_xBack;
    }
}
int TriangleObstacle::hasCollided(int x, int y, int width, int height) const{
    if(x+width<m_x || x>m_x+m_width){
        return 0;
    }
    if(y<m_height+m_y && y+height > m_y){
        double halfw = m_width/2.0;
        double hit = m_height-y;
        double ratio = halfw*hit/m_height;
        hit = halfw-ratio;
        if(x+width>hit+m_x && x < m_x+m_width-hit){
            return -1;
        }
    }
    return 0;
}

void TriangleObstacle::setXVelocity(int x) {
    m_xVelocity += x;
}

TriangleObstacle::~TriangleObstacle()
{

}

void TriangleObstacle::resetLevel() {
    m_x = m_initialx;
}
