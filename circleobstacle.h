#ifndef CIRCLEOBSTACLE_H
#define CIRCLEOBSTACLE_H

#include "obstacle.h"

class CircleObstacle : public Obstacle
{
public:
    CircleObstacle(int startx, int starty, float xVelocity, int radius, QColor color, int xBack, int yBack);
    void render(QPainter &painter, int collisioncheck, bool invuln) const;
    void update();
    void setMax(float max);
    int hasCollided(int x, int y, int width, int height) const;
    void setXVelocity(int x);
    void resetLevel();
    ~CircleObstacle();
private:
    int m_x;
    int m_y;
    int m_xVelocity;
    int m_radius;
    QColor m_color;
    int m_xBack;
    int m_yBack;
    float m_max;
    int m_initialx;
};
#endif // CIRCLEOBSTACLE_H
