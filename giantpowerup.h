#ifndef GIANTPOWERUP_H
#define GIANTPOWERUP_H



#include "obstacle.h"

class GiantPowerup : public Obstacle
{
public:
    GiantPowerup(int startx, int starty, float xVelocity, int height, int width, QColor color, int xBack, int yBack);
    void render(QPainter &painter, int collisioncheck, bool invuln) const;
    void update();
    void setMax(float max);
    int hasCollided(int x, int y, int width, int height) const;
    void setXVelocity(int x);
    void resetLevel();
    ~GiantPowerup();
private:
    int m_x;
    int m_y;
    int m_xVelocity;
    int m_height;
    int m_width;
    QColor m_color;
    int m_xBack;
    int m_yBack;
    float m_max;
    int m_initialx;
    QImage m_powerupimage;
};


#endif // GIANTPOWERUP_H
